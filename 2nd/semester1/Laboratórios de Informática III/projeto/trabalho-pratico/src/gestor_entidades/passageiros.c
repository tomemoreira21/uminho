#include "passageiros.h"
#include "parser_dados.h"
#include "validacao_sintatica_dados.h"
#include <stdlib.h>
#include <stdio.h>

Passageiros *passageiros_create() {
    Passageiros *gestor = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,(GDestroyNotify)free_passageiro); 
    
    return gestor;
}

void passageiros_add(void *objeto, void *colecao) {
    if (!objeto || !colecao)
        return;

    Passageiro *passageiro = objeto;
    Passageiros *gestorPassageiros = colecao;

    g_hash_table_insert(gestorPassageiros, g_strdup(get_passenger_number(passageiro)), passageiro);
}

Passageiro *passageiros_get(Passageiros *gestor, const char *document_number) {
    if (!gestor || !document_number)
        return NULL;

    return g_hash_table_lookup(gestor, document_number);
}

void passageiros_free(Passageiros *gestor) {
    if (gestor != NULL)
        g_hash_table_destroy(gestor);

}

void passageiros_load(const char *dir, Passageiros *gestor) {
    const char *path_passengers_load = get_ficheiro_dados(dir,"passengers");
    if (!path_passengers_load) return;

    char path_passengers_erros[256];
    snprintf (path_passengers_erros, sizeof (path_passengers_erros), "resultados/passengers_errors.%s",strrchr(path_passengers_load, '.') + 1);

    cria_colecao_do_csv(
        path_passengers_load,
        path_passengers_erros,
        validacao_sintatica_passageiro,
        NULL,
        (void* (*)(const gchar**)) cria_passageiro,
        (void (*)(void*, void*)) passageiros_add,
        free_passageiro,
        gestor
    );
}
