#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 20000

/*
ls | wc 

- | -> significa o pipe
- wc -> vai dar o numero de characteres ..., que o ls tem
*/

int main (int argc,char *argv[]) {
    int fildes[2];
    __pid_t fork_res;
    pipe(fildes);

    fork_res = fork();

    if (fork_res == 0) {
        close(fildes[0]);

        /*
        Se o filho tentar escrever mais dados do que o pipe pode armazenar 
        e o pai ainda não leu nada, o write() bloqueia.
        */
        for (int i = 0; i < N; i++) {
            write(fildes[1],&i,sizeof(i));
            printf ("[proc_%d] (filho) escreveu num = %d\n",getpid(),i);
        }
        
        close(fildes[1]);
        _exit(0);
    } else {
        close(fildes[1]);

        sleep(5);
        size_t bytes_read;
        int num_received, i = 0;

        while ((bytes_read = read(fildes[0],&num_received,sizeof(num_received))) > 0) {
            printf("numbers[%d] = %d\n",i++,num_received);
        }

        close(fildes[0]);

        int status;
        wait(&status);
        if (WIFEXITED(status)) 
            printf("[proc_%d] o processo pai terminou, status = %d\n",getpid(),WEXITSTATUS(status));
    }


    return 0;
}