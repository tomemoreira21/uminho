#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// processo filho está num estado zombie quando o processo filho termina primeiro que o pai
// processo filho fica orfão quando o pai termina primeiro do que ele sendo adotado pelo PID = 1, o pid de init

int main (int argc,char *argv[]) {
    pid_t fork_res;

    fork_res = fork();
    printf ("[proc-%d] apos fork, fork_res = %d\n",getpid(),fork_res);

    if (fork_res == 0) {
        // child process
        printf ("[proc-%d] (filho) PPID=%d\n",getpid(),getppid());
        sleep(10);
        printf ("[proc-%d] (filho) PPID=%d\n",getpid(),getppid());
        _exit(0); // termina a sua execução aqui e não vai dar o print do vou terminar (dá este valor no WEXITSTATUS)
    } else {
        // parent process
        printf ("[proc-%d] (pai) PPID=%d, filho = %d\n",getpid(),getppid(),fork_res);
        int status;
        pid_t exit_pid = wait (&status);
        if (WIFEXITED(status)) {
            printf ("[proc-%d] (pai) - filho %d terminou corretamente com o valor %d\n",getpid(),exit_pid,WEXITSTATUS(status));
        } else {
            printf ("[proc-%d] (pai) - filho %d não terminou corretamente\n",getpid(),exit_pid);
        }

    }

    printf ("[proc-%d] Vou terminar...\n",getpid());
}