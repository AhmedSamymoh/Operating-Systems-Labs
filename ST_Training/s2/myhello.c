#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char * bf = "Linux is Fun\n";
	int count = strlen(bf);
	write(1,bf,count);

	int ret = open("./open_hello.txt" , O_WRONLY|O_CREAT);
	
	printf("FD is %d\n",ret);

	write(ret,bf,count);


	return 0;

}

