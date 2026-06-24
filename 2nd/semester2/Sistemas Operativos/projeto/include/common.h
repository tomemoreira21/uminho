#ifndef COMMON_H
#define COMMON_H

#define FIFO_PATH "../tmp/fifo_global" // utilizado para enviar os pedidos para o controller
#define BUFFER_SIZE 256
#define MAX_CMD 256

typedef enum {
    MSG_SUBMIT,    // pedir execução (-e)
    MSG_EXECUTE,   // controller envia para o runner autorizacao
    MSG_FINISHED,  // terminou execução
    MSG_STATUS,    // -c
    MSG_SHUTDOWN,   // -s
} MessageType;

typedef struct {
    MessageType type;
    int user_id;
    long command_id;
    char command[MAX_CMD];
} Message;

Message build_request(int user_id, long command_id, const char *command);
Message build_finished(long command_id);
Message build_execute();
Message build_status(long command_id);
Message build_shutdown(long commad_id);

#endif