#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <glib.h>
#include "process.h"
#include <sys/types.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "../tmp/controller.log"
#define STRING_SIZE 128
#define BUFFER_SIZE 256

typedef enum schedulledPolicy {
    FCFS, // First-Come,First-Served
    RR // Round robin fairness entre users
} SchedPolicy;

typedef struct controllerState ControllerState;

typedef struct rr RoundRobin;

ControllerState* controller_create(int max_parallel,const char *policy);
RoundRobin *create_RoundRobin_struct();

long controller_get_shutdown_request_command_id(ControllerState* ctrl);
int controller_get_shutdown_requested(ControllerState* ctrl);
void controller_set_shutdown_requested (ControllerState* ctrl, long command_id);
int no_more_processes(ControllerState *ctrl);

Process* fcfs_select_next(ControllerState *ctrl);
Process* rr_select_next(ControllerState *ctrl);
Process* scheduler_select_next(ControllerState *ctrl);

void controller_add_process (ControllerState *ctrl, int user_id,long command_id,const char *command);
void controller_parallel(ControllerState *ctrl);
void controller_send_to_runner(ControllerState *ctrl,Process *p);
void controller_mark_finished(ControllerState *ctrl, long command_id);

void fcfs_list(ControllerState *ctrl, char **buffer, ssize_t *size, ssize_t *used);
void rr_list(ControllerState *ctrl, char **buffer, ssize_t *size, ssize_t *used);
void controller_list_commands(ControllerState *ctrl, long command_id);

int controller_finish_process(ControllerState *ctrl,Process* p);
int controller_log_process(Process *p);

void free_RoundRobin_struct(RoundRobin *data);
void controller_destroy(ControllerState *ctrl);

int append_buffer(char **buffer, ssize_t *size, ssize_t *used, const char *text);

#endif