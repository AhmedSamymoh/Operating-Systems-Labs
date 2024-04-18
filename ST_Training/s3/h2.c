#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*!gcc --- > last gcc you called */

#define RET     0
//also could wrote as int main(int argc , char * argv[])
int main(int argc , char ** argv){
 
    printf("argc = %d \n" , argc);
    for (int i = 0; i < argc; i++)
    {
      printf("argv[%d] = %s \n" , i , argv[i]);
    }
    


   return RET;
}






























    // char * buf = "Linux is Fun !\n";
    // int len = strlen(buf);
    
    // int fd = open("./open.txt" , O_WRONLY | O_CREAT );


    // write(fd,buf , len);
    // printf("fd = %d \n" , fd);
    // write(1,"Done File Wrote :) \n" , strlen("Done File Wrote :) \n"));
    
    