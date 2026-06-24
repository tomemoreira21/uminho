#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "fifo"
#define SIZE 1024

int main() {
    int fifo_open = open(FIFO_NAME,O_RDONLY);
    
    char buffer[SIZE];

    ssize_t bytes_read;
    while ((bytes_read = read(fifo_open,buffer,sizeof(buffer))) > 0) {
        write(1,buffer,bytes_read);
    }

    close(fifo_open);
}