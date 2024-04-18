#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


int main()
{        
    char* c_dir = getcwd(NULL,0);
    
    if(c_dir != NULL)
    {

        printf("%s\n",c_dir);
        free(c_dir);
    }
    else{
        perror("getcwd");
        return -1;
    }        
}