#include "parser.h"

int parse_command (char *command,Command *cmd) {
    int argc = 0;
    char *token;    

    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->error_file = NULL;

    while ((token = strsep (&command," ")) != NULL) {
        if (*token == '\0') continue;

        if (strcmp(token,">") == 0) {
            token = strsep(&command," ");
            if (token) cmd->output_file = token;

        } else if (strcmp(token,"<") == 0) {
            token = strsep(&command," ");
            if (token) cmd->input_file = token;

        } else if (strcmp(token,"2>") == 0) {
            token = strsep(&command," ");
            if (token) cmd->error_file = token;

        } else {
            cmd->argv[argc++] = token;
        }
    }
    
    cmd->argv[argc] = NULL;
    return 0;
}

int parse_pipeline(char *command_str, Pipeline *pipeline) {
    pipeline->count = 0;
    char *token;

    while ((token = strsep(&command_str, "|")) != NULL) {
        if (*token == '\0') continue;

        if (pipeline->count >= BUFFER_SIZE) return -1;

        parse_command(token, &pipeline->commands[pipeline->count]);
        pipeline->count++;
    }

    return 0;
}

