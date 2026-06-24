#include "command_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void processCommand_Push (Deque deque,Cmd cmd) {
    for (int i = 0; i < cmd->nargs; i++) {
        int* val = malloc(sizeof(int)); 
        *val = cmd->args[i];            
        push(deque, val);
    }
}

void processCommand_PushFront (Deque deque,Cmd cmd) {
    for (int i = 0; i < cmd->nargs; i++) {
        int* val = malloc(sizeof(int)); 
        *val = cmd->args[i];            
        pushFront (deque,val);
    }
}

void processCommand_Pop (Deque deque) {
    int *v = pop (deque);

    if (v == NULL) printf ("EMPTY\n");
    else printf ("%d\n",*v);
}

void processCommand_PopFront (Deque deque) {
    int *v = popFront (deque);

    if (v == NULL) printf ("EMPTY\n");
    else printf ("%d\n",*v);
}

void processCommand_Size (Deque deque) {
    int v = size (deque);
    printf ("%d\n",v);
}

void processCommand_Reverse (Deque deque) {
    reverse (deque);
}

void processCommand_Print (Deque deque) {
    printDeque (deque,printFunc);
}

void processCommand (Deque deque,Cmd cmd) {
    if (strcmp (cmd->command,"PUSH") == 0) processCommand_Push (deque,cmd);
    else if (strcmp (cmd->command,"PUSH_FRONT") == 0) processCommand_PushFront (deque,cmd);
    else if (strcmp (cmd->command,"POP") == 0) processCommand_Pop (deque);
    else if (strcmp (cmd->command,"POP_FRONT") == 0) processCommand_PopFront (deque);
    else if (strcmp (cmd->command,"SIZE") == 0) processCommand_Size (deque);
    else if (strcmp (cmd->command,"REVERSE") == 0) processCommand_Reverse (deque);
    else if (strcmp (cmd->command,"PRINT") == 0) processCommand_Print (deque);
}
 
Cmd create_cmd () {
    Cmd cmd = malloc (sizeof (struct cmd));
    cmd->args = NULL;
    cmd->command = NULL;
    cmd->nargs = 0;

    return cmd;
}

Cmd parseLine (char* line) {
    Cmd cmd = create_cmd ();
    char* token = strsep (&line," ");

    if (token != NULL) {
        cmd->command = strdup (token);
        cmd->command[strcspn(cmd->command, "\n")] = '\0'; // remove o \n do final colocando \0
    }

    int capacity = 10;
    cmd->args = malloc (capacity * sizeof (int));

    token = strsep (&line," ");
    int i = 0;

    while (token != NULL) {
        if (i >= capacity) {
            capacity *= 2;
            cmd->args = realloc (cmd->args,capacity * sizeof (int));
        }
        
        cmd->args[i++] = atoi (token); 
        token = strsep (&line," ");
    }

    cmd->nargs = i;
    return cmd;
}

void destroy_cmd (Cmd cmd) {
    free (cmd->command);
    free (cmd->args);
    free (cmd);
}
