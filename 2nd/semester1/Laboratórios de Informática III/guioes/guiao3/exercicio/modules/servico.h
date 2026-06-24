#ifndef SERVICO_H
#define SERVICO_H

typedef struct deque *Fila;
typedef struct servico *Servico;
typedef struct cliente *Cliente; 

// Getters e Setters
char* getNomeServico(Servico s);
Fila getFilaServico(Servico s);
void setNomeServico(Servico s, const char *nome);
void setFilaServico(Servico s, Fila f);

// Funções implementadas
Servico createServico (char *nomeServico);
void insertClienteFila (Cliente c,Fila f);

#endif