#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define RESOURCE_TYPES 3

int available[RESOURCE_TYPES] = {7, 2, 6}; // Available resources
int max[MAX_PROCESSES][RESOURCE_TYPES];     // Max resources for each process
int allocation[MAX_PROCESSES][RESOURCE_TYPES]; // Allocated resources for each process
int need[MAX_PROCESSES][RESOURCE_TYPES];     // Needed resources for each process
int process_count;

void accept_allocation() {
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
}

void accept_max() {
    printf("Enter Max Matrix:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            scanf("%d", &max[i][j]);
        }
    }
}

void calculate_need() {
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void display_allocation() {
    printf("Allocation Matrix:\n");
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
}

void display_max() {
    printf("Max Matrix:\n");
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

void display_need() {
    calculate_need();
    printf("Need Matrix:\n");
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void display_available() {
    printf("Available Resources:\n");
    for (int i = 0; i < RESOURCE_TYPES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

bool check_deadlock() {
    // Placeholder for deadlock detection logic
    // This is a simple demonstration, so we'll return false
    return false;
}

void display_menu() {
    printf("\nMenu:\n");
    printf("1. Accept Allocation Matrix\n");
    printf("2. Accept Max Matrix\n");
    printf("3. Display Allocation Matrix\n");
    printf("4. Display Max Matrix\n");
    printf("5. Display Need Matrix\n");
    printf("6. Display Available Resources\n");
    printf("7. Check for Deadlock\n");
    printf("8. Exit\n");
}

int main() {
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &process_count);

    int choice;
    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                accept_allocation();
                break;
            case 2:
                accept_max();
                break;
            case 3:
                display_allocation();
                break;
            case 4:
                display_max();
                break;
            case 5:
                display_need();
                break;
            case 6:
                display_available();
                break;
            case 7:
                if (check_deadlock()) {
                    printf("Deadlock detected!\n");
                } else {
                    printf("No deadlock detected.\n");
                }
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

