#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RET     0

/*cp source dist
  1   2     3

  argc = 3
*/

// fd : is abbreviation for file descriptor :)

int main(int argc , char * argv[]){
    char buf[100];
 
    printf("argc = %d \n" , argc);
    for (int i = 0; i < argc; i++)
    {
      printf("argv[%d] = %s \n" , i , argv[i]);
    }


    if(argc != 3)
	    return -1;


    int fd1 = open(argv[1] , O_RDONLY ); //source
    int fd2 = open(argv[2] , O_WRONLY | O_CREAT ); //dist

    int count = read(fd1 , buf , 100); // 100 is the size of buffer
    write(fd2 , buf , count);//write to dist until count
    close(fd1);
    close(fd2);

   return RET;
}

