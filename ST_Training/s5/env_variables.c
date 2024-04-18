#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RET     0

extern char **environ;

int main(int argc , char ** argv){
 
    printf("argc = %d \n" , argc);
    for (int i = 0; i < argc; i++)
    {
      printf("argv[%d] = %s \n" , i , argv[i]);
    }
    
    for(int i = 0; environ[i] != NULL; i++){
        printf("env[%d] = %s \n" , i , environ[i]);
    }


   return RET;
}

