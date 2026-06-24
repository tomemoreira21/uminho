#include "aeroportos.h"
#include "query3.h"
#include "parser_dados.h"
#include "validacao_sintatica_dados.h"
#include <stdlib.h>
#include <stdio.h>

Aeroportos* aeroportos_create() {
    Aeroportos *gestor = g_hash_table_new_full(g_str_hash, g_str_equal,g_free,(GDestroyNotify)free_airport);

    return gestor;
}

/*
Casos de Devolução:
    0 -> se conseguiu inserir o aeroporto na hash_table
    1 -> caso contrário
*/
void aeroportos_add (void *objeto, void *colecao) {
    if (!objeto || !colecao) 
        return;

    Aeroporto *airport = objeto;
    Aeroportos *gestorAeroportos = colecao;

    g_hash_table_insert(gestorAeroportos, g_strdup(get_airport_code(airport)), airport);
}

Aeroporto *aeroportos_get(Aeroportos *gestor, const char *code) {
    if (!gestor || !code) 
        return NULL;

    return g_hash_table_lookup(gestor, code);
}

void aeroportos_free(Aeroportos *gestor) {
    if (gestor != NULL) 
        g_hash_table_destroy(gestor);
}

void incrementa_departure_count_na_coleção (Aeroportos *gestor, const char *code) {
    Aeroporto *airport  = g_hash_table_lookup(gestor, code);
    if (airport == NULL) return;

    incrementa_departure_count(airport);
}

void incrementa_arrival_count_na_coleção (Aeroportos *gestor, const char *code) {
    Aeroporto *airport  = g_hash_table_lookup(gestor, code);
    if (airport == NULL) return;

    incrementa_arrival_count(airport);
}

void aeroportos_load(const char *dir, Aeroportos *gestor) {
    const char *path_airports_load = get_ficheiro_dados(dir,"airports");
    if (!path_airports_load) return;

    char path_airports_erros[256];
    snprintf (path_airports_erros, sizeof (path_airports_erros), "resultados/airports_errors.%s",strrchr(path_airports_load, '.') + 1);

    cria_colecao_do_csv(
        path_airports_load,
        path_airports_erros,
        validacao_sintatica_aeroporto,
        NULL,
        (void* (*)(const gchar**)) cria_aeroporto,
        (void (*)(void*, void*)) aeroportos_add,
        free_airport,
        gestor
    );
}


