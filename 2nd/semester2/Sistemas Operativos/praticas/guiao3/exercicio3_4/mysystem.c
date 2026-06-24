#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	int res = -1;

	// responsável por fazer o parsing para " "
	char *cmd_copy = strdup(command);
	char *args[BUFFER];
	int argc = 0;

	char *token = strtok(cmd_copy, " ");

    while (token != NULL) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }

    args[argc] = NULL;

	pid_t fork_res;
	fork_res = fork();
	if (fork_res == 0) {
		//printf ("[proc_%d] (filho) executing ...\n",getpid());
		int v = execvp(args[0],args);
		_exit(v);
	} else {
		int status;
		pid_t exit_pid = wait(&status);
		if (WIFEXITED(status)) {
			int valor = WEXITSTATUS(status);
			res = valor;
			//printf("[proc_%d] (pai) PID = %d exited\n",getpid(),exit_pid);
		}
	}

	free(cmd_copy);
	return res;
}