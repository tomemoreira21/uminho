#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <sys/wait.h>

// ls /etc | wc -l -> ls /etc conteudo vai para o pipe escrito, e o wc -l é sobre o conteudo que está no pipe
/*
Nunca devo executar no pai algum destes comandos,
pois assim fico sem controlo do pai, pois o código é todo substituido
pelo execlp
*/

int main() {
    int fildes[2];
    pipe(fildes);

    pid_t p1;
    p1 = fork();

    if (p1 == 0) {
        close(fildes[0]);

        dup2(fildes[1],1);
        close(fildes[1]);

        execlp("ls","ls","/etc",NULL);
        _exit(1);
    } 

    close(fildes[1]);

    pid_t p2;
    p2 = fork();

    if (p2 == 0) {
        close(fildes[1]);

        dup2(fildes[0],0);
        close(fildes[0]);

        execlp("wc","wc","-l",NULL);
        _exit(1);
    }

    close(fildes[0]);
    
    wait(NULL);
    wait(NULL);

    return 0;
}