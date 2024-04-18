#ifndef _PICO_SHELL_H_
#define _PICO_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <signal.h>

#define  Green "\033[0;32m"
#define  Blue "\033[1;34m"
#define  Reset "\033[0m"

FILE *log_file;

/******************* Function prototypes *******************/ 
void Info(); 
void Entry();
void parseInput(char *input, char **args);
void executeCommand(char **args, int background);

static void cdCommand(char *argv[]);
static int echoCommand(unsigned long argc, char *argv[]);
static void exportVariable(char *arg);
static void pwdCommand();
static void on_child_exit(int signum) ;
/***********************************************************/ 


#endif