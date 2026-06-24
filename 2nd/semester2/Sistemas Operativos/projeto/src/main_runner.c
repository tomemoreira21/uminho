#include "runner.h"
#include "runner_pipe.h"
#include <string.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int global_fifo_fd = open (FIFO_PATH,O_WRONLY);
    if (global_fifo_fd < 0) {
        return 1;
    }

    if (strcmp(argv[1],"-e") == 0) {
        int user_id = atoi(argv[2]);
        char *command = argv[3];
        long command_id = getpid();

        // criar FIFO individual
        if (runner_create_fifo(command_id) != 0) {
            perror("mkfifo");
            return 1;
        }

        Message msg = build_request(user_id,command_id,command);
        
        // envia o pedido para o controller no global
        if (runner_send_request(&msg,global_fifo_fd) != 0) {
            perror("send request");
            free(command);
            return 1;
        }

        print_runner_status (command_id, SUBMITTED);

        // espera autorização para executar
        if (runner_wait_execute(command_id) != 0) {
            perror("wait execute");
            free(command);
            return 1;
        }
        
        // executa o processo
        if (runner_execute(command_id, command) != 0) {
            free(command);
            return 1;
        }

        // avisa que terminou
        if (runner_send_finish(command_id,global_fifo_fd) != 0) {
            perror("send finish");
        }
    } 
    
    else if (strcmp(argv[1],"-c") == 0) {
        long command_id = getpid();

        // criar FIFO individual
        if (runner_create_fifo(command_id) != 0) {
            perror("mkfifo");
            return 1;
        }

        if (runner_send_list_request(command_id,global_fifo_fd) != 0) {
            perror("list request");
            return 1;
        }

        if (runner_receive_command_list(command_id) != 0) {
            perror("receive list");
            return 1;
        }

    } 
    
    else if (strcmp(argv[1],"-s") == 0) {
        long command_id = getpid();

        //cria fifo individual para poder receber a informação que o controller terminou a execução
        if (runner_create_fifo(command_id) != 0) {
            perror("mkfifo");
            return 1;
        }

        print_runner_shutdown_status("sent shutdown notification");

        if (runner_send_shutdown_request(command_id, global_fifo_fd) != 0) {
            perror("shutdown request");
            return 1;
        }

        close(global_fifo_fd);

        print_runner_shutdown_status("waiting for controller to shutdown...");

        if (runner_wait_controller_shutdown(command_id) != 0) {
            perror("wait shutdown");
            return 1;
        }

        print_runner_shutdown_status("controller exited.");
    }

    return 0;
}