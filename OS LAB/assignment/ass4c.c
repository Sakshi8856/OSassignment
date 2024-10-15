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
    {2, 0, 0, 1},
    {3, 0, 2, 1},
    {2, 1, 1, 0},
    {0, 0, 2, 2}
};

int available[MAX_RESOURCES] = {3, 3, 2, 2};

int need[MAX_PROCESSES][MAX_RESOURCES];

void calculate_need() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool is_safe_state(int work[], bool finish[]) {
    int safe_sequence[MAX_PROCESSES];
    int count = 0;
    int k = 0;

    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == MAX_RESOURCES) {
                    for (int m = 0; m < MAX_RESOURCES; m++)
                        work[m] += allocation[i][m];
                    finish[i] = true;
                    safe_sequence[k++] = i;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++)
        printf("P%d ", safe_sequence[i]);
    printf("\n");

    return true;
}

bool request_resources(int process_id, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Process P%d is requesting resources, but they are not available.\n", process_id);
            return false;
        }
    }

    // Pretend to allocate the resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    // Check for safe state
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    if (is_safe_state(work, finish)) {
        return true;
    } else {
        // Rollback
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
}

void display_need_matrix() {
    printf("Need Matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    calculate_need();
    display_need_matrix();

    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    is_safe_state(work, finish);

    int request[MAX_RESOURCES] = {0, 4, 2, 0};
    int process_id = 1; // Request for Process P1
    printf("\nRequesting resources for Process P%d: (%d, %d, %d, %d)\n", process_id, request[0], request[1], request[2], request[3]);
    request_resources(process_id, request);

    return 0;
}

