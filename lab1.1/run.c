#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 51
#define GROUP_SIZE 21

int is_valid_name(const char value[]) {
    size_t length = strlen(value);

    if (length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isalpha((unsigned char)value[i]) && value[i] != '-') {
            return 0;
        }
    }

    return 1;
}

int is_valid_group(const char value[]) {
    return strlen(value) > 0;
}

int main(void) {
    char firstName[NAME_SIZE];
    char lastName[NAME_SIZE];
    char group[GROUP_SIZE];
    int birthYear;
    double averageGrade;

    printf("Enter first name: ");
    if (scanf("%50s", firstName) != 1 || !is_valid_name(firstName)) {
        printf("Error: invalid first name.\n");
        return 1;
    }

    printf("Enter last name: ");
    if (scanf("%50s", lastName) != 1 || !is_valid_name(lastName)) {
        printf("Error: invalid last name.\n");
        return 1;
    }

    printf("Enter birth year: ");
    if (scanf("%d", &birthYear) != 1 || birthYear < 1900 || birthYear > 2026) {
        printf("Error: invalid birth year.\n");
        return 1;
    }

    printf("Enter group: ");
    if (scanf("%20s", group) != 1 || !is_valid_group(group)) {
        printf("Error: invalid group.\n");
        return 1;
    }

    printf("Enter average grade (0-100): ");
    if (scanf("%lf", &averageGrade) != 1 || averageGrade < 0.0 || averageGrade > 100.0) {
        printf("Error: invalid average grade.\n");
        return 1;
    }

    printf("\n");
    printf("================================\n");
    printf("          STUDENT CARD          \n");
    printf("================================\n");
    printf("First name    : %s\n", firstName);
    printf("Last name     : %s\n", lastName);
    printf("Birth year    : %d\n", birthYear);
    printf("Group         : %s\n", group);
    printf("Average grade : %.2f\n", averageGrade);
    printf("================================\n");

    return 0;
}
