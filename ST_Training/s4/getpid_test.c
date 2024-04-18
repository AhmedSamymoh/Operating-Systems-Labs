#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(){
	printf("\ngetpid = %d , get ppid = %d\n",getpid(),getppid());

}

