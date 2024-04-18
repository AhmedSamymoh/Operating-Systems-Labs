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



int main(int argc , char ** argv){

    while(1){
        char buf[100];

        char cDir[100];
        getcwd(cDir, 100);
        printf("[~]%s $", cDir);


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

            printf("Child Status: %d\n", WEXITSTATUS(status));   
            sleep(1);   
        }

    }



}

