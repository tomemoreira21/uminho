#include <stdio.h>
#include "mysystem.h"

// fica limitado às execuções de 254 vezes
void controller_v1(int N, char** commands) {
	pid_t pids[3];

	for (int i = 0; i < 3; i++) {
		pid_t fork_res;
		fork_res = fork();		

		if (fork_res == 0) {
			int count = 0;
			int ret = mysystem(commands[i]);
			count++;

			while (ret > 0) {
				ret = mysystem(commands[i]);
				count++;
			}

			_exit(count);
		} else {
			pids[i] = fork_res;
		}
	}

	for (int i = 0; i < 3; i++) {
		int status;
		waitpid(pids[i],&status,0);
		if (WIFEXITED(status)) {
			printf("%s %d\n",commands[i],WEXITSTATUS(status));
		}
	}
}

// não fica limitado ao 254 mas é muito mais lenta
void controller_v2 (int N,char **commands) {
	int count[3] = {0};

	for (int i = 0; i < 3; i++) {
		int ret = 1;

		while (ret != 0) {
			pid_t fork_res;
			fork_res = fork();
			
			if (fork_res == 0) {
				int res = mysystem(commands[i]);
				_exit(res > 0 ? 1 : 0);

			} else {
				int status;
				wait(&status);
				
				if (WIFEXITED(status)) {
					ret = WEXITSTATUS(status);
					count[i]++;
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		printf("%s %d\n",commands[i],count[i]);
	}

}

void controller_v3(int N,char **commands) {
	int fildes[N][2];

	for (int i = 0; i < N; i++) {
		pipe(fildes[i]);

		pid_t fork_res;
		fork_res = fork();

		if (fork_res == 0) {
			close(fildes[i][0]);

			int count = 0;
			int ret = mysystem(commands[i]);
			count++;

			while (ret > 0) {
				ret = mysystem(commands[i]);
				count++;
			}

			write(fildes[i][1],&count,sizeof(count));
			close(fildes[i][1]);
			_exit(0);
		}
	}

	for (int i = 0; i < N; i++) {
		close(fildes[i][1]);

		int valor;
		read(fildes[i][0],&valor,sizeof(valor));

		printf("%s %d\n",commands[i],valor);

		close(fildes[i][0]);
	}

	for (int i = 0; i < N; i++) {
		wait(NULL);
	}
}



int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller_v3(N, commands);

	return 0;
}