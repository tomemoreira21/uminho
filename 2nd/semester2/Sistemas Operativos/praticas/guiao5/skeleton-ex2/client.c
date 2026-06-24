#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){
	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	int fd_server = open(SERVER,O_WRONLY);

	Msg msg;
	msg.pid = getpid();
	msg.needle = atoi(argv[1]);
	msg.occurrences = 0;

	char name_client[1024];
	snprintf(name_client,sizeof(name_client),"fifo_client_%d",msg.pid);
	mkfifo(name_client,0600);

	write(fd_server,&msg,sizeof(msg));
	close(fd_server);	

	int fd_client = open(name_client,O_RDONLY);
	read(fd_client,&msg,sizeof(msg));

	printf("[proc_%d] num = %d ocorre %d vezes\n",msg.pid,msg.needle,msg.occurrences);

	close(fd_client);	
	unlink(name_client);
	return 0;
}