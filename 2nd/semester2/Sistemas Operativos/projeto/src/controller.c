#include "controller.h"
#include "controller_pipe.h"

struct controllerState {
    void *scheduller_data; //estrutura de dados usada em cada política de escalonamento (GQueue para FCFS; struct com hashTable [UID -> GQueue de processos] + GQueue de Users ativos)
    GList *running_list; // comandos em execucao (já em forma de lista orientado para o extra de ter programas concorrentes)
    int max_parallel; // numero máximo de comandos em paralelo
    SchedPolicy policy; // algoritmo de escalonamento utilizado
    int shutdown_requested; // essencial para o comando -s
    long shutdown_request_command_id; // guarda o command_id do runner que faz o shutdown request
};

struct rr {
    GHashTable *user_queues; //[UserID -> GQueue de Processos]
    GQueue *active_users; //GQueue de UserID
};

ControllerState* controller_create(int max_parallel,const char *policy) {
    ControllerState *ctrl = malloc(sizeof (struct controllerState));
    if (!ctrl) return NULL;

    ctrl->running_list = NULL;
    ctrl->max_parallel = max_parallel;
    ctrl->shutdown_requested = 0;
    ctrl->shutdown_request_command_id = -1;
    
    if (strcmp (policy,"RR") == 0) { 
        ctrl->policy = RR;
        ctrl->scheduller_data = create_RoundRobin_struct();
    } else if (strcmp(policy,"FCFS") == 0) {
        ctrl->policy = FCFS;
        ctrl->scheduller_data = g_queue_new();
    }

    return ctrl;
}

RoundRobin *create_RoundRobin_struct() {
    RoundRobin *data = malloc(sizeof (struct rr));
    if (!data) return NULL;

    //verificar alocações
    data->user_queues = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify) g_queue_free);
    data->active_users = g_queue_new();

    return data;
}

long controller_get_shutdown_request_command_id(ControllerState* ctrl) {
    return ctrl->shutdown_request_command_id;
}

int controller_get_shutdown_requested(ControllerState* ctrl) {
    return ctrl->shutdown_requested;
}

void controller_set_shutdown_requested (ControllerState* ctrl, long command_id) {
    ctrl->shutdown_requested = 1;
    ctrl->shutdown_request_command_id = command_id;
}

/*
Retornos:
    1 -> não há mais processos à espera de serem escalonados e a executarem
    0 -> ainda há processos a executar/por executar  
*/
int no_more_processes(ControllerState *ctrl) {
    if (!ctrl) return 1;

    if (ctrl->policy == FCFS) {
        GQueue *queue = ctrl->scheduller_data;

        return (g_queue_is_empty(queue) && g_list_length(ctrl->running_list) == 0) ? 1 : 0;
    }

    RoundRobin *data = ctrl->scheduller_data;
    return (g_queue_is_empty(data->active_users) && g_list_length(ctrl->running_list) == 0) ? 1 : 0;
}

Process* fcfs_select_next(ControllerState *ctrl) {
    if (!ctrl) return NULL;

    GQueue *queue = (GQueue *) ctrl->scheduller_data;

    if (g_queue_is_empty(queue))
        return NULL;

    return g_queue_pop_head(queue);
}

Process* rr_select_next(ControllerState *ctrl) {
    if (!ctrl) return NULL;

    RoundRobin *data = (RoundRobin *) ctrl->scheduller_data;

    while (!g_queue_is_empty(data->active_users)) {
        int *user_id = g_queue_pop_head(data->active_users);

        GQueue *processQueue = g_hash_table_lookup(data->user_queues, user_id);

        if (!processQueue || g_queue_is_empty(processQueue)) {
            continue; // tenta próximo user
        }

        Process *p = g_queue_pop_head(processQueue);

        if (!g_queue_is_empty(processQueue)) {
            g_queue_push_tail(data->active_users, user_id);
        }

        return p;
    }

    return NULL;
}

Process* scheduler_select_next(ControllerState *ctrl) {
    if (!ctrl) return NULL;

    switch (ctrl->policy) {
        case FCFS:
            return fcfs_select_next(ctrl);

        case RR:
            return rr_select_next(ctrl);

        default:
            return NULL;
    }
}

void controller_add_process(ControllerState *ctrl, int user_id,long command_id,const char *command) {
    if (!ctrl || !command) return;
    
    Process* p = process_create(command,user_id,command_id);
    if (!p) {
        perror("Failed to create process");
        return;
    }

    process_set_submit_time(p);
    process_set_state(p,SUBMITTED);

    if (ctrl->policy == FCFS) {
        GQueue *schedulled_queue = ctrl->scheduller_data;
        g_queue_push_tail(schedulled_queue, p);

    } else {
        RoundRobin *data = ctrl->scheduller_data;

        gpointer key = GINT_TO_POINTER(user_id);
        GQueue *queue = g_hash_table_lookup(data->user_queues, key);

        if (!queue) {
            queue = g_queue_new();
            g_hash_table_insert(data->user_queues, key, queue);

            g_queue_push_tail(data->active_users, key);
        }

        int was_empty = g_queue_is_empty(queue);

        g_queue_push_tail(queue, p);

        if (was_empty) {
            g_queue_push_tail(data->active_users, key);
        }
    }

}

void controller_parallel(ControllerState *ctrl) {
    if (!ctrl) return;

    int running = g_list_length(ctrl->running_list);
    int slots = ctrl->max_parallel - running;

    while (slots > 0) {
        Process *p = scheduler_select_next(ctrl);

        if (!p) break;

        process_set_state(p, EXECUTING);
        controller_send_to_runner(ctrl, p); // comunicação com o runner

        slots--;
    }
}

//função que adiciona informação ao buffer, manipulando o tamanho do mesmo
int append_buffer(char **buffer, ssize_t *size, ssize_t *used, const char *text) {
    //determina quanto caracteres vao ter de ser adicionados
    ssize_t len = strlen(text);

    //Verifica se tem tamamnho suficiente
    if (*used + len + 1 > *size) {
        //aumenta o tamanho e dá realloc
        while (*used + len + 1 > *size)
            *size *= 2;

        char *tmp = realloc(*buffer, *size);
        if (!tmp) return -1;

        *buffer = tmp;
    }

    //adiciona informação ao buffer
    memcpy(*buffer + *used, text, len);
    *used += len;
    (*buffer)[*used] = '\0';

    return 0;
}

// depois ele tera de enviar esta string pelo pipe o runner recebe e dá o write dela
void controller_list_commands(ControllerState *ctrl, long command_id) {
    if (!ctrl) return;

    ssize_t size = 1024;
    ssize_t used = 0;
    char *buffer = malloc(size);
    if (!buffer) return;

    buffer[0] = '\0';

    char line[128];

    // Executing
    append_buffer(&buffer, &size, &used, "---\nExecuting\n");

    for (GList *l = ctrl->running_list; l != NULL; l = l->next) {
        Process *p = l->data;

        snprintf(line, sizeof(line),
            "user-id %d - command-id %ld\n",
            process_get_user_id(p),
            process_get_command_id(p));

        append_buffer(&buffer, &size, &used, line);
    }

    // Scheduled
    append_buffer(&buffer, &size, &used, "---\nScheduled\n");

    if (ctrl->policy == FCFS) {
        fcfs_list(ctrl, &buffer, &size, &used);
    } else {
        rr_list(ctrl, &buffer, &size, &used);
    }

    controller_send_command_list(command_id, buffer, used); // comunicação com o runner
    free(buffer);
}

void fcfs_list(ControllerState *ctrl, char **buffer, ssize_t *size, ssize_t *used) {
    GQueue *queue = (GQueue *) ctrl->scheduller_data;
    char line[128];

    for (GList *l = queue->head; l != NULL; l = l->next) {
        Process *p = l->data;

        snprintf(line, sizeof(line),
            "user-id %d - command-id %ld\n",
            process_get_user_id(p),
            process_get_command_id(p));

        append_buffer(buffer, size, used, line);
    }
}

void rr_list(ControllerState *ctrl, char **buffer, ssize_t *size, ssize_t *used) {
    RoundRobin *data = (RoundRobin *) ctrl->scheduller_data;

    if (g_queue_is_empty(data->active_users))
        return;

    GList *users = g_list_copy(data->active_users->head);

    GHashTableIter iter;
    gpointer key, value;

    GHashTable *temp = g_hash_table_new(g_direct_hash, g_direct_equal);

    g_hash_table_iter_init(&iter, data->user_queues);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_hash_table_insert(temp, key, g_queue_copy(value));
    }

    int has_more = 1;
    char line[128];

    while (has_more) {
        has_more = 0;

        for (GList *u = users; u != NULL; u = u->next) {
            gpointer user_id = u->data;
            GQueue *q = g_hash_table_lookup(temp, user_id);

            if (q && !g_queue_is_empty(q)) {
                Process *p = g_queue_pop_head(q);

                snprintf(line, sizeof(line),
                    "user-id %d - command-id %ld\n",
                    process_get_user_id(p),
                    process_get_command_id(p));

                append_buffer(buffer, size, used, line);

                has_more = 1;
            }
        }
    }

    g_hash_table_iter_init(&iter, temp);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_queue_free(value);
    }

    g_list_free(users);
    g_hash_table_destroy(temp);
}

int controller_log_process(Process *p) {
    int fd = open(FILENAME,O_WRONLY | O_CREAT | O_APPEND,0600);
    if (fd < 0) {
        perror("controller log open failed");
        return 1;
    }

    double turnaround_time = process_get_turnaround_time(p);
    double response_time = process_get_response_time(p);
    
    char buffer[STRING_SIZE];
    int len = snprintf(buffer,sizeof(buffer),
        "user-id %d|command-id %ld|turnaround %.3f|response %.3f\n",
        process_get_user_id(p),
        process_get_command_id(p),
        turnaround_time,
        response_time
    );

    if (len < 0) {
        close(fd);
        return 1;
    }

    ssize_t bytes_written = write(fd,buffer,len);
    if (bytes_written < 0) {
        perror("controller log write failed");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

int controller_finish_process(ControllerState *ctrl,Process* p) {
    if (!ctrl || !p) return 1;

    // remove da running_list
    ctrl->running_list = g_list_remove(ctrl->running_list,p);
    
    // muda estado para FINISHED
    process_set_end_time(p);
    process_set_state(p, FINISHED);

   if (controller_log_process(p) != 0) {
       process_destroy(p);
       return 1;
   }

   process_destroy(p);
   return 0;
}

void controller_mark_finished(ControllerState *ctrl, long command_id) {
    if (!ctrl) return;

    for (GList *l = ctrl->running_list; l != NULL; l = l->next) {
        Process *p = l->data;

        if (process_get_command_id(p) == command_id) {
            controller_finish_process(ctrl, p);
            break;
        }
    }
}

void controller_send_to_runner(ControllerState *ctrl,Process *p) {
    if (!ctrl || !p) return;

    // marca o tempo da primeira execução
    process_set_first_run_time(p);

    // Adicina a lista de running
    ctrl->running_list = g_list_append(ctrl->running_list,p);

    // envia o EXECUTE no fifo individual do runner
    controller_send_execute(process_get_command_id(p));
}

void free_RoundRobin_struct(RoundRobin *data) {
    if (!data) return;

    g_hash_table_destroy(data->user_queues);
    g_queue_free(data->active_users);

    free(data);
}

void controller_destroy(ControllerState *ctrl) {
    if (!ctrl) return;

   if (ctrl->policy == FCFS) {
        GQueue *queue = (GQueue *) ctrl->scheduller_data;
        g_queue_free_full(queue, (GDestroyNotify) process_destroy);
   } else {
        free_RoundRobin_struct((RoundRobin *) ctrl->scheduller_data);
   }

    g_list_free_full(ctrl->running_list, (GDestroyNotify) process_destroy);
    free(ctrl);
}