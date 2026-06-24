#include "aeronaves.h"
#include "parser_dados.h"
#include "validacao_sintatica_dados.h"
#include "utils.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

struct fabricante {
    GList *lista_aeronaves;
    GHashTable *by_airplane_id;
};

struct aeronaves {
    GHashTable *by_manufacturer; // manufacturer → struct fabricante*
    GHashTable *by_identifier; // id → Aeronave*
};

Aeronaves *aeronaves_create() {
    Aeronaves *aeronaves = malloc (sizeof (struct aeronaves));
    if (!aeronaves) return NULL;

    aeronaves->by_manufacturer = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_fabricante);
    aeronaves->by_identifier   = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    return aeronaves;
}

void aeronaves_add(void *objeto, void *colecao) {
    if (!objeto || !colecao)
        return;

    Aeronave *aircraft = objeto;
    Aeronaves *aircrafts = colecao;

    const char *manufacturer = get_aircraft_manufactor(aircraft);
    Fabricante *fab = g_hash_table_lookup(aircrafts->by_manufacturer, manufacturer);

    if (!fab) {
        fab = malloc(sizeof(struct fabricante));
        fab->lista_aeronaves = NULL;
        fab->by_airplane_id = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
        g_hash_table_insert(aircrafts->by_manufacturer, g_strdup(manufacturer), fab);
    }

    fab->lista_aeronaves = g_list_prepend(fab->lista_aeronaves, aircraft);
    g_hash_table_insert(fab->by_airplane_id, g_strdup(get_aircraft_identifier(aircraft)), aircraft);
    g_hash_table_insert(aircrafts->by_identifier, g_strdup(get_aircraft_identifier(aircraft)), aircraft);
}

int aeronaves_is_initialized(Aeronaves *gestor) {
    return (gestor != NULL && gestor->by_manufacturer != NULL);
}

GHashTable *aeronaves_get_all_manufacturers(Aeronaves *gestor) {
    if (!gestor || !gestor->by_manufacturer)
        return NULL;

    return gestor->by_manufacturer;
}

GHashTable *aeronaves_get_airplane_id(Fabricante *fab) {
    if (!fab || !fab->by_airplane_id)
        return NULL;

    return fab->by_airplane_id;
}

GList *aeronaves_get_airplane_list(Fabricante *fab) {
    if (!fab || !fab->lista_aeronaves) 
        return NULL;
    
    return fab->lista_aeronaves;
}

GList *aeronaves_get_by_manufacturer(Aeronaves *gestor, const char *manufacturer) {
    if (!gestor || !manufacturer) 
        return NULL;
    
    Fabricante *fab = g_hash_table_lookup(gestor->by_manufacturer, manufacturer);
    if (!fab) return NULL;
    
    return aeronaves_get_airplane_list (fab);
}

Aeronave *aeronaves_get_by_id(Aeronaves *gestor, const char *id) {
    if (!gestor || !id ) 
        return NULL;
    
    return g_hash_table_lookup(gestor->by_identifier, id);
}

void free_fabricante(void *fab_ptr) {
    if (!fab_ptr) return;

    Fabricante *fab = (Fabricante*)fab_ptr;

    g_list_free_full(fab->lista_aeronaves, free_aeronave);

    if (fab->by_airplane_id != NULL) 
        g_hash_table_destroy(fab->by_airplane_id);

    free(fab);
}

void aeronaves_free(Aeronaves *gestor) {
    if (!gestor) return;

    if (gestor->by_manufacturer != NULL) 
        g_hash_table_destroy(gestor->by_manufacturer);

    if (gestor->by_identifier != NULL) 
        g_hash_table_destroy(gestor->by_identifier);

    free(gestor);
}

void aeronaves_ordena_listas(Aeronaves *gestor) {
    if (!gestor || !gestor->by_manufacturer) return;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor->by_manufacturer);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Fabricante *fab = (Fabricante*)value;
        fab->lista_aeronaves = g_list_sort(fab->lista_aeronaves, aeronaves_compare_flight_count);
    }
}

void aeronaves_load(const char *dir,Aeronaves *gestor) {
    const char *path_aircrafts_load = get_ficheiro_dados(dir,"aircrafts");
    if (!path_aircrafts_load) return;

    char path_aircrafts_erros[256];
    snprintf (path_aircrafts_erros, sizeof (path_aircrafts_erros), "resultados/aircrafts_errors.%s",strrchr(path_aircrafts_load, '.') + 1);

    cria_colecao_do_csv(
        path_aircrafts_load,
        path_aircrafts_erros,
        validacao_sintatica_aeronave,
        NULL,
        (void* (*)(const gchar**)) cria_aeronave,
        (void (*)(void*, void*)) aeronaves_add,
        free_aeronave,
        gestor
    );
}
