#ifndef CONTROLLER_PIPE_H
#define CONTROLLER_PIPE_H

#include "common.h"
#include <unistd.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int controller_receive_message(int fd, Message *msg);
int controller_send_execute(long command_id);
int controller_send_command_list(long command_id, char* buffer, ssize_t size);
int controller_notifiy_runner_of_shutdown(long command_id);
#endif