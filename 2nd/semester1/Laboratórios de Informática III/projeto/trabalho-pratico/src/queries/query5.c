#include "query5.h"
#include "stdio.h"
#include "output.h"
#include "interativo.h"
#include "math.h"

/*
A ideia passa por ter uma hash table 
    chave: char* airline_name
    valor: struct com {total_atraso_min, n_voos}


No fim converter para um array (não há outra forma de fazer de outra forma pois só consegues calcular a media no fim de tudo estar carregado) que vai ser 
struct {
    char *airline;
    int n_flights;
    double avg_delay;
} AirlineResult;

ordenar o array com qsort apenas uma vez após dar o load

e depois quando pedir a query basta dar sempre o top N

*/

struct airlineDelay {
    long total_delay;
    int n_flights;
};

struct airlineStat {
    char *airline;
    int n_flights;
    double avg_delay; 
};

struct airlineResult {
    AirlineStat *airline_results; // array de AirlineStat
    int size; // tamanho do array
};

GHashTable *airlines_create() {
    GHashTable *airline_table = g_hash_table_new_full (g_str_hash,g_str_equal,g_free,g_free);
    
    return airline_table;
}

AirlineResult *airlines_result_create() {
    AirlineResult *r = malloc (sizeof (struct airlineResult));

    r->airline_results = NULL;
    r->size = 0;

    return r;
}

const char *get_airline_name (AirlineStat *a) {
    return a->airline;
}

int get_airline_flights (AirlineStat *a) {
    return a->n_flights;
}

double get_airline_avg_delay (AirlineStat *a) {
    return a->avg_delay;
}

void airlines_add_delay (const char *airline_name, long delay_minutes,GHashTable *airline_table) {
    if (!airline_table || !airline_name) 
        return;

    AirlineDelay *stats = g_hash_table_lookup (airline_table,airline_name);

    if (!stats) {
        stats = calloc(1, sizeof(struct airlineDelay)); // cria a estrutura e inicia ambos com 0
        g_hash_table_insert(airline_table, g_strdup(airline_name), stats);
    }

    stats->total_delay += delay_minutes;
    stats->n_flights++;
}

// mede a diferença em minutos entre duas datas
long diff_minutes(GDateTime *end, GDateTime *start) {
    GTimeSpan diff = g_date_time_difference(end, start); // g_date_time_difference devolve microsegundos

    return diff / (60 * G_TIME_SPAN_SECOND); // converte microsegundos em minutos
}

/*
Ordena o array:
    1.média de atraso DESC
    2.nome alfabético ASC (em caso de empate)
*/
int cmp_airline(const void *a, const void *b) {
    const AirlineStat *x = a;
    const AirlineStat *y = b;

    if (x->avg_delay < y->avg_delay) return 1;
    if (x->avg_delay > y->avg_delay) return -1;

    return strcmp(x->airline, y->airline);
}

// Função que constroi o array de resultados ordenado
void build_airline_results(GHashTable *airline_table,AirlineResult *r) {
    if (!airline_table) return;

    if (r->airline_results != NULL) // evita ordenar novamente, ordena apenas uma vez no início
        return;

    r->size = g_hash_table_size (airline_table);
    r->airline_results = calloc (r->size,sizeof(struct airlineStat));

    GHashTableIter iter;
    gpointer key, value;
    int idx = 0;

    g_hash_table_iter_init(&iter, airline_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *airline_name = (char*)key;
        AirlineDelay *stats = (AirlineDelay*)value;

        r->airline_results[idx].airline = airline_name; // aponta diretamente para a string da hash table
        r->airline_results[idx].n_flights = stats->n_flights;
        double avg = (stats->n_flights > 0) ? ((double)stats->total_delay / stats->n_flights) : 0;

        avg = round(avg * 1000.0) / 1000.0; // arredonda para 3 casas decimais 

        r->airline_results[idx].avg_delay = avg;
        idx++;
    }

    qsort (r->airline_results ,r->size, sizeof (struct airlineStat),cmp_airline);
}

void query5_listar_companhias_mais_atrasos (int topN, char c,const char *output_file,AirlineResult *r) {
    int modo_interativo = (output_file == NULL);
    
    FILE *out = !modo_interativo ? fopen (output_file,"w") : NULL; // se não existir o ficheiro txt ele cria-o
    if (!out && !modo_interativo)
        return;

     if (!r || !r->airline_results) {
        if (!modo_interativo) fclose(out);
        return;
    }

    GList *lista_interativa = NULL;

    if (topN > r->size)
        topN = r->size;

    for (int i = 0; i < topN; i++) {
        if (modo_interativo) {
            lista_interativa = g_list_append(lista_interativa,&r->airline_results[i]);
        } else {
            char buffer_count_flights[32],buffer_count_avgdelay[32];

            sprintf (buffer_count_flights,"%d",r->airline_results[i].n_flights); // necessário para converter para string
            sprintf (buffer_count_avgdelay,"%.3f",r->airline_results[i].avg_delay); // necessário para converter para string
        
            output_fields(out,c,3,
                r->airline_results[i].airline,
                buffer_count_flights,
                buffer_count_avgdelay
            );
        }
    }

    if (!modo_interativo) 
        fclose(out);
    else {
        output_interativo_query5(lista_interativa,topN);
        g_list_free(lista_interativa);
    }
}

void free_airlines(GHashTable *airline_table,AirlineResult *r) {
    if (airline_table != NULL) {
        g_hash_table_destroy(airline_table);
    }

    if (r != NULL) {
        if (r->airline_results != NULL) {
            free(r->airline_results);
        }
        free(r);
    }
}