#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "fifo"
#define SIZE 1024

int main() {
    mkfifo(FIFO_NAME,0600);
    int fifo_open = open(FIFO_NAME,O_WRONLY);
    
    char buffer[SIZE];

    ssize_t bytes_read;
    while ((bytes_read = read(0,buffer,sizeof(buffer))) > 0) {
        write(fifo_open,buffer,bytes_read);
    }

    close(fifo_open);
    unlink(FIFO_NAME);
}