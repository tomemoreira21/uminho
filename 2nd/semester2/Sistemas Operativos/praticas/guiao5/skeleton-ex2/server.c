#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){
	init_vector();
	print_vector();

	mkfifo(SERVER,0600);
	int fd_server = open(SERVER,O_RDONLY);

	ssize_t bytes_read;
	Msg msg;

	while (1) {
		while ((bytes_read = read(fd_server,&msg,sizeof(msg))) > 0) {
			msg.occurrences = count_needle(msg.needle);

			char name_client[1024];
			snprintf(name_client,sizeof(name_client),"fifo_client_%d",msg.pid);

			int fd_client = open(name_client,O_WRONLY);
			write(fd_client,&msg,sizeof(msg));

			close(fd_client);
		}	
	}
	
	close(fd_server);

	unlink(SERVER);

	return 0;
}