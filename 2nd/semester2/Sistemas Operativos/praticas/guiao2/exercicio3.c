#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10


int main (int argc,char *argv[]) {

    for (int i = 0; i < N; i++) {
        pid_t fork_res;

        fork_res = fork();

        if (fork_res == 0) {
            // child process
            printf ("[proc-%d] (filho) PPID = %d\n",getpid(),getppid());
            sleep(2);
            _exit(i);
        } else {
            // parent process
            int status;
            pid_t exit_pid = waitpid(fork_res,&status,0);
            if (WIFEXITED(status)) {
                printf ("[proc-%d] (pai) - filho %d terminou corretamente com o valor %d\n",getpid(),exit_pid,WEXITSTATUS(status));
            } else {
                 printf ("[proc-%d] (pai) - filho %d não terminou corretamente\n",getpid(),exit_pid);
            }

        }
    }

    return 0;
}