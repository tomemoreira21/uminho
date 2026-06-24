#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>

typedef enum processState {
    NONE, // ainda nao definido
    SUBMITTED, // na lista de escalonamento
    EXECUTING, // em execucao
    FINISHED
} ProcessState;

typedef struct process Process;

Process* process_create (const char *command,int user_id,long command_id);

const char* process_get_command(Process* p);
int process_get_user_id(Process* p);
long process_get_command_id (Process* p);
ProcessState process_get_state(Process* p);

struct timeval process_get_submit_time(Process *p);
struct timeval process_get_end_time(Process *p);
struct timeval process_get_first_run_time(Process *p);

void process_set_command (Process* p, char* command);
void process_set_state(Process* p, ProcessState state);
void process_set_user_id(Process* p,int user_id);
void process_set_command_id (Process* p,long command_id);
void process_set_pid (Process* p,pid_t pid);
void process_set_submit_time(Process *p);
void process_set_end_time(Process *p);
void process_set_first_run_time(Process *p);

double process_get_turnaround_time(Process *p);
double process_get_response_time(Process *p);

void process_destroy(Process* p);


#endif