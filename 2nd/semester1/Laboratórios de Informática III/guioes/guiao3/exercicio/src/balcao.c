#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balcao.h"
#include "cliente.h"
#include "servico.h"

struct horario {
    char *hora_init; // "09:00"
    char *hora_fim; // "18:00";
};

struct balcao {
    int id;
    char *nome;
    char *localizacao; // ex: "Braga"
    Horario horario_atendimento;
    Clientes clientes;   
    int totalClientes;
    Servico *servicos;    
    int totalServicos;
};

// Getters
char* getHoraInit(Horario h) {
    return strdup(h->hora_init); 
}

char* getHoraFim(Horario h) {
    return strdup(h->hora_fim); 
}

int getIdBalcao (Balcao b) {
    return b->id;
}

int getTotalClientes (Balcao b) {
    return b->totalClientes;
}

int getTotalServicos (Balcao b) {
    return b->totalServicos;
}

char* getNome(Balcao b) {
    return strdup(b->nome);
}

char* getLocalizacao(Balcao b) {
    return strdup(b->localizacao); 
}

Horario getHorario(Balcao b) {
    return b->horario_atendimento; 
}

Clientes getClientes (Balcao b) {
    return b->clientes;
}

Servico getServico(Balcao b, int index) {
    return b->servicos[index];
}

Servico* getServicos(Balcao b) {
    return b->servicos;
}


// Setters
void setHoraInit(Horario h, const char *hora) {
    free(h->hora_init);
    h->hora_init = strdup(hora);
}

void setHoraFim(Horario h, const char *hora) {
    free(h->hora_fim);
    h->hora_fim = strdup(hora);
}

void setTotalClientes (Balcao b,int total) {
    b->totalClientes = total;
}

void setTotalServicos (Balcao b,int total) {
    b->totalServicos = total;
}

void setIdBalcao(Balcao b, int id) {
    b->id = id;
}

void setNome(Balcao b, const char *nome) {
    free(b->nome);
    b->nome = strdup(nome);
}

void setLocalizacao(Balcao b, const char *loc) {
    free(b->localizacao);
    b->localizacao = strdup(loc);
}

void setHorario(Balcao b, Horario h) {
    if (b->horario_atendimento != NULL) {
        free(b->horario_atendimento->hora_init);
        free(b->horario_atendimento->hora_fim);
        free(b->horario_atendimento); 
    }

    b->horario_atendimento = malloc(sizeof(struct horario));
    b->horario_atendimento->hora_init = strdup(h->hora_init);
    b->horario_atendimento->hora_fim = strdup(h->hora_fim);
}

void setClientes(Balcao b, Clientes c) {
    b->clientes = c;
}

void setServicos(Balcao b, Servico *s, int total) {
    b->servicos = s;
    b->totalServicos = total;
}


// Funções Gerais
int insertClienteServico(Balcao b, Cliente c, char *nomeServ) {
    
    for (int i = 0; i < getTotalServicos (b); i++) {
        Servico s = getServico (b,i);
        if (strcmp (getNomeServico (s),nomeServ) == 0) {
            insertClienteFila (c,getFilaServico (s));
            return 0;
        }
    }

    Servico novoServico = createServico(nomeServ);
    b->servicos = realloc(b->servicos, sizeof(Servico) * (b->totalServicos+1));
    b->servicos[b->totalServicos++] = novoServico;

    insertClienteFila(c, getFilaServico (novoServico));
    return 1;
}


void freeBalcao(Balcao b) {
    if (!b) return;

    free(b->nome);
    free(b->localizacao);

    if (b->servicos) {
        for (int i = 0; i < b->totalServicos; i++) {
            free(getNomeServico (b->servicos[i]));
            free(getFilaServico (b->servicos[i]));
            free(b->servicos[i]);
        }
        free(b->servicos);
    }

    if (b->clientes) {
        free(getClientesTable (b->clientes));
        free(b->clientes);
    }

    free(b);
}

