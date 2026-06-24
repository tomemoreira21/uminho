
#define SERVER "fifo_server"
#define CLIENT "fifo_client"
#define LOG "ficheiro_regista.log"

typedef struct msg{
    int needle;
    int pid;
    int occurrences;
} Msg;