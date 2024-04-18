#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h> //sleep()


int main(int argc , char ** argv){



    /*fork - create a child process*/
    int ret_pid = fork();

    if(ret_pid < 0){
        printf("Fork failed\n");
    }else if(ret_pid == 0){
        while (1)
        {
            char * newargv[] = {NULL};
            char * newenvp[] = {NULL};

            printf("I am the child process with Pid = %d \
            , My Parent Pid = %d\n", getpid() , getppid());
            execve("/usr/bin/ls", newargv , newenvp); 
        }
             
    }else{
        while(1){
            printf("I am the parent process with Pid = %d \
            , My child Pid  = %d\n", getpid() , ret_pid);
            sleep(1);

        }   
    }


}

