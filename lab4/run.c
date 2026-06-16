#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define NAME_SIZE 256

struct FileNode {
    char name[NAME_SIZE];
    long size;
    unsigned long inode;
    struct FileNode *next;
};

struct FileNode *create_node(const char *name, const struct stat *metadata) {
    struct FileNode *node = malloc(sizeof(struct FileNode));

    if (node == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';
    node->size = (long)metadata->st_size;
    node->inode = (unsigned long)metadata->st_ino;
    node->next = NULL;

    return node;
}

void append_node(struct FileNode **head, struct FileNode **tail, struct FileNode *node) {
    if (*head == NULL) {
        *head = node;
        *tail = node;
        return;
    }

    (*tail)->next = node;
    *tail = node;
}

struct FileNode *scan_directory(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct FileNode *head = NULL;
    struct FileNode *tail = NULL;

    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        struct stat metadata;
        char fullPath[PATH_MAX];
        int written;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        written = snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);
        if (written < 0 || (size_t)written >= sizeof(fullPath)) {
            fprintf(stderr, "Error: path is too long: %s/%s\n", path, entry->d_name);
            continue;
        }

        if (stat(fullPath, &metadata) == -1) {
            perror(entry->d_name);
            continue;
        }

        append_node(&head, &tail, create_node(entry->d_name, &metadata));
    }

    if (closedir(dir) == -1) {
        perror("closedir");
    }

    return head;
}

void print_structure_size(void) {
    size_t fieldSum = NAME_SIZE + sizeof(long) + sizeof(unsigned long) + sizeof(void *);

    printf("sizeof(struct FileNode) = %zu\n", sizeof(struct FileNode));
    printf("Manual field sum       = %zu\n\n", fieldSum);
}

void print_list(const struct FileNode *head) {
    printf("=== File list ===\n");

    for (const struct FileNode *current = head; current != NULL; current = current->next) {
        printf("[%p] %-30s size=%-8ld inode=%lu\n",
               (const void *)current,
               current->name,
               current->size,
               current->inode);
    }

    printf("\nNode addresses are allocated on the heap and may be non-sequential.\n\n");
}

const struct FileNode *find_file(const struct FileNode *head, const char *name) {
    for (const struct FileNode *current = head; current != NULL; current = current->next) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
    }

    return NULL;
}

void print_file_details(const struct FileNode *node) {
    if (node == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Name:  %s\n", node->name);
    printf("Size:  %ld bytes\n", node->size);
    printf("Inode: %lu\n", node->inode);
}

void free_list(struct FileNode *head) {
    while (head != NULL) {
        struct FileNode *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    char searchName[NAME_SIZE];
    struct FileNode *files = scan_directory("./test-data");

    if (files == NULL) {
        return 1;
    }

    print_structure_size();
    print_list(files);

    printf("Search file: ");
    if (scanf("%255s", searchName) != 1) {
        printf("Error: invalid file name.\n");
        free_list(files);
        return 1;
    }

    print_file_details(find_file(files, searchName));
    free_list(files);

    return 0;
}
