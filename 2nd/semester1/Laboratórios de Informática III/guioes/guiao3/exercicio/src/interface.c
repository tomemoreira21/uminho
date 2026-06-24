#include <stdio.h>
#include <stdlib.h>
#include "sistema_gestao.h"
#include "balcao.h"
#include "cliente.h"
#include "servico.h"
#include <string.h>

// Função para mostrar info de um cliente
void printClienteInfo(Cliente c) {
    if (!c) {
        printf("Cliente não encontrado!\n");
        return;
    }
    printf("CC: %d\n", getNum(c));
    printf("Nome: %s\n", getName(c));
    printf("Data de nascimento: %s\n", getDate(c));
    Address a = getAddress(c);
    printf("Morada: %s, %d\n", getStreet(a), getDoorNum(a));
    printf("--------------------------\n");
}

// Mostra todos clientes de um balcão
void printClientesHash(Clientes cList, int idBalcao) {
    if (!cList || getClientesCount(cList) == 0) {
        printf("Sem clientes no balcão %d\n", idBalcao);
        return;
    }

    printf("Clientes do balcão %d:\n", idBalcao);

    int size = getClientesSize(cList);      // tamanho da tabela
    Node* table = getClientesTable(cList);  // array de listas

    for (int i = 0; i < size; i++) {
        Node atual = table[i];
        while (atual != NULL) {
            Cliente c = getNodeClienteHash(atual);
            printClienteInfo(c);
            atual = getNodeNext(atual);
        }
    }
}


// Adiciona cliente a um serviço de um balcão
void adicionarClienteServico(Sistema s, int idBalcao, int numCC, char *nomeServ) {
    if (insertClienteBalcao(s, idBalcao, numCC, nomeServ)) {
        printf("Cliente %d adicionado ao serviço '%s' no balcão %d\n", numCC, nomeServ, idBalcao);
    } else {
        printf("Falha ao adicionar cliente %d ao serviço '%s'\n", numCC, nomeServ);
    }
}

// Chama (remove) o próximo cliente de um serviço
void chamarClienteServico(Sistema s, int idBalcao, char *nomeServ) {
    Cliente c = chamaClienteBalcao(s, idBalcao, nomeServ);
    if (c) {
        printf("Cliente chamado do serviço '%s': %s (CC: %d)\n", nomeServ, getName(c), getNum(c));
    } else {
        printf("Não há clientes na fila do serviço '%s'\n", nomeServ);
    }
}

// Consulta cliente pelo CC
void consultarClienteSistema(Clientes h, int numCC) {
    Cliente c = consultCliente(h, numCC);
    printClienteInfo(c);
}