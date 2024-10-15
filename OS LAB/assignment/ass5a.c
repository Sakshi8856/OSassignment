#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child Process (PID: %d) before nice: %d\n", getpid(), nice(0));

        // Set a higher priority (lower nice value)
        if (nice(-5) == -1) {
            perror("Failed to set nice value in child");
            exit(1);
        }

        printf("Child Process (PID: %d) after nice: %d\n", getpid(), nice(0));
        sleep(5); // Simulate some work
        printf("Child Process (PID: %d) is exiting.\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent Process (PID: %d) before nice: %d\n", getpid(), nice(0));
        sleep(2); // Give child time to run
        printf("Parent Process (PID: %d) is exiting.\n", getpid());
        exit(0);
    }

    return 0;
}

