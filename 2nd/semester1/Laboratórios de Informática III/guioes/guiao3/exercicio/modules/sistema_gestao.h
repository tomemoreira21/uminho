#ifndef SISTEMA_GESTAO_H
#define SISTEMA_GESTAO_H

typedef struct nodeB *NodeB;
typedef struct sistema *Sistema;

#include "balcao.h"
#include "cliente.h"
#include "servico.h"

// Getters
int getSistemaSize(Sistema s);
int getSistemaTotalBalcoes(Sistema s);
NodeB* getSistemaTable(Sistema s);
Balcao getNodeBBalcao(NodeB n);
NodeB getNodeBNext(NodeB n);

// Setters
void setSistemaSize(Sistema s, int size);
void setSistemaTotalBalcoes(Sistema s, int total);
void insertBalcaoSistema(Sistema s, Balcao b);

Sistema createSistema(int size);
int hashSistema (Sistema s,int id);
Clientes consultBalcao(Sistema s, int id);
int insertClienteBalcao(Sistema s, int idBalcao, int numCC, char *nomeServ);
Cliente chamaClienteBalcao (Sistema s,int idBalcao,char *nomeServ);
void freeSistema(Sistema s);


#endif