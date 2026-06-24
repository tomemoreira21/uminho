#include <stdio.h>
#include "interpretador.h"

int main () {
    int exit = 0;

    while (!exit) {
        printf("> ");
        fflush(stdout);

        char command[BUFFER];
        ssize_t bytes_read = read(0,command,BUFFER);

        if (bytes_read == 0) {
            printf("CRTL+D detected ...\n");
            break;
        }

        if (bytes_read > 0 && command[bytes_read - 1] == '\n') {
            command[bytes_read - 1] = '\0';
        }   

        if (strcmp (command, "exit") == 0) 
            exit = 1;
        else 
            execute(command);
        }

    return 0;
}