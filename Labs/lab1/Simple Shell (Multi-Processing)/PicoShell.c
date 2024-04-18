#include "PicoShell.h"


/*******************************************************************************
 * @brief Display user, host, and current directory information in a custom prompt format.
 *******************************************************************************/
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

/*******************************************************************************
 * @brief Display welcome message for PicoShell.
 *******************************************************************************/
void Entry(){
    printf("\n\n");
    printf(Blue);
    printf("\t Welcome to my picoShell \t");
    printf(Reset);
    printf("\n\n");
}


/*******************************************************************************
 * @brief Tokenize the input string into arguments.
 * 
 * @param input The input string to be parsed.
 * @param args The array to store parsed arguments.
 *******************************************************************************/
void parseInput(char *input, char **args) {
    // Tokenize the input string
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

/*******************************************************************************
 * @brief Execute a command with or without background execution.
 * 
 * @param args The array of command arguments.
 * @param background Flag indicating whether the command should be executed in the background.
 *******************************************************************************/
void executeCommand(char **args, int background) {
    /* Fork a child process */
    pid_t pid = fork();
    /*Child process*/
    if (pid == 0) { 
        if (background) {
            freopen("/dev/null", "r", stdin);
        }
        execvp(args[0], args);
        
        perror("execvp");
        exit(EXIT_FAILURE);

    } else if (pid < 0) { 
        perror("fork");
    } else { 
        /* Parent process */
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[%d]\n", pid); 
        }
    }
}

/*******************************************************************************
 * @brief Main function of PicoShell.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Returns 0 on successful execution.
 *******************************************************************************/
int main(int argc, char **argv) {
    Entry();

    log_file = fopen("shell_log.txt", "a");
    if (log_file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /*  Register signal handler for SIGCHLD */
    signal(SIGCHLD, on_child_exit);

    while (1) {
        Info();

        char buf[100];
        fgets(buf, 100, stdin);
        buf[strlen(buf) - 1] = '\0'; 

        if (strlen(buf) == 0) continue;

        char *args[20];
        parseInput(buf, args);

        
        /* Check built-in Commands */
        if (strcmp(args[0], "exit") == 0) {
            // Terminate the shell !!!!
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            cdCommand(args);
        } else if (strcmp(args[0], "echo") == 0) {
            echoCommand(argc, args);
        } else if (strcmp(args[0], "export") == 0) {
            exportVariable(args[1]);
        } else if (strcmp(args[0], "pwd") == 0) {
            pwdCommand();
        } else {
            // Check if last argument '&'
            int background = 0;
            if (strcmp(args[argc - 1], "&") == 0) {
                background = 1;
                // Remove '&'
                args[argc - 1] = NULL;
            }
            executeCommand(args, background);

            
            if (background) {
                Info();
            }
        }
    }

    fclose(log_file);

    return 0;
}


/*******************************************************************************
 * @brief Change directory - Buit in - command.
 * 
 * @param argv Array of command arguments.
 *******************************************************************************/
static void cdCommand(char *argv[]) {
    char *curDirection;
    char prevDirection[1024], direction[1024], tempDirection[1024];

    if((!argv[1]) || (!strcmp(argv[1], "~"))) {
        curDirection = getenv("HOME");
    } else if(!strcmp(argv[1], "-")) {
        memcpy(direction, prevDirection, sizeof(prevDirection));
        curDirection = direction;
    } else {
        curDirection = argv[1];
    }

    getcwd(tempDirection, sizeof(tempDirection));

    if(chdir(curDirection)) {
        perror("cd");
        return;
    }

    memcpy(prevDirection, tempDirection, sizeof(tempDirection));
}

/*******************************************************************************
 * @brief Echo - Buit in - command.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command arguments.
 * @return Returns 0 on successful execution.
 *******************************************************************************/
static int echoCommand(unsigned long argc, char *argv[]) {
    unsigned char count = 1;
    int num_write = 0;
    char ch;
    while (argv[count] != NULL) {
        char *arg = argv[count];

        // Check if the argument is an environment variable
        if (arg[0] == '$') {
            char *env_value = getenv(arg + 1); // Skip the '$'
            if (env_value != NULL) {
                num_write = write(1, env_value, strlen(env_value));
                if (num_write == -1) {
                    return -1;
                }
            }
        } else {
            num_write = write(1, arg, strlen(arg));

            if (num_write == -1) {
                return -1;
            }
        }
        count++;
        if (count != argc) {
            num_write = write(1, " ", 1);
            if (num_write == -1) {
                return -1;
            }
        }
    }
    num_write = write(1, "\n", 1);
    return 0;
}

/*******************************************************************************
 * @brief Export variable - Buit in - command.
 * 
 * @param arg The argument to be exported.
 *******************************************************************************/
static void exportVariable(char *arg) {
    char *name = strtok(arg, "=");
    char *value = strtok(NULL, "=");

    if (name == NULL || value == NULL) {
        printf("Error: Invalid variable format\n");
        return;
    }

    // Set the environment variable using setenv
    if (setenv(name, value, 1) != 0) {
        printf("Error: Failed to export variable %s\n", name);
        return;
    }

    printf("Exported variable %s=%s\n", name, value);
}

/*******************************************************************************
 * @brief Print current working directory.
 *******************************************************************************/
static void pwdCommand() {
    char* c_dir = getcwd(NULL, 0);

    if(c_dir != NULL) {
        printf("%s\n", c_dir);
        free(c_dir);
    } else {
        perror("getcwd");
    }
}
/*******************************************************************************
 * @brief Handle child process exit.
 * 
 * @param signum Signal number.
 *******************************************************************************/
static void on_child_exit(int signum) {
    // Reap zombie processes
    while (waitpid(-1, NULL, WNOHANG) > 0);

    fprintf(log_file, "Child process was terminated\n");
}
