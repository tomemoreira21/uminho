#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int parsing (const char *command,char** args);
void destroy_array (char **args);
void execute(const char* command);


#define BUFFER 16