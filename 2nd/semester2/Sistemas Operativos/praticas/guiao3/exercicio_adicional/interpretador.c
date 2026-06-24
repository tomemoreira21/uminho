#include <stdio.h>
#include "interpretador.h"

static int count = 1;

// devolve 0 se não possui o "&", senão devolve 1
int parsing (const char *command,char** args) {
    int res = 0;

	char *cmd_copy = strdup(command);
	int argc = 0;

	char *token = strtok(cmd_copy, " ");

    while (token != NULL) {
        args[argc++] = strdup(token);
        token = strtok(NULL, " ");
    }

    if (argc > 0 && strcmp(args[argc - 1], "&") == 0) {
        res = 1;
        free(args[argc - 1]); // remove o &
        args[argc - 1] = NULL;
    } else {
        args[argc] = NULL; 
    }

    free(cmd_copy);
    return res;
}

void destroy_array (char **args) {
    for (int i = 0; args[i] != NULL; i++) 
            free(args[i]);
}

void execute(const char* command) { 
    char *args[BUFFER];
    int ret = parsing(command,args);

    char *command_copy = strdup(command);
    command_copy[strlen(command_copy) - 2] = '\0';

    pid_t fork_res;
    fork_res = fork();

    if (fork_res == 0) {
        printf ("[proc_%d] executing ...",getpid());
        execvp(args[0],args);
        _exit(1);
    } else {
        if (ret == 0) { // espera pois não possui "&"
            int status;
            pid_t exit_pid = wait(&status);
            if (WIFEXITED(status)) {
                printf("[proc_%d] process %d exited with value %d\n",getpid(),exit_pid,WEXITSTATUS(status));
            }
        } else {
            printf("[%d] %d running '%s' in background\n",count++,fork_res,command_copy);
        }
    }

    destroy_array(args);
} 



