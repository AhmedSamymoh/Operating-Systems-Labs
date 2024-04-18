#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*!gcc --- > last gcc you called */

#define RET     0

int main(){
    /*
    The Old Way
    printf("Linux is Fun !");
    */ 

    char * buf = "Linux is Fun !\n";
    int len = strlen(buf);
    
    int fd = open("./open.txt" , O_WRONLY | O_CREAT );


    write(fd,buf , len);
    printf("fd = %d \n" , fd);
    write(1,"Done File Wrote :) \n" , strlen("Done File Wrote :) \n"));
    
    
   return RET;
}
