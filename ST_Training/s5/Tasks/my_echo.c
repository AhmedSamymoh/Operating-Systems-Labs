#include "stdio.h"
#include <stdlib.h>
#include <string.h>

// External variable to access environment variables
extern char **environ;

int main(int argc, char **argv)
{
    int i = 0;
    if (argc > 1)
    {
        for (i = 1; i < argc; i++)
        {
            printf("%s", argv[i]);

            printf(" ");
        }

    }
    printf("\n");

    return 0;
}