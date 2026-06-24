#include "command_parser/command_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main (int argc,char **argv) {
    Deque deque = create ();

    size_t len;
    char *line = NULL;
    ssize_t read;

    if (argc < 2) {
        while ((read = getline (&line,&len,stdin)) != -1) {
            Cmd cmd = parseLine (line);
            processCommand (deque,cmd);
            destroy_cmd (cmd);
        }
        free (line);

    } else {
        FILE* fr = fopen (argv[1],"r");
    
        while ((read = getline (&line,&len,fr)) != -1) {
            Cmd cmd = parseLine (line);
            processCommand (deque,cmd);
            destroy_cmd (cmd);
        }
        free (line);
    }

    destroy (deque);
    return 0;
}
