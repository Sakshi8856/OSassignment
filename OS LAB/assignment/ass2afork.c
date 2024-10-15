#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // This block is executed by the child process
        printf("Child Process: PID = %d\n", getpid());
        printf("Hello World\n");
    } else {
        // This block is executed by the parent process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Hi\n");
    }

    return 0;
}

