#include "controller_pipe.h"

// envia o execute no fifo individual
int controller_send_execute(long command_id) {
    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd < 0) {
        return 1;
    }

    Message msg = build_execute();
    ssize_t bytes_written = write(fifo_fd,&msg,sizeof(Message));

    if (bytes_written != sizeof(Message)) {
        close(fifo_fd);
        return 1;
    }

    close(fifo_fd);
    return 0;
}

int controller_receive_message(int fd, Message *msg) {
    ssize_t bytes_read = read(fd, msg, sizeof(Message));

    if (bytes_read <= 0)
        return 1;
        
    if (bytes_read != sizeof(Message))
        return 1;

    return 0;
}

int controller_send_command_list(long command_id, char* buffer, ssize_t size) {
    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd < 0) {
        return 1;
    }

    if (write(fifo_fd, buffer, size) != size) {
        close(fifo_fd);
        return 1;
    }

    close(fifo_fd);
    return 0;
}

int controller_notifiy_runner_of_shutdown(long command_id) {
    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd < 0) {
        return 1;
    }

    char buffer[14] = "SHUTDOWN_DONE";
    buffer[13] = '\0';
    if (write(fifo_fd, &buffer, sizeof(buffer)) != sizeof(buffer)) {
        close(fifo_fd);
        return 1;
    }

    close(fifo_fd);
    return 0;
}