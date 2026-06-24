#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_COMMANDS 10

// parse the argument and execvp
// returns the result of exec
int exec_command(char *arg) {

	// We are assuming a maximum number of arguments of 10.
	// This could be improved with realloc, for example.
	char *exec_args[10];
	int args_count = 0;
	int exec_ret = 0;

	char *token, *string, *tofree;

	tofree = string = strdup(arg);
	assert(string != NULL);

	while ((token = strsep(&string, " ")) != NULL) {
		exec_args[args_count] = token;
		args_count++;
	}

	exec_args[args_count] = NULL;

	exec_ret = execvp(exec_args[0], exec_args);

	perror("Exec error");

	free(tofree);

	return exec_ret;
}

int main(int argc, char **argv) {

	int number_of_commands = 4;
	char *commands[] = {
		"grep system /etc/passwd",
		"wc -l",
		"uniq",
		"wc -l"};
	
	// grep system /etc/passwd | wc -l > out.txt
	int fildes[number_of_commands][2];
	for (int i = 0; i < number_of_commands; i++) {

		if (i < number_of_commands - 1) 
			pipe(fildes[i]);

		pid_t fork_res;
		fork_res = fork();

		if (fork_res == 0) {

			/* stdin vem do anterior
			  Muda o redericionamento de leitura para o fildes anterior
			*/
			if (i  > 0) {
				dup2(fildes[i-1][0],0);
				close(fildes[i-1][0]);
			}

			/* stdout vai par o próximo
			  Muda para escrever o redericionamento
			  E fecha o próprio de leitura
			*/
			if (i < number_of_commands - 1) {
				dup2(fildes[i][1],1);
				close(fildes[i][1]);
			}

			// fechar extremos que não vou usar
			if (i > 0) 
				close(fildes[i-1][1]); // não escreve no anterior

			if (i < number_of_commands - 1) 
				close(fildes[i][0]); // não vou sar para leitura, apenas para escrita

			int res = exec_command(commands[i]);
			_exit(res);			
		}

		// pai

		// já nao precisa do pipe anterior
		if (i > 0) 
			close(fildes[i-1][0]);

		// pai nunca escreve
		if (i < number_of_commands -1)
			close(fildes[i][1]);
	}

	for (int i = 0; i < number_of_commands; i++)
		wait(NULL);

	return 0;
}
