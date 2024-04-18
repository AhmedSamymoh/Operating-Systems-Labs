/*My_cd*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 1024


void ExportError(char error[])
{
        perror(error);
        usleep(1000);
}



void cdCommand(char *argv[])
{
// Pointer to the target directory
    char *curDirection;
    char prevDirection[MAX_LENGTH], direction[MAX_LENGTH], tempDirection[MAX_LENGTH];

    if((!argv[1]) || (!strcmp(argv[1], "~")))
    {
        curDirection = getenv("HOME");
    }

    
    else if(!strcmp(argv[1], "-")) 
    {

        memcpy(direction, prevDirection, sizeof(prevDirection));
        curDirection = direction;
    }
    else
    {
    // Set the target directory to the provided argument
            curDirection = argv[1];
    }
    
    // Change the current working directory to the target directory
    getcwd(tempDirection, sizeof(tempDirection));

    if(chdir(curDirection))
    {
    // If changing directory fails, export an error message
            perror("cd");
            return;
    }
    
    // Store the current working directory as the previous directory
    memcpy(prevDirection, tempDirection, sizeof(tempDirection));
}

int main(int argc, char *argv[]) {
    // Execute the 'cd' command
    cdCommand(argv);

    return 0;
}
