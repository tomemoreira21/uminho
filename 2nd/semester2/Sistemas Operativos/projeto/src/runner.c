#include "runner.h"
#include "runner_pipe.h"

int execute_command(Command *cmd) {
    // STDIN >
    if (cmd->input_file) {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd < 0) _exit(1);
        dup2(fd,0);
        close(fd);
    } 

    // STDOUT >
    if (cmd->output_file) {
        int fd = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
        if (fd < 0) _exit(1);
        dup2(fd,1);
        close(fd);
    }   

    // STDERR 2>
    if (cmd->error_file) {
        int fd = open(cmd->error_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
        if (fd < 0) _exit(1);
        dup2(fd,2);
        close(fd);
    }

	execvp(cmd->argv[0], cmd->argv);

	return 1;
}

int execute_pipeline (Pipeline *cmds) {
    int number_of_commands = cmds->count;
    int fides[number_of_commands-1][2];

    for (int c = 0; c < number_of_commands; c++) {
        if (c < number_of_commands - 1)
            if (pipe(fides[c]) < 0) _exit(1);

        pid_t pid = fork();
        if (pid < 0) _exit(1);
        if (pid == 0) {
            if (c < number_of_commands - 1) {
                close(fides[c][0]);

                dup2(fides[c][1], 1);
                close(fides[c][1]);
            }
    
            if (c > 0) {
                dup2(fides[c-1][0],0);
                close(fides[c-1][0]);
            }

            _exit(execute_command(&(cmds->commands[c])));
        }

        if (c < number_of_commands - 1) close(fides[c][1]);
        if (c > 0) close(fides[c-1][0]);
    }

    for (int i = 0; i < number_of_commands; i++)
        wait(NULL);

    return 0;
}

int runner_execute (long command_id,const char* command) {  
    char *buffer = strdup(command);
    if (!buffer) return 1;

    Pipeline cmds;
    if (parse_pipeline(buffer, &cmds) != 0 || cmds.count == 0) {
        free(buffer);
        return 1;
    }

    pid_t fork_res = fork();
    if (fork_res < 0) {
        free(buffer);
        return 1;
    }

    if (fork_res == 0) {

        if (cmds.count == 1)  _exit(execute_command(&(cmds.commands[0])));
        else _exit(execute_pipeline(&cmds));
        _exit(1);

    } else {
        print_runner_status(command_id,EXECUTING);

        int status;
        int failed = 0;

        if (waitpid(fork_res,&status,0) < 0) {
            free(buffer);
            return 1;
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            failed = 1;
        }

        print_runner_status(command_id,FINISHED);

        if (failed) {
            free(buffer);
            return 1;
        }
    }

    free(buffer);
    return 0;
}

void print_runner_status(long command_id,ProcessState s) {
    char buffer[BUFFER_SIZE];
    int len;

    if (s == EXECUTING) {
        len = snprintf(buffer,sizeof(buffer),"[runner] executing command %ld...\n",
                    command_id);
    } else {
        len = snprintf(buffer,sizeof(buffer),"[runner] command %ld %s\n",
            command_id,(s == SUBMITTED) ? "submitted" : "finished");
    }

    write(1,buffer,len);
}

void print_runner_shutdown_status(const char *msg) {
    char buffer[BUFFER_SIZE];
    int len = snprintf(buffer, sizeof(buffer), "[runner] %s\n", msg);
    write(1, buffer, len);
}