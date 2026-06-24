#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <time.h>

#define SIZE 100000

int mycp (const char *path_origin,const char *path_dest) {
    int fd_origin = open (path_origin,O_RDONLY);
    if (fd_origin < 0) {
        perror("Erro ao abrir o ficheiro de origem");
        return -1;
    }

    int fd_dest = open (path_dest,O_WRONLY | O_CREAT | O_TRUNC,0600);
    if (fd_dest < 0) {
        perror("Erro ao abrir o ficheiro de destino");
        close(fd_origin);
        return -1;
    }

    int n_read_syscalls = 0;
    ssize_t bytes_read;
    char buffer[SIZE];

    while ((bytes_read = read(fd_origin,buffer,sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(fd_dest,buffer,bytes_read);
        n_read_syscalls++;

        if (bytes_read != bytes_written) {
            perror ("Bytes read e os bytes written são diferentes");
            return -1;
        }

    }

    close(fd_origin);
    close(fd_dest);
    return n_read_syscalls;
}

int main(int argc,char *argv[]) {
    struct timespec start,end;
    int nRead = -1;

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (argc == 3) {
        const char *pathOrigin = argv[1];
        const char *pathDest = argv[2];
        nRead = mycp(pathOrigin,pathDest);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Tempo (BUFFER_SIZE %d): %.6f s\n", SIZE,elapsed);
    printf("Nº read syscalls: %d\n",nRead);

    return 0;
}