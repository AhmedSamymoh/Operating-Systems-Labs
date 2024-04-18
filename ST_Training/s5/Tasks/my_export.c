#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to export an environment variable
void export_variable(char *arg) {
    char *name = strtok(arg, "=");
    char *value = strtok(NULL, "=");
    
    if (name == NULL || value == NULL) {
        printf("Error: Invalid variable format\n");
        return;
    }
    
    // Set the environment variable using setenv
    if (setenv(name, value, 1) != 0) {
        printf("Error: Failed to export variable %s\n", name);
        return;
    }
    
    printf("Exported variable %s=%s\n", name, value);
    
    // Print the value of the variable from the environment
    char *env_value = getenv(name);
    if (env_value != NULL) {
        printf("Value of %s: %s\n", name, env_value);
    } else {
        printf("%s not found\n", name);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s variable=value\n", argv[0]);
        return 1;
    }
    
    export_variable(argv[1]);
    
    return 0;
}
