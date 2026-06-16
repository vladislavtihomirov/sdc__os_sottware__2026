#include <stdio.h>
#include <stdlib.h>

int read_count(void) {
    int count;

    printf("Enter number count: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Error: invalid number count.\n");
        return -1;
    }

    return count;
}

int *allocate_numbers(int count) {
    int *numbers = malloc((size_t)count * sizeof(int));

    if (numbers == NULL) {
        printf("Error: memory allocation failed.\n");
    }

    return numbers;
}

int read_numbers(int numbers[], int count) {
    printf("Enter numbers: ");

    for (int i = 0; i < count; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Error: invalid number at position %d.\n", i + 1);
            return 0;
        }
    }

    return 1;
}

int calculate_sum(const int numbers[], int count) {
    int sum = 0;

    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }

    return sum;
}

int find_min(const int numbers[], int count) {
    int min = numbers[0];

    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    return min;
}

int find_max(const int numbers[], int count) {
    int max = numbers[0];

    for (int i = 1; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    return max;
}

void count_even_odd(const int numbers[], int count, int *evenCount, int *oddCount) {
    *evenCount = 0;
    *oddCount = 0;

    for (int i = 0; i < count; i++) {
        if (numbers[i] % 2 == 0) {
            (*evenCount)++;
        } else {
            (*oddCount)++;
        }
    }
}

void sort_numbers(int numbers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

void print_array(const int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d", numbers[i]);

        if (i < count - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

void print_results(int numbers[], int count) {
    int sum = calculate_sum(numbers, count);
    float average = (float)sum / count;
    int min = find_min(numbers, count);
    int max = find_max(numbers, count);
    int evenCount;
    int oddCount;

    count_even_odd(numbers, count, &evenCount, &oddCount);

    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    printf("Even count: %d\n", evenCount);
    printf("Odd count: %d\n", oddCount);

    sort_numbers(numbers, count);
    printf("Sorted array: ");
    print_array(numbers, count);
}

int main(void) {
    int count = read_count();

    if (count == -1) {
        return 1;
    }

    int *numbers = allocate_numbers(count);

    if (numbers == NULL) {
        return 1;
    }

    if (!read_numbers(numbers, count)) {
        free(numbers);
        return 1;
    }

    print_results(numbers, count);
    free(numbers);

    return 0;
}
