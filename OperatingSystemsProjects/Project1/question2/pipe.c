#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);

        execlp("./sort", "./sort", (char *)NULL);
        perror("execlp"); 
        exit(EXIT_FAILURE);
    } else {       
        close(pipefd[0]);          
        dup2(pipefd[1], STDOUT_FILENO);

        execlp("./pre", "./pre", "arg1", "arg2", (char *)NULL);
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }
    return 0;
}


