#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int main (int argc,char *argv[]) {
    for (int i = 0; i < N; i++) {
        pid_t fork_res;

        fork_res = fork();
        if (fork_res == 0) {
            printf ("[proc-%d] (filho) PPID = %d submitted\n",getpid(),getppid());
            sleep(2);
            _exit(i);
        }
    }

    for (int i = 0; i < 10; i++) {
        int status;
        pid_t exit_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf ("[proc-%d] (pai) - filho %d terminou corretamente com o valor %d\n",getpid(),exit_pid,WEXITSTATUS(status));
        } else {
            printf ("[proc-%d] (pai) - filho %d não terminou corretamente\n",getpid(),exit_pid);
        }
    }

    return 0;
}