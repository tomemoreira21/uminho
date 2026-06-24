#include "query6.h"
#include "output.h"
#include "interativo.h"
#include "stdio.h"

/*
Ter uma hash table
    key = nationality (string)
    value = struct {
        destinations: hash_table <IATA, count>
        best_iata: string
        best_count: int
    }

A ideia é ter a nacionalidade como key tendo dentro de cada nacionalidade outra hash table com o code IATA e count,
e para alem disso ir atualizando best_iata e o best_count de forma a que no fim não tenha de percorrer a hash table
interna e basta dar o best_iata,best_count

*/

struct nacionalidadeInfo {
    GHashTable *dest_counts; // key = char* IATA, value = int*
    char *best_iata;
    int best_count;
};

GHashTable *stats_nacionalidade_create() {
    GHashTable *stats_nacionalidade = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,(GDestroyNotify)free_nacionalidade_info);

    return stats_nacionalidade;
}

NacionalidadeInfo *nacionalidade_info_new() {
    NacionalidadeInfo *info = malloc(sizeof(NacionalidadeInfo));

    info->dest_counts = g_hash_table_new_full(g_str_hash, g_str_equal,g_free, free);

    info->best_iata = NULL;
    info->best_count = 0;

    return info;
}

int get_nacionalidade_best_count (NacionalidadeInfo *info) {
    return info->best_count;
}

const char *get_nacionalidade_best_iata (NacionalidadeInfo *info) {
    return info->best_iata;
}

void incrementa_destino(NacionalidadeInfo *info,const char *code) {
    int *count = g_hash_table_lookup(info->dest_counts, code);

    if (!count) {
        count = malloc(sizeof(int));
        *count = 1;
        g_hash_table_insert(info->dest_counts, g_strdup(code), count);
    } else {
        (*count)++;
    }

    if (*count > info->best_count || 
        (*count == info->best_count && strcmp (code,info->best_iata) < 0)) {
            info->best_count = *count; 
            free(info->best_iata);
            info->best_iata = g_strdup(code);
        }
}

void regista_nacionalidade(const char *nat,const char *dest,GHashTable *stats_nacionalidade) {
     if (!nat || !dest) return;

    NacionalidadeInfo *info = g_hash_table_lookup(stats_nacionalidade, nat);
    if (!info) {
        info = nacionalidade_info_new();
        g_hash_table_insert(stats_nacionalidade, g_strdup(nat), info);
    }

    incrementa_destino(info, dest);
}

void query6_aeroporto_destino(const char *nationality, char c, const char *output_file,GHashTable *stats_nacionalidade) {
    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen(output_file, "w") : NULL;
    if (!out && !modo_interativo)
        return;

    NacionalidadeInfo *info = g_hash_table_lookup(stats_nacionalidade,nationality);

    if (!info || info->best_count == 0) {
        if (!modo_interativo)
            fprintf(out, "\n");
        else 
            output_interativo_nacionalidade(info,nationality);
    } else {
        if (modo_interativo) {
           output_interativo_nacionalidade(info,nationality);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",info->best_count); // necessário para converter para string

            output_fields(out,c,2,info->best_iata,buffer_count);
        }
    }

    if (!modo_interativo) fclose(out);
}

void free_nacionalidade_info(NacionalidadeInfo *info) {
    if (!info) return;

    g_hash_table_destroy(info->dest_counts);
    free(info->best_iata);
    free(info);
}

void free_stats_nacionalidade(GHashTable *stats_nacionalidade) {
    if (stats_nacionalidade != NULL) {
        g_hash_table_destroy(stats_nacionalidade);
        stats_nacionalidade = NULL;
    }
}