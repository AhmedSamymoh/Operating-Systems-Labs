#include <unistd.h>
#include <stdio.h>

/* from man execve
NAME
       execve - execute program

SYNOPSIS
       #include <unistd.h>

       int execve(const char *pathname, char *const argv[],
                  char *const envp[]);

*/

int main(int argc, char *argv[]){
    char * newargv[] = {NULL};
    char * newenvp[] = {NULL};

    if(argc < 2){
        printf("Usage: %s <file-to-exec>\n", argv[0]);
        return -1;
    } 
    printf("> %s\n", argv[1]);
    getchar();

    execve(argv[1], newargv , newenvp);   

    /*Error State*/
    printf("Error in > %s \n" , argv[1]);
    perror("execve");



}