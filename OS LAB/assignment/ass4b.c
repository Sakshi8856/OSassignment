#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;                // Process ID
    int arrival_time;       // Arrival time
    int cpu_burst;          // CPU burst time
    int priority;           // Priority
    int completion_time;    // Completion time
    int turnaround_time;    // Turnaround time
    int waiting_time;       // Waiting time
} Process;

// Function to calculate times
void calculate_times(Process *processes, int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // Wait until the process arrives
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Update completion time
        current_time += processes[i].cpu_burst;
        processes[i].completion_time = current_time;
        
        // Calculate turnaround and waiting times
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].cpu_burst;
    }
}

// Function to sort processes based on arrival time and priority
void sort_processes(Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // First sort by arrival time, then by priority
            if ((processes[i].arrival_time > processes[j].arrival_time) || 
                (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority > processes[j].priority)) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to print the Gantt chart
void print_gantt_chart(Process *processes, int n) {
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].pid);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = malloc(n * sizeof(Process));

    // Input arrival times, CPU bursts, and priorities
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process IDs start from 1
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter CPU burst for Process %d: ", i + 1);
        scanf("%d", &processes[i].cpu_burst);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Sort processes by arrival time and priority
    sort_processes(processes, n);

    // Calculate times
    calculate_times(processes, n);

    // Print Gantt chart
    print_gantt_chart(processes, n);

    // Print process details
    printf("\nProcess ID\tArrival Time\tCPU Burst\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].cpu_burst,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    // Calculate and print average times
    float total_turnaround_time = 0, total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);

    free(processes);
    return 0;
}

