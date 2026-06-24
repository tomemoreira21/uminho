#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

void regista_pesquisa(Msg msg) {
	int fd = open(LOG,O_CREAT | O_WRONLY | O_APPEND,0600);
	if (fd < 0) return;

	char buffer[SIZE];	
	ssize_t bytes_written = snprintf(buffer,sizeof(buffer),
				"proc = %d | num_requested = %d | num_occurs = %d\n",
				msg.pid,msg.needle,msg.occurrences);

	write(fd,buffer,bytes_written);
	close(fd);
}


int main (int argc, char * argv[]){
	init_vector();
	print_vector();

	mkfifo(SERVER,0600);
	int fd_server = open(SERVER,O_RDONLY);

	Msg msg;
	ssize_t bytes_read;
	
	while ((bytes_read = read(fd_server,&msg,sizeof(msg))) > 0) {
		pid_t fork_res;
		fork_res = fork();

		if (fork_res == 0) { 
			msg.occurrences = count_needle(msg.needle);

			char name_client[1024];
			snprintf(name_client,sizeof(name_client),"fifo_client_%d",msg.pid);

			int fd_client = open(name_client,O_WRONLY);
			if (fd_client != -1) {
				write(fd_client,&msg,sizeof(msg));
				close(fd_client);
			}

			regista_pesquisa(msg);
			_exit(0);
		}
	}


	close(fd_server);
	unlink(SERVER);

	return 0;
}