#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    char *argv[20], buf[80], n, *p;
    int m, status, inword, continu;

    while (1) {
        printf("\nshhh> ");
        fflush(stdout);

        inword = 0;
        p = buf;
        m = 0;
        continu = 0;

        while ((n = getchar()) != '\n' || continu) {
            if (n == ' ') {
                if (inword) {
                    inword = 0;
                    *p++ = 0;
                }
            } else if (n == '\n') continu = 0;
            else if (n == '\\' && !inword) continu = 1;
            else {
                if (!inword) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                } else *p++ = n;
            }
        }
        *p++ = 0;
        argv[m] = 0;

        if (strcmp(argv[0], "exit") == 0) exit(0);

        int pipes = 0;
        int input_redirection = 0;
        int output_redirection = 0;
        int input_fd, output_fd;

        for (int i = 0; argv[i] != NULL; i++) {
            if (argv[i] && strcmp(argv[i], "|") == 0)
                pipes++;
            if (argv[i] && strcmp(argv[i], "<") == 0) {
                input_redirection = 1;
                input_fd = open(argv[i + 1], O_RDONLY);
                if (input_fd < 0) {
                    perror("Failed to open input file");
                    exit(EXIT_FAILURE);
                }
                argv[i] = NULL;
                argv[i + 1] = NULL;
            }
            if (argv[i] && strcmp(argv[i], ">") == 0) {
                output_redirection = 1;
                output_fd = open(argv[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
                if (output_fd < 0) {
                    perror("Failed to open output file");
                    exit(EXIT_FAILURE);
                }
                argv[i] = NULL;
                argv[i + 1] = NULL;
            }

        }

        if (pipes == 0 && input_redirection == 0 && output_redirection == 0) {
            // Only one command, no pipes or redirections
            int pid = fork();

            if (pid == 0) {
                execvp(argv[0], argv);
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                exit(EXIT_FAILURE);
            }

            waitpid(pid, &status, 0);

        } else {
            int pfd[2 * pipes];

        for (int i = 0; i < pipes; i++) {
            if (pipe(pfd + i * 2) < 0) {
                exit(EXIT_FAILURE);
            }
        }

        int pid;
        int end = 0;

        while (argv[end] != NULL) {
            int start = end;
            while(argv[end] != NULL && strcmp(argv[end], "|") != 0) {
                end++;
            }

            argv[end] = NULL;

            pid = fork();

            if (pid == 0) {
                if (start != 0) {
                    // Read from the pipe connected to the previous command
                    dup2(pfd[(start - 1) * 2], STDIN_FILENO);
                } else if (input_redirection) {
                    // First command in the pipeline, and there's input redirection
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                }

                if (argv[end + 1] != NULL) {
                    // There's a command after this one, so send output to the next pipe
                    dup2(pfd[start * 2 + 1], STDOUT_FILENO);
                } else if (output_redirection) {
                    // Last command in the pipeline, and there's output redirection
                    dup2(output_fd, STDOUT_FILENO);
                    close(output_fd);
                }

                // Close all pipe descriptors after duplication
                for (int j = 0; j < 2 * pipes; j++)
                    close(pfd[j]);

                execvp(argv[start], &argv[start]);
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                exit(EXIT_FAILURE);
            }

            if (input_redirection && start == 0) {
                close(input_fd);
                input_redirection = 0;
            }

            if (output_redirection && argv[end + 1] == NULL) {
                close(output_fd);
                output_redirection = 0;
            }

            end++;
        }

        // Close pipe descriptors in the parent process
        for (int i = 0; i < 2 * pipes; i++)
            close(pfd[i]);

        // Wait for child processes to terminate
        while (wait(NULL) > 0);
        }
    }
    return 0;
}