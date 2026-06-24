#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int main (int argc,char *argv[]) {
    pid_t exits_pids[10] = {0};

    for (int i = 0; i < N; i++) {
        pid_t fork_res;

        fork_res = fork();
        if (fork_res == 0) {
            printf ("[proc-%d] (filho) PPID = %d submitted\n",getpid(),getppid());
            sleep(2);
            _exit(i);
        } else {
            exits_pids[i] = fork_res;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        int status;
        pid_t exit_pid = waitpid(exits_pids[i],&status,0);
        if (WIFEXITED(status)) {
            printf ("[proc-%d] (pai) - filho %d terminou corretamente com o valor %d\n",getpid(),exit_pid,WEXITSTATUS(status));
        } else {
            printf ("[proc-%d] (pai) - filho %d não terminou corretamente\n",getpid(),exit_pid);
        }
    }



    return 0;
}