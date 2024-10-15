#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0, 0},
    {2, 0, 0, 1},
    {3, 0, 2, 1},
    {2, 1, 1, 0},
    {0, 0, 2, 2}
};

int max[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0, 0},
    {2, 1, 1, 1},
    {3, 1, 2, 1},
    {3, 2, 1, 0},
    {1, 0, 2, 2}
};

int available[MAX_RESOURCES] = {3, 3, 2, 2}; // Available resources

void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES]) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool is_safe(int need[MAX_PROCESSES][MAX_RESOURCES], int work[MAX_RESOURCES], bool finish[MAX_PROCESSES], int safe_sequence[MAX_PROCESSES]) {
    int count = 0;
    int work_copy[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work_copy[i] = work[i];
    }

    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int p = 0; p < MAX_PROCESSES; p++) {
            if (!finish[p]) {
                // Check if the needs can be satisfied
                bool can_allocate = true;
                for (int r = 0; r < MAX_RESOURCES; r++) {
                    if (need[p][r] > work_copy[r]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    // Add allocation to work
                    for (int r = 0; r < MAX_RESOURCES; r++) {
                        work_copy[r] += allocation[p][r];
                    }
                    finish[p] = true; // Mark process as finished
                    safe_sequence[count++] = p; // Store in safe sequence
                    found = true;
                }
            }
        }
        // If no process can be allocated, the system is not in a safe state
        if (!found) {
            return false;
        }
    }
    return true;
}

bool request_resources(int process_id, int request[MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES]) {
    for (int r = 0; r < MAX_RESOURCES; r++) {
        if (request[r] > need[process_id][r]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[r] > available[r]) {
            printf("Resources not available.\n");
            return false;
        }
    }

    // Pretend to allocate the requested resources
    for (int r = 0; r < MAX_RESOURCES; r++) {
        available[r] -= request[r];
        allocation[process_id][r] += request[r];
        need[process_id][r] -= request[r];
    }

    // Check if the system is in a safe state after allocation
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];

    for (int r = 0; r < MAX_RESOURCES; r++) {
        work[r] = available[r];
    }

    if (is_safe(need, work, finish, safe_sequence)) {
        printf("Request can be granted safely.\n");
        return true;
    } else {
        // Rollback the changes
        for (int r = 0; r < MAX_RESOURCES; r++) {
            available[r] += request[r];
            allocation[process_id][r] -= request[r];
            need[process_id][r] += request[r];
        }
        printf("Request cannot be granted safely.\n");
        return false;
    }
}

int main() {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need);

    // Display need matrix
    printf("Need Matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check for safe state
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    if (is_safe(need, work, finish, safe_sequence)) {
        printf("The system is in a safe state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < MAX_PROCESSES; i++) {
            printf("P%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    // Request from process P0 for (0, 4, 2, 0)
    int request[MAX_RESOURCES] = {0, 4, 2, 0};
    printf("\nRequesting resources from process P0: (0, 4, 2, 0)\n");
    request_resources(0, request, need, available);

    return 0;
}

