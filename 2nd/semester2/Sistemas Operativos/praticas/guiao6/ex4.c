#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1024

// cat file.txt | wc -> cat vai escrever no pipe, wc vai ler

int main () {
    int fildes[2];
    pipe(fildes);

    pid_t fork_res;
    fork_res = fork();

    if (fork_res == 0) {
        // executa o wc
        close(fildes[1]);

        dup2(fildes[0],0);
        close(fildes[0]);

        execlp("wc","wc",NULL);
        _exit(1);
    } else {
        close(fildes[0]);
        
        ssize_t bytes_read;
        char buffer[SIZE];  
        int i = 0;

        while ((bytes_read = read(0,buffer,SIZE)) > 0) {
            write(fildes[1],buffer,bytes_read);
            i++;
        }
        
        close(fildes[1]);
        wait(NULL);
    }

    return 0;
}