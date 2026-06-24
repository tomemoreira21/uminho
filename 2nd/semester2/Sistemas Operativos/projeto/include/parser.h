#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

typedef struct {
    char *argv[BUFFER_SIZE];

    char *input_file;     // <
    char *output_file;    // >
    char *error_file;     // 2>
} Command;

typedef struct {
    Command commands[BUFFER_SIZE];
    int count;
} Pipeline;

int parse_command (char *command,Command *cmd);
int parse_pipeline(char *command_str, Pipeline *pipeline);

#endif