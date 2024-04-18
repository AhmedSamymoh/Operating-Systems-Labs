#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <unistd.h> //sleep()



/*
> ps -ef | grep forkDemo    : to see the process tree
> kill -9 <pid>             : to kill the process

> ps -lt pts/0              : to see the process tree in a tree format 
                                pts/0 is the terminal
*/


int main(){

    printf("My old pid is %d\n", getpid());

    getchar();

    /*fork - create a child process*/
    int ret_pid = fork();

    if(ret_pid < 0){
        printf("Fork failed\n");
    }else if(ret_pid == 0){
        printf("I am the child process with Pid = %d , My Parent Pid = %d\n", getpid() , getppid());
        
    }else{
        printf("I am the parent process with Pid = %d , My child Pid = %d\n", getpid() , ret_pid);
        sleep(5);
        printf("Parent Woke up\n");
    }


}

