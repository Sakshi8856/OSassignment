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
        printf("Child Process (PID: %d) is going to sleep for 10 seconds.\n", getpid());
        sleep(10); // Sleep for 10 seconds
        printf("Child Process (PID: %d) is awake and exiting now.\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent Process (PID: %d) is going to exit now.\n", getpid());
        exit(0); // Parent process exits
    }

    return 0;
}

