#ifndef RUNNER_PIPE_H
#define RUNNER_PIPE_H

#include "common.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int runner_send_request(Message *msg,int global_fifo_fd);
int runner_wait_execute(long command_id);
int runner_create_fifo(long command_id);
int runner_send_finish(long command_id,int global_fifo_fd);
int runner_send_list_request(long command_id, int global_fifo_fd);
int runner_receive_command_list(long command_id);
int runner_wait_controller_shutdown(long command_id);
int runner_send_shutdown_request(long command_id, int global_fifo_fd);

#endif