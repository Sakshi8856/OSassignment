#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Initial Burst Time
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time
} Process;

// Function to compare processes for sorting by burst time
int compare(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burst - p2->burst;
}

// Function to generate next CPU burst time randomly
int generate_random_burst() {
    return rand() % 10 + 1; // Random burst time between 1 and 10
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    Process processes[MAX_PROCESSES];
    int n;

    // Input number of processes
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    // Input arrival times and first CPU bursts
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
    }

    // Sort processes based on arrival time and burst time
    qsort(processes, n, sizeof(Process), compare);

    int time = 0; // Current time
    int completed = 0;

    // Gantt chart output
    printf("\nGantt Chart:\n");
    while (completed < n) {
        int idx = -1;
        int min_burst = __INT_MAX__;

        // Find the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].burst < min_burst) {
                min_burst = processes[i].burst;
                idx = i;
            }
        }

        if (idx != -1) {
            // Update time and process details
            time += processes[idx].burst + 2; // Add I/O waiting time
            processes[idx].turnaround = time - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;

            printf("| P%d ", processes[idx].pid);
            processes[idx].burst = generate_random_burst(); // Generate new burst for next CPU burst

            completed++;
        } else {
            // If no process is ready, advance time
            time++;
        }
    }
    printf("|\n");

    // Calculate and print turnaround time and waiting time
    float total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, processes[i].turnaround, processes[i].waiting);
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }

    // Average times
    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}

