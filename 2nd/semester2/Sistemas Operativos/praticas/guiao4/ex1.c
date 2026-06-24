#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc,char *argv[]) {
    int fildes[2];
    __pid_t fork_res;
    pipe(fildes);

    fork_res = fork();

    if (fork_res == 0) {
        close(fildes[1]);

        int num_received;
        read(fildes[0],&num_received,sizeof(num_received));
        printf("[proc_%d] (filho) received num = %d\n",getpid(),num_received);

        close(fildes[0]);
        _exit(0);
    } else {
        close(fildes[0]);
        
        int num = 40;

        sleep(5);
        write(fildes[1],&num,sizeof(num));
        
        close(fildes[1]);

        int status;
        wait(&status);
        if (WIFEXITED(status)) 
            printf("[proc_%d] o processo pai terminou, status = %d\n",getpid(),WEXITSTATUS(status));
    }


    return 0;
}