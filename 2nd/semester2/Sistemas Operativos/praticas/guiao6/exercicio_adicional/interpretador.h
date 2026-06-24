#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 1024

typedef struct {
    const char *error_file;
    const char *output_file;
    const char *input_file;
    int append;

    char *argv[SIZE];
    int argc;
} Comando;

int parsing(const char *command,Comando *cmd);
void destroy_array (char **args);
void execute(const char* command);


#define BUFFER 16