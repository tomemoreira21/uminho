#include "process.h"

struct process {
    char* command; // comando a executar
    ProcessState state;
    int user_id;
    long command_id;

    // necessárias para calcular o turnaround time de cada processo e o response time
    struct timeval submit_time;
    struct timeval first_run_time; 
    struct timeval end_time;

    int has_started; // flag para controlar o first_run_time
};

Process* process_create (const char *command,int user_id,long command_id) {
    Process* p = malloc (sizeof (struct process));
    if (!p) return NULL;

    p->command = strdup(command);
    p->state = NONE;
    p->user_id = user_id;
    p->command_id = command_id;
    p->has_started = 0;

    return p;
}

const char* process_get_command(Process* p) {
    return p->command;
}

int process_get_user_id(Process* p) {
    return p->user_id;
}

long process_get_command_id (Process* p) {
    return p->command_id;
}

ProcessState process_get_state(Process* p) {
    return p->state;
}

struct timeval process_get_submit_time(Process *p) {
    return p->submit_time;
}

struct timeval process_get_first_run_time(Process *p) {
    return p->first_run_time;
}

struct timeval process_get_end_time(Process *p) {
    return p->end_time;
}

void process_set_command (Process* p, char* command) {
    p->command = strdup(command);
}

void process_set_state(Process* p, ProcessState state) {
    p->state = state;
}

void process_set_user_id(Process* p,int user_id) {
    p->user_id = user_id;
}

void process_set_command_id (Process* p,long command_id) {
    p->command_id = command_id;
}

void process_set_submit_time(Process *p) {
    gettimeofday(&p->submit_time, NULL);
}

void process_set_first_run_time(Process *p) {
    if (!p->has_started) {
        gettimeofday(&p->first_run_time, NULL);
        p->has_started = 1;
    }
}

void process_set_end_time(Process *p) {
    gettimeofday(&p->end_time, NULL);
}

// calcula a duração em milissegundos
double process_get_turnaround_time(Process *p) {
    double submit = p->submit_time.tv_sec + p->submit_time.tv_usec / 1000000.0;
    double end = p->end_time.tv_sec + p->end_time.tv_usec / 1000000.0;

    return end - submit;
}

double process_get_response_time(Process *p) {
    double submit = p->submit_time.tv_sec + p->submit_time.tv_usec / 1000000.0;
    double first = p->first_run_time.tv_sec + p->first_run_time.tv_usec / 1000000.0;

    return first - submit;
}

void process_destroy(Process* p) {
    if (!p) return;

    free(p->command);
    free(p);
}
