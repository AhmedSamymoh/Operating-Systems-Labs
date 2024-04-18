#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


#define  Green "\033[0;32m"
#define  Reset "\033[0m"
#define  White "\033[47m"
#define  Cyan "\033[1;36m"
#define  Blue "\033[1;34m"

int temp = 0;

void EchoInfo(){

    //┌──(user@host)-[~cDir]
    //└─$ 
    char *user = getenv("USER");

    char host[1024];
    if (gethostname(host, sizeof(host)) == -1) {
        perror("Error getting hostname");
    }
    
    char cDir[100];
    getcwd(cDir, 100);
    
    printf(Blue);
    printf("\n┌──(%s@%s)", user, host);

    printf("\033[1;92m");
    printf("[~%s] ", cDir);
    printf(Reset);

    printf(Blue);
    printf("\n└─");
    printf(Reset);

    printf("\033[1;92m");
    printf("$");
    printf(Reset);

}

int main(int argc , char ** argv){
    
    printf("\n\n");
    printf(Blue);
    printf(White);
    printf("\t Welcome to my picoShell \t");
    printf(Reset);
    printf("\n\n");


    while(1){
        char buf[100];

        EchoInfo();

        fgets(buf, 100, stdin);
        buf[strlen(buf) - 1] = '\0';

        if(strlen(buf) == 0){
            continue;
        }

        /*fork - create a child process*/
        int ret_pid = fork(); 

        if(ret_pid < 0){
            printf("Fork failed\n");
        }
        else if(ret_pid == 0){ // Child process

            char * newargv[] = {NULL};
            char * newenvp[] = {NULL};


            execve(buf, newargv , newenvp); 
            perror("execve");
            return -1;


        }else{// Parent process 

            int status;

            wait(&status);

            printf("\nChild Status: %d", WEXITSTATUS(status));   
            sleep(1);   
        }

    }



}

