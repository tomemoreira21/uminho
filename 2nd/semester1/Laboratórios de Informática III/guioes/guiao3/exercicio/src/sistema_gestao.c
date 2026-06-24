#include <stdio.h>
#include <stdlib.h>
#include "sistema_gestao.h"
#include "balcao.h"
#include "cliente.h"
#include <string.h>
#include "../../../guiao1/deque/deque.h"

struct nodeB {
    Balcao balcao;
    struct nodeB *prox;
};

struct sistema {
    int size;          // número atual de buckets
    int totalBalcoes;         // número de balcoes disponiveis
    NodeB *table;  // array de listas
};

int getSistemaSize(Sistema s) {
    return s->size;
}

int getSistemaTotalBalcoes(Sistema s) {
    return s->totalBalcoes;
}

NodeB* getSistemaTable(Sistema s) {
    return s->table;
}

Balcao getNodeBBalcao(NodeB n) {
    return n->balcao;
}

NodeB getNodeBNext(NodeB n) {
    return n->prox;
}

void setSistemaSize(Sistema s, int size) {
    s->size = size;
}

void setSistemaTotalBalcoes(Sistema s, int total) {
    s->totalBalcoes = total;
}

void insertBalcaoSistema(Sistema s, Balcao b) {
    if (s == NULL || b == NULL) return;

    int index = hashSistema(s, getIdBalcao(b));
    NodeB novo = malloc(sizeof(struct nodeB));
    if (novo == NULL) return;

    novo->balcao = b;
    novo->prox = s->table[index];
    s->table[index] = novo;
    s->totalBalcoes++;
}


Sistema createSistema(int size) {
    Sistema s = malloc(sizeof(struct sistema));
    s->size = size;
    s->totalBalcoes = 0;
    s->table = calloc(size, sizeof(NodeB));
    return s;
}

int hashSistema (Sistema s,int id) {
    return id % s->size;
}

Clientes consultBalcao(Sistema s, int id) {
    if (s == NULL) return NULL;

    int index = hashSistema(s, id); 
    NodeB atual = s->table[index];

    while (atual != NULL) {
        if (getIdBalcao(atual->balcao) == id) {
            return getClientes(atual->balcao);
        }
        atual = atual->prox;
    }

    return NULL;
}

int insertClienteBalcao(Sistema s, int idBalcao, int numCC, char *nomeServ) {
    if (s == NULL) return 0;

    int index = hashSistema(s, idBalcao);
    NodeB atual = s->table[index];

    while (atual != NULL) {
        if (getIdBalcao(atual->balcao) == idBalcao) {
            Balcao b = atual->balcao;

            Cliente c = consultCliente(getClientes(b), numCC);
            if (c == NULL) return 0;

            insertClienteServico(b, c, nomeServ);
            return 1;
        }
        atual = atual->prox;
    }

    return 0; 
}

Cliente chamaClienteBalcao(Sistema s, int idBalcao, char *nomeServ) {
    NodeB atual = s->table[hashSistema(s, idBalcao)];

    while (atual != NULL) {
        if (getIdBalcao(atual->balcao) == idBalcao) {
            Balcao b = atual->balcao;
            Servico* servicos = getServicos(b);

            for (int i = 0; i < getTotalServicos(b); i++) {
                Servico serv = servicos[i];
                if (strcmp(getNomeServico(serv), nomeServ) == 0) {
                    return (Cliente) popFront(getFilaServico (serv)); 
                }
            }
        }
        atual = atual->prox;
    }
    return NULL;
}


void freeSistema(Sistema s) {
    if (!s) return;

    for (int i = 0; i < s->size; i++) {
        NodeB atual = s->table[i];
        while (atual) {
            NodeB temp = atual;
            atual = atual->prox;
            freeBalcao(temp->balcao);
            free(temp);
        }
    }

    free(s->table);
    free(s);
}
