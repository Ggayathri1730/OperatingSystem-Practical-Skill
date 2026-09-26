#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    char command[100];
    printf("===== MY MINI SHELL =====\n");
    while (1) {
        printf("myshell> ");
        fflush(stdout);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';
        // Exit
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }
        // cd
        if (strncmp(command, "cd ", 3) == 0) {
            if (chdir(command + 3) != 0) {
                perror("cd");
            }
            continue;
        }
        //Create child process for other commands
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            // Execute command
            execl("/bin/sh", "sh", "-c", command, NULL);
            perror("Command failed");
            exit(1);
        }
        // Parent waits for child
        waitpid(pid, NULL, 0);
    }
    return 0;
}
