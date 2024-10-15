#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    pid_t pid;

    // Fork a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child Process (PID: %d)\n", getpid());
        
        // Increase the priority of the child process
        if (nice(-5) == -1) { // Assigning higher priority
            perror("Failed to change priority");
            exit(1);
        }
        
        // Display new priority
        int new_priority = getpriority(PRIO_PROCESS, 0);
        printf("Child Process New Priority: %d\n", new_priority);
        
        // Simulate some work in the child process
        for (int i = 0; i < 5; i++) {
            printf("Child working... %d\n", i + 1);
            sleep(1); // Sleep to simulate work
        }
    } else {
        // Parent process
        printf("Parent Process (PID: %d)\n", getpid());
        
        // Display the parent priority
        int parent_priority = getpriority(PRIO_PROCESS, 0);
        printf("Parent Process Priority: %d\n", parent_priority);
        
        // Wait for child to finish
        wait(NULL);
    }

    return 0;
}

