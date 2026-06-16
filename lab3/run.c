#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_NUMBERS 100000
#define INITIAL_CAPACITY 100
#define LINEAR_STEP 100

typedef struct {
    const char *name;
    int reallocCount;
    int moveCount;
    int finalCapacity;
    double seconds;
} Result;

void *checked_malloc(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }

    return ptr;
}

void print_result(Result result) {
    printf("%s\n", result.name);
    printf("Time: %.6f seconds\n", result.seconds);
    printf("Resize calls: %d\n", result.reallocCount);
    printf("Address changes: %d\n", result.moveCount);
    printf("Final capacity: %d\n\n", result.finalCapacity);
}

Result run_realloc_strategy(const char *name, int useDoubling) {
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    int resizeCount = 0;
    int moveCount = 0;
    int *numbers = checked_malloc((size_t)capacity * sizeof(int));
    clock_t start = clock();

    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        if (size == capacity) {
            int newCapacity = useDoubling ? capacity * 2 : capacity + LINEAR_STEP;
            int *oldNumbers = numbers;
            int *newNumbers = realloc(numbers, (size_t)newCapacity * sizeof(int));

            if (newNumbers == NULL) {
                free(numbers);
                fprintf(stderr, "Error: realloc failed.\n");
                exit(1);
            }

            resizeCount++;

            if (newNumbers != oldNumbers) {
                moveCount++;
            }

            numbers = newNumbers;
            capacity = newCapacity;
        }

        numbers[size] = i;
        size++;
    }

    clock_t end = clock();
    free(numbers);

    Result result = {
        name,
        resizeCount,
        moveCount,
        capacity,
        (double)(end - start) / CLOCKS_PER_SEC
    };

    return result;
}

Result run_manual_copy_strategy(void) {
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    int resizeCount = 0;
    int moveCount = 0;
    int *numbers = checked_malloc((size_t)capacity * sizeof(int));
    clock_t start = clock();

    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        if (size == capacity) {
            int newCapacity = capacity * 2;
            int *oldNumbers = numbers;
            int *newNumbers = checked_malloc((size_t)newCapacity * sizeof(int));
            size_t copiedBytes = (size_t)capacity * sizeof(int);

            memcpy(newNumbers, oldNumbers, copiedBytes);
            printf("Move: address %p -> %p, copied %lu bytes\n",
                   (void *)oldNumbers,
                   (void *)newNumbers,
                   (unsigned long)copiedBytes);
            free(oldNumbers);

            numbers = newNumbers;
            capacity = newCapacity;
            resizeCount++;
            moveCount++;
        }

        numbers[size] = i;
        size++;
    }

    clock_t end = clock();
    free(numbers);

    Result result = {
        "Manual malloc + memcpy + free",
        resizeCount,
        moveCount,
        capacity,
        (double)(end - start) / CLOCKS_PER_SEC
    };

    return result;
}

int main(void) {
    Result linear = run_realloc_strategy("Linear strategy (+100)", 0);
    Result doubling = run_realloc_strategy("Doubling strategy (*2)", 1);
    Result manual = run_manual_copy_strategy();

    printf("\nSummary\n");
    printf("=======\n");
    print_result(linear);
    print_result(doubling);
    print_result(manual);

    return 0;
}
