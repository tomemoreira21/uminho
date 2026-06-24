#include "voos.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query5.h"
#include "parser_dados.h"
#include "validacao_sintatica_dados.h"
#include "validacao_logica_dados.h"
#include "aeronaves.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

Voos *voos_create() {
    Voos *gestor = g_hash_table_new_full (g_str_hash,g_str_equal,g_free,(GDestroyNotify)free_voo);

    return gestor;
}

void voos_add(void *objeto, void *colecao) {
    if (!objeto || !colecao)
        return;

    Voo *voo = objeto;
    GestorGlobal *g = colecao;
    Voos *gestorVoos = get_gestor_Voos(g);
    Aeronaves *gestorAeronaves = get_gestor_Aeronaves(g);
    GTree *btree_datas = get_btree_query3(get_gestor_Queries(g));
    GHashTable *airline_table = get_hashtable_query5(get_gestor_Queries(g));
    VooStatus status = get_status(voo);

    g_hash_table_insert(gestorVoos,g_strdup(get_flight_id(voo)),voo);

    if (status != CANCELLED) {
        incrementa_flight_count_da_aeronave(gestorAeronaves,voo);
        adicionar_voo_btree (voo,btree_datas);
    }

    if (status == DELAYED) {
        long atraso = diff_minutes (get_actual_departure(voo), get_departure(voo));
        airlines_add_delay (get_airline (voo),atraso,airline_table);
    }
}

Voo *voos_get (Voos *gestor, const char *id) {
    if (!gestor || !id) 
        return NULL;

    return g_hash_table_lookup (gestor,id);
}

void voos_free (Voos *gestor) {
    if (gestor != NULL )
        g_hash_table_destroy (gestor);
}

void voos_load(const char *dir,GestorGlobal *gestor) {
    const char *path_flights_load = get_ficheiro_dados(dir,"flights");
    if (!path_flights_load) return;

    char path_flights_erros[256];
    snprintf (path_flights_erros, sizeof (path_flights_erros), "resultados/flights_errors.%s",strrchr(path_flights_load, '.') + 1);

    cria_colecao_do_csv(
        path_flights_load,
        path_flights_erros,
        validacao_sintatica_voo,
        valida_logica_voo,
        (void* (*)(const gchar**)) cria_voo,
        (void (*)(void*, void*)) voos_add,
        free_voo,
        gestor
    );
}


