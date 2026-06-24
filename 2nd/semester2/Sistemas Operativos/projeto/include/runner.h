#ifndef RUNNER_H
#define RUNNER_H

#include "process.h"
#include "parser.h"
#include <unistd.h>
#include <sys/wait.h>

void print_runner_status(long command_id,ProcessState s);
int execute_command(Command *cmd);
int execute_pipeline (Pipeline *cmds);
int runner_execute (long command_id,const char* command);
void print_runner_shutdown_status(const char *msg) ;

#endif