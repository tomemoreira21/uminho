#include "controller.h"
#include "controller_pipe.h"
#include <string.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
    if (argc < 3) {
        return 1;
    }   

    int max_paralled = atoi(argv[1]);
    char *schedulled_policy = strdup(argv[2]);
    int finished = 0;

    ControllerState *ctrl = controller_create(max_paralled,schedulled_policy);
    if (!ctrl) {
        return 1;
    }

    // cria o fifo global
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        return 1;
    }

    int fifo_fd_read = open(FIFO_PATH, O_RDONLY);
    if (fifo_fd_read < 0) {
        return 1;
    }

    int fifo_fd_write = open(FIFO_PATH, O_WRONLY);
    if (fifo_fd_write < 0) {
        return 1;
    }

    while(!finished) {
        Message msg;
        if (controller_receive_message(fifo_fd_read,&msg) == 0) {

            switch (msg.type) {
                case MSG_SUBMIT:
                    if (!controller_get_shutdown_requested(ctrl))
                        controller_add_process(ctrl, msg.user_id, msg.command_id, msg.command);
                    break;

                case MSG_FINISHED:
                    controller_mark_finished(ctrl, msg.command_id);
                    break;

                case MSG_STATUS:
                    controller_list_commands(ctrl, msg.command_id);
                    break;

                case MSG_SHUTDOWN:
                    controller_set_shutdown_requested(ctrl,msg.command_id);
                    unlink(FIFO_PATH);
                    break;

                default:
                    break;
            }
        }

        controller_parallel(ctrl);

        if (controller_get_shutdown_requested(ctrl)) {
            if (no_more_processes(ctrl)) {
                controller_notifiy_runner_of_shutdown(controller_get_shutdown_request_command_id(ctrl));
                finished = 1;
            }
        }
    }

    close(fifo_fd_read);
    close(fifo_fd_write);
    
    free(schedulled_policy);
    controller_destroy(ctrl);

    return 0;
}