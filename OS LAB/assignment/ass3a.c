#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        
        // Replace the child process with a new process (e.g., running the 'ls' command)
        execlp("ls", "ls", NULL);
        
        // If exec fails
        perror("exec failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent Process (PID: %d)\n", getpid());
        
        // Wait for the child process to terminate
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Child process terminated with exit status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not terminate normally.\n");
        }
    }

    return 0;
}

