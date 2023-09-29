#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
	// Child
        printf("I'm the child process with PID %d and my parent's PID is %d.\n", getpid(), getppid());

        char** cmd = &argv[1];
        execvp(cmd[0], cmd);

        // execvp return error
        perror("execvp");
        return EXIT_FAILURE;
    } else {
	//parent
        printf("I'm the parent process with PID %d.\n", getpid());

        wait(NULL);  // Wait for child process to finish

        printf("Child process finished executing.\n");
        return 0;
    }
}

