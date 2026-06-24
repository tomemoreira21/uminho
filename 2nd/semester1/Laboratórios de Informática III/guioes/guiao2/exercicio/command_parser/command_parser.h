#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "deque.h"

typedef struct cmd {
    char* command;
    int* args; // NULL se não houver
    int nargs; // número de argumentos
} *Cmd;

void processCommand (Deque deque,Cmd cmd);
Cmd parseLine (char* line);
Cmd create_cmd ();
void destroy_cmd (Cmd cmd);
void processCommand_Push (Deque deque,Cmd cmd);
void processCommand_PushFront (Deque deque,Cmd cmd);
void processCommand_Pop (Deque deque);
void processCommand_PopFront (Deque deque);
void processCommand_Size (Deque deque);
void processCommand_Reverse (Deque deque);
void processCommand_Print (Deque deque);

#endif