#ifndef BALCAO_H
#define BALCAO_H

typedef struct balcao *Balcao;
typedef struct horario *Horario;

#include "servico.h"
#include "cliente.h"

// Getters e Setters
char* getHoraInit(Horario h);
char* getHoraFim(Horario h);
int getIdBalcao(Balcao b);
int getTotalClientes (Balcao b);
int getTotalServicos (Balcao b);
char* getNome(Balcao b); 
char* getLocalizacao(Balcao b);
Horario getHorario(Balcao b);
Clientes getClientes (Balcao b);
Servico getServico(Balcao b, int index);
Servico* getServicos(Balcao b);

void setHoraInit(Horario h, const char *hora); 
void setHoraFim(Horario h, const char *hora);
void setTotalClientes (Balcao b,int total);
void setTotalServicos (Balcao b,int total);
void setIdBalcao(Balcao b, int id);
void setNome(Balcao b, const char *nome); 
void setLocalizacao(Balcao b, const char *loc);
void setHorario(Balcao b, Horario h);
void setClientes(Balcao b, Clientes c);
void setServicos(Balcao b, Servico *s, int total);

// Funções implementadas
int insertClienteServico(Balcao b, Cliente c, char *nomeServ);
void freeBalcao(Balcao b);

#endif