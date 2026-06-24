#include "reservas.h"
#include "voos.h"
#include "passageiros.h"
#include "parser_dados.h"
#include "query1.h"
#include "query4.h"
#include "query6.h"
#include "validacao_sintatica_dados.h"
#include "validacao_logica_dados.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

Reservas *reservas_create() {
    Reservas *gestor = g_hash_table_new_full (g_str_hash,g_str_equal,g_free,(GDestroyNotify)free_reserva);

    return gestor;
}

void reservas_add(void *objeto, void *colecao) {
    if (!objeto || !colecao)
        return;

    Reserva *reserva = objeto;
    GestorGlobal *g = colecao;
    Reservas *gestorReservas = get_gestor_Reservas(g);
    Passageiros *gestorPassageiros = get_gestor_Passageiros(g);
    Aeroportos *gestorAeroportos = get_gestor_Aeroportos(g);
    Voos *gestorVoos = get_gestor_Voos(g);
    TableSemAno *semAno_table = get_hashtable_query4(get_gestor_Queries(g));
    GHashTable *stats_nacionalidade = get_hashtable_query6(get_gestor_Queries(g));

    g_hash_table_insert(gestorReservas,g_strdup(get_reservation_document_number(reserva)),reserva);

    const char *doc = get_reservation_document_number(reserva);
    Passageiro *p = passageiros_get(gestorPassageiros,doc);
    if (!p) return;

    const char *nat = get_nationality(p);
    if (!nat || nat[0] == '\0') return;

    GPtrArray *flight_ids = get_flight_ids(reserva);                                 
    for (guint i = 0; i<flight_ids->len; i++) {
        const char *flight_id = flight_ids->pdata[i];
        const Voo *v = voos_get (gestorVoos,flight_id);
        VooStatus s = get_status(v);
        const char *dest = get_destination(v);
        
        if (s != CANCELLED) {
            incrementa_arrival_e_departure_count_na_coleção(gestorAeroportos,v);
            regista_nacionalidade (nat,dest,stats_nacionalidade);
        }

    }

    const char *flight_id = flight_ids->pdata[0];
    const Voo *v = voos_get (gestorVoos,flight_id);
    adicionaGasto(get_reservation_price(reserva),strdup(doc),v,semAno_table);
}

Reserva *reservas_get (Reservas *gestor, const char *id) {
    if (!gestor || !id) return NULL;

    return g_hash_table_lookup(gestor,id);
}

void reservas_free (Reservas *gestor) {
    if (gestor != NULL)
        g_hash_table_destroy(gestor);
}

void reservas_load(const char *dir, GestorGlobal *gestor) {
    const char *path_reservations_load = get_ficheiro_dados(dir,"reservations");
    if (!path_reservations_load) return;

    char path_reservations_erros[256];
    snprintf (path_reservations_erros, sizeof (path_reservations_erros), "resultados/reservations_errors.%s",strrchr(path_reservations_load, '.') + 1);
    
    cria_colecao_do_csv(
        path_reservations_load,
        path_reservations_erros,
        validacao_sintatica_reserva,
        valida_logica_reserva,
        (void* (*)(const gchar**)) cria_reserva,
        (void (*)(void*, void*)) reservas_add,
        free_reserva,
        gestor
    );
}

