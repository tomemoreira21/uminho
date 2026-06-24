#ifndef INTERFACE_H
#define INTERFACE_H

#include "cliente.h"
#include "balcao.h"
#include "servico.h"
#include "sistema_gestao.h"

// Funções da interface (para interação com o utilizador / terminal)
void printClienteInfo(Cliente c);
void printClientesHash(Clientes cList, int idBalcao);
void adicionarClienteServico(Sistema s, int idBalcao, int numCC, char *nomeServ);
void chamarClienteServico(Sistema s, int idBalcao, char *nomeServ);
void consultarClienteSistema(Clientes h, int numCC);

#endif
