#include "common.h"
#include <string.h>

Message build_request(int user_id, long command_id, const char *command) {
    Message msg;

    msg.type = MSG_SUBMIT;
    msg.user_id = user_id;
    msg.command_id = command_id;

    strncpy(msg.command, command, MAX_CMD - 1);
    msg.command[MAX_CMD - 1] = '\0'; 

    return msg;
}

Message build_finished(long command_id) {
    Message msg = {0};

    msg.type = MSG_FINISHED;
    msg.command_id = command_id;

    return msg;
}

Message build_execute() {
    Message msg = {0};
    msg.type = MSG_EXECUTE;

    return msg;
}

Message build_status(long command_id) {
    Message msg = {0};
    msg.type = MSG_STATUS;
    msg.command_id = command_id;

    return msg;
}

Message build_shutdown(long command_id) {
    Message msg = {0};
    msg.type = MSG_SHUTDOWN;
    msg.command_id = command_id;

    return msg;
}
