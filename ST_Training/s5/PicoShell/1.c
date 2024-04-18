#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define  Blue "\033[1;34m"
#define  Reset "\033[0m"

void Info() {
    char user[1024];
    char host[1024];
    char cDir[1024];

    if (getlogin_r(user, sizeof(user)) != 0) {
        perror("Error getting username");
        exit(EXIT_FAILURE);
    }

    if (gethostname(host, sizeof(host)) != 0) {
        perror("Error getting hostname");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cDir, sizeof(cDir)) == NULL) {
        perror("Error getting current directory");
        exit(EXIT_FAILURE);
    }

    printf(Blue);
    printf("\n┌──(%s@%s)", user, host);
    printf("\033[1;92m");
    printf("[~%s] ", cDir);
    printf(Reset);
    printf(Blue);
    printf("\n└─$ ");
    printf(Reset);
}


void Entry(){
    printf("\n\n");
    printf(Blue);
    printf("\t Welcome to my picoShell \t");
    printf(Reset);
    printf("\n\n");

}

int main(int argc , char ** argv) {

    Entry();

    while(1) {
        char buf[100];

        Info();

        fgets(buf, 100, stdin);
        buf[strlen(buf) - 1] = '\0';

        if(strlen(buf) == 0 || strlen(buf) == '\n' || strlen(buf) == '\t' || strlen(buf) ==' ' ){
            continue;
        }

        // Split the command into arguments
        char *token = strtok(buf, " ");
        char *args[3]; // Maximum of two arguments including the command
        int i = 0;
        while (token != NULL && i < 2) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check if the command is 'cd'
        if(strcmp(args[0], "cd") == 0) {
            // If no argument provided, change to home directory
            if (args[1] == NULL) {
                if (chdir(getenv("HOME")) != 0) {
                    perror("chdir");
                }
            } else {
                // Change to the specified directory
                if (chdir(args[1]) != 0) {
                    perror("chdir");
                }
            }
            continue;
        }

        /* fork - create a child process */
        pid_t pid = fork();

        if(pid < 0){
            perror("Fork failed");
        } else if(pid == 0){ // Child process
            execlp(buf, buf, (char *) NULL);
            perror("execve");
            return -1;
        } else { // Parent process
            int status;
            waitpid(pid, &status, 0);
            printf("\nChild Status: %d", WEXITSTATUS(status));
            sleep(1);
        }
    }

    return 0;
}
