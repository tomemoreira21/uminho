#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1024

int main () {
    char buffer[SIZE];
    int original_stdout = dup(1);

    // input
    int fd_input = open("/etc/passwd",O_RDONLY);
    if (fd_input == -1) return -1;
    dup2(fd_input,0);
    close(fd_input);
    
    // output
    int fd_output = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd_output == -1) return -1;
    dup2(fd_output,1);
    close(fd_output);

    // error
    int fd_error = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd_error == -1) return -1;
    dup2(fd_error,2);
    close(fd_error);

    // vai ao input e faz o wc
    if (fork() == 0)  {
        execlp("wc","wc",NULL);
        _exit(0);
    }

    wait(NULL);

    dup2(original_stdout,1);
    close(original_stdout);

    printf("terminei\n");

    return 0;
}