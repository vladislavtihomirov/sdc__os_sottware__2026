#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int globalInitialized = 42;
int globalUninitialized;

int main(int argc, char *argv[]);

void print_usage(const char *programName) {
    printf("Usage: %s <mode>\n", programName);
    printf("Modes:\n");
    printf("  addresses        Print addresses from text, data, bss, stack, and heap\n");
    printf("  addresses-pause  Print addresses and wait, so /proc/<pid>/maps can be checked\n");
    printf("  stack <depth>    Recursively print stack addresses up to depth\n");
    printf("  endian           Show raw bytes of uint32_t value\n");
    printf("  leak             Allocate memory and intentionally do not free it\n");
    printf("  fixed            Allocate memory and free it correctly\n");
}

void print_memory_map(int pauseAfterPrint) {
    int localVariable = 7;
    int *heapValue = malloc(100);

    if (heapValue == NULL) {
        fprintf(stderr, "Error: malloc failed.\n");
        exit(1);
    }

    *heapValue = 100;

    printf("PID: %d\n", getpid());
    printf("main function (.text)          : %p\n", (void *)&main);
    printf("global initialized (.data)     : %p\n", (void *)&globalInitialized);
    printf("global uninitialized (.bss)    : %p\n", (void *)&globalUninitialized);
    printf("heap allocation (malloc)       : %p\n", (void *)heapValue);
    printf("local variable (stack)         : %p\n", (void *)&localVariable);

    if (pauseAfterPrint) {
        printf("\nRun in another terminal: cat /proc/%d/maps\n", getpid());
        printf("Press Enter to continue...");
        getchar();
    }

    free(heapValue);
}

void test_stack(int depth, int maxDepth) {
    volatile char buffer[1024];
    buffer[0] = (char)depth;

    printf("Depth %d, buffer address: %p\n", depth, (const void *)&buffer[0]);

    if (depth < maxDepth) {
        test_stack(depth + 1, maxDepth);
    }
}

int run_stack_demo(const char *depthText) {
    char *end = NULL;
    long maxDepth = strtol(depthText, &end, 10);

    if (*depthText == '\0' || *end != '\0' || maxDepth < 0) {
        fprintf(stderr, "Error: depth must be a non-negative integer.\n");
        return 1;
    }

    test_stack(0, (int)maxDepth);
    return 0;
}

void print_endian_demo(void) {
    uint32_t value = 0x41424344;
    unsigned char *bytes = (unsigned char *)&value;

    printf("Value: 0x%08x\n", value);
    printf("Bytes: ");

    for (size_t i = 0; i < sizeof(value); i++) {
        printf("%02x", bytes[i]);

        if (i + 1 < sizeof(value)) {
            printf(" ");
        }
    }

    printf("\n");

    if (bytes[0] == 0x44) {
        printf("Result: little-endian system.\n");
    } else {
        printf("Result: big-endian or another byte order.\n");
    }
}

int *allocate_int_array(void) {
    int *numbers = malloc(10 * sizeof(int));

    if (numbers == NULL) {
        fprintf(stderr, "Error: malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        numbers[i] = i + 1;
    }

    return numbers;
}

void run_leak_demo(void) {
    int *numbers = allocate_int_array();

    printf("Allocated array at %p and intentionally did not call free().\n", (void *)numbers);
}

void run_fixed_demo(void) {
    int *numbers = allocate_int_array();

    printf("Allocated array at %p.\n", (void *)numbers);
    free(numbers);
    printf("Memory was freed correctly.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "addresses") == 0) {
        print_memory_map(0);
        return 0;
    }

    if (strcmp(argv[1], "addresses-pause") == 0) {
        print_memory_map(1);
        return 0;
    }

    if (strcmp(argv[1], "stack") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s stack <depth>\n", argv[0]);
            return 1;
        }

        return run_stack_demo(argv[2]);
    }

    if (strcmp(argv[1], "endian") == 0) {
        print_endian_demo();
        return 0;
    }

    if (strcmp(argv[1], "leak") == 0) {
        run_leak_demo();
        return 0;
    }

    if (strcmp(argv[1], "fixed") == 0) {
        run_fixed_demo();
        return 0;
    }

    print_usage(argv[0]);
    return 1;
}
