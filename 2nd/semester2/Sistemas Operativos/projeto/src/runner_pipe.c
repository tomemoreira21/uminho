#include "runner_pipe.h"

// enviar pedido ao controller (FIFO global)
int runner_send_request(Message *msg,int global_fifo_fd) {
    ssize_t bytes_written = write(global_fifo_fd, msg, sizeof(Message));

    if (bytes_written != sizeof(Message)) {
        return 1;
    }

    return 0;
}

// cria o fifo individual do processo
int runner_create_fifo(long command_id) {
    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    if (mkfifo(fifo_name, 0666) == -1) {
        return 1;
    }

    return 0;
}

// abre o fifo individual e fica à espera da mensagem de execute
int runner_wait_execute(long command_id) {
    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fd = open(fifo_name, O_RDONLY);
    if (fd < 0) return 1;

    Message msg;
    ssize_t bytes_read = read(fd, &msg, sizeof(Message));

    if (bytes_read != sizeof(Message)) {
        close(fd);
        return 1;
    }

    close(fd);
    unlink(fifo_name); 

    return (msg.type == MSG_EXECUTE) ? 0 : 1;
}

// fica simplesmente à espera que o controller feche o FIFO global, e dessa forma indica que terminou
int runner_wait_controller_shutdown(long command_id) {
    char buffer[14];

    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fd = open(fifo_name, O_RDONLY);
    if (fd < 0) {
        unlink(fifo_name);
        return 1;
    }

    if (read(fd, &buffer, sizeof(buffer)) <= 0 || strcmp(buffer, "SHUTDOWN_DONE") != 0) {
        close(fd);
        unlink(fifo_name);
        return 1;
    } 

    close(fd);
    unlink(fifo_name);
    return 0;
}

// envia a informação que terminou de executar
int runner_send_finish(long command_id,int global_fifo_fd) {
    Message msg = build_finished(command_id);
    
    ssize_t bytes_written = write(global_fifo_fd,&msg,sizeof(Message));
    if (bytes_written != sizeof(Message)) {
        return 1;
    }

    return 0;
}

int runner_send_list_request(long command_id, int global_fifo_fd) {
    Message msg = build_status(command_id);

    if (write(global_fifo_fd, &msg, sizeof(Message)) != sizeof(Message)) {
        return 1;
    } 

    return 0;
}

int runner_send_shutdown_request(long command_id, int global_fifo_fd) {
    Message msg = build_shutdown(command_id);
    ssize_t bytes_written = write(global_fifo_fd, &msg, sizeof(Message));

    if (bytes_written != sizeof(Message)) {
        return 1;
    }

    return 0;
}

int runner_receive_command_list(long command_id) {
    char buffer[1024];
    ssize_t bytes_read = -1;

    char fifo_name[BUFFER_SIZE];
    snprintf(fifo_name, sizeof(fifo_name), "../tmp/runner_%ld", command_id);

    int fd = open(fifo_name, O_RDONLY);
    if (fd < 0) 
        return 1;

    while((bytes_read = read(fd,&buffer,1024)) > 0) {
        write(1,&buffer,bytes_read);
    }

    close(fd);
    unlink(fifo_name);
    return bytes_read != -1 ? 0 : 1;
}
