#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servico.h"
#include "cliente.h"
#include "../../../guiao1/deque/deque.h"
#include "../../../guiao1/deque/node.h"

struct servico {
    char *nome_servico;
    Deque fila;
};

// Getters
char* getNomeServico(Servico s) {
    return strdup(s->nome_servico); 
}

Fila getFilaServico(Servico s) {
    return s->fila;
}

// Setters
void setNomeServico(Servico s, const char *nome) {
    free(s->nome_servico);
    s->nome_servico = strdup(nome);
}

void setFilaServico(Servico s, Fila f) {
    s->fila = f;
}

// Funções gerais
Servico createServico(char *nomeServico) {
    Servico s = malloc(sizeof(struct servico));
    s->nome_servico = strdup(nomeServico);
    s->fila = malloc(sizeof(struct deque)); // alocar deque
    s->fila->front = NULL;
    s->fila->back = NULL;
    s->fila->size = 0;
    s->fila->printfFunc = NULL; // se não precisares de printFunc
    return s;
}

void insertClienteFila(Cliente c, Fila f) {
    int idade = getIdade(getDate(c));

    if (idade > 80)
        pushFront(f, (void*) c);
    else
        push(f, (void*) c);
}

