#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <sys/wait.h>

// ls /etc | wc -l -> wc -l vai ser sobre o novo ls /etc
/*
Tem a questão que o processo pai
pode terminar de facto após o filho
*/
int main() {
    int fildes[2];  
    pipe(fildes);

    pid_t fork_res;
    fork_res = fork();

    if (fork_res == 0) {
        close(fildes[1]);

        dup2(fildes[0],0);
        close(fildes[0]);

        execlp("wc","wc","-l",NULL);
        _exit(1);
    } else {
        close(fildes[0]);

        dup2(fildes[1],1);
        close(fildes[1]);

        execlp("ls","ls","/etc",NULL);

        // código após execpl não deve estar bem
        //close(fildes[1]);
        //wait(NULL);
    }

    return 0;
}


