#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main () {
    pid_t fork_res;

    fork_res = fork();

    if (fork_res == 0) {
        printf ("[proc_%d] (filho) inicialize\n",getpid());
        char *args[3];
        args[0] = strdup("ls");
        args[1] = strdup("-l");
        args[2] = NULL;
        execvp(args[0],args);
    } else {
        int status;
        pid_t exit_pid = wait(&status);
        printf("[proc_%d] (pai) PID = %d exited\n",getpid(),exit_pid);
    }

    return 0;

}
