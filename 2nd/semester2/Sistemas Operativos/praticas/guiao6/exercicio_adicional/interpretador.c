#include <stdio.h>
#include "interpretador.h"

static int count = 1;

// devolve 0 se não possui o "&", senão devolve 1
int parsing (const char *command,Comando *cmd) {
    int res = 0;

	char *cmd_copy = strdup(command);
    char *ptr = cmd_copy;

	int argc = 0;
	char *token;

    while ((token = strsep(&ptr," ")) != NULL) {
        if (*token == '\0') continue;

        if (strcmp(token,"<") == 0) {
            token = strsep(&ptr," ");
            if (token) cmd->input_file = strdup(token);
        
        } else if (strcmp (token,">") == 0) {
            token = strsep(&ptr," ");
            if (token) cmd->output_file = strdup(token);

        } else if (strcmp (token,">>") == 0) {
            token = strsep(&ptr," ");
            if (token) {
                cmd->output_file = strdup(token);
                cmd->append = 1;
            }

        } else if (strcmp(token,"2>") == 0) {
            token = strsep(&ptr," ");
            if (token) cmd->error_file = strdup(token);

        } else if (strcmp(token,"2>>") == 0) {
            token = strsep(&ptr," ");
            if (token) {
                cmd->error_file = strdup(token);
                cmd->append = 1;
            }
        } else {
            cmd->argv[argc++] = strdup(token);
        }
    }

    if (argc > 0 && strcmp(cmd->argv[argc - 1], "&") == 0) {
        res = 1;
        free(cmd->argv[argc - 1]); // remove o &
        argc--;
    } 

    cmd->argv[argc] = NULL;
    cmd->argc = argc;

    free(cmd_copy);
    return res;
}

void destroy_array (char **args) {
    for (int i = 0; args[i] != NULL; i++) 
            free(args[i]);
}

void execute(const char* command) { 
    char *cmdline = strdup(command);
    cmdline[strcspn(cmdline, "\n")] = '\0';

    Comando cmd = {0};
    int ret = parsing(cmdline,&cmd);

    pid_t fork_res;
    fork_res = fork();

    if (fork_res == 0) {
        printf ("[proc_%d] executing ...",getpid());

        // STDIN
        if (cmd.input_file) {
            int fd = open(cmd.input_file,O_RDONLY);
            if (fd < 0) _exit(1);
            dup2(fd,0);
            close(fd);
        }

        // STDOUT
        if (cmd.output_file) {
            int fd;
            if (cmd.append) fd = open(cmd.output_file,O_CREAT | O_WRONLY | O_APPEND, 0600);
            else fd = open(cmd.output_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);

            if (fd < 0) _exit(1);
            dup2(fd,1);
            close(fd);
        }

        // STDERR
        if (cmd.error_file) {
            int fd;
            if (cmd.append) fd = open(cmd.error_file,O_CREAT | O_WRONLY | O_APPEND, 0600);
            else fd = open(cmd.error_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);

            if (fd < 0) _exit(1);
            dup2(fd,2);
            close(fd);
        }

        execvp(cmd.argv[0],cmd.argv);
        _exit(1);
    } else {
        if (ret == 0) { // espera pois não possui "&"
            int status;
            pid_t exit_pid = wait(&status);
            if (WIFEXITED(status)) {
                printf("[proc_%d] process %d exited with value %d\n",getpid(),exit_pid,WEXITSTATUS(status));
            }
        } else {
            printf("[%d] %d running in background\n",count++,fork_res);
        }
    }

    destroy_array(cmd.argv);
    free(cmdline);
} 



