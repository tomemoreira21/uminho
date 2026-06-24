#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

#define SIZE 1024

// CRTL + D -> terminar o programa corretamente
void mycat (const char *pathname) {
    int fd = (pathname == NULL) ? 0 : open (pathname,O_RDONLY);

    if (fd < 0) {
        perror("Erro ao abrir o ficheiro");
        return;
    }

    char buffer[SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read (fd,buffer,sizeof(buffer))) > 0) {    
        // escrever para o stdout
        ssize_t bytes_written = write(1,buffer,bytes_read);
    }

    if (fd != 0) close(fd);
}

int main(int argc,char* argv[]) {
    if (argc == 1) mycat(NULL);
    else {
        for (int i = 1; i < argc;i++) {
            mycat(argv[i]);
        }
    }

    return 0;
}