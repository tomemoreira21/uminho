#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "balcao.h"
#include "servico.h"
#include "sistema_gestao.h"
#include "interface.h"

#define NUM_CLIENTES 6
#define NUM_BALCOES 2

int main() {
    // --- Criar sistema ---
    Sistema sistema = createSistema(10);

    // --- Criar clientes ---
    Cliente c1 = create_cliente(12345678, "Joao Silva", "15/03/1940", "Rua A", 10);
    Cliente c2 = create_cliente(87654321, "Maria Santos", "20/06/1990", "Rua B", 5);
    Cliente c3 = create_cliente(11223344, "Ana Costa", "01/01/1935", "Rua C", 20);
    Cliente c4 = create_cliente(55667788, "Pedro Lopes", "12/12/1950", "Rua D", 12);
    Cliente c5 = create_cliente(99887766, "Sofia Martins", "05/05/2000", "Rua E", 7);
    Cliente c6 = create_cliente(33445566, "Carlos Ferreira", "30/08/1930", "Rua F", 2);

    // --- Criar balcões ---
    Balcao balcao1 = malloc(sizeof(Balcao));
    setIdBalcao(balcao1, 1);
    setNome(balcao1, "Balcao Braga");
    setLocalizacao(balcao1, "Braga");
    Clientes clientesB1 = createHashTable(NUM_CLIENTES);
    setClientes(balcao1, clientesB1);
    setTotalClientes(balcao1, 0);
    setServicos(balcao1, NULL, 0);

    Balcao balcao2 = malloc(sizeof(Balcao));
    setIdBalcao(balcao2, 2);
    setNome(balcao2, "Balcao Porto");
    setLocalizacao(balcao2, "Porto");
    Clientes clientesB2 = createHashTable(NUM_CLIENTES);
    setClientes(balcao2, clientesB2);
    setTotalClientes(balcao2, 0);
    setServicos(balcao2, NULL, 0);

    // --- Inserir clientes nas hash tables dos balcões ---
    hashInsert(clientesB1, c1);
    hashInsert(clientesB1, c2);
    hashInsert(clientesB1, c3);
    hashInsert(clientesB1, c4);
    hashInsert(clientesB1, c5);
    hashInsert(clientesB1, c6);

    hashInsert(clientesB2, c1);
    hashInsert(clientesB2, c2);
    hashInsert(clientesB2, c3);
    hashInsert(clientesB2, c4);
    hashInsert(clientesB2, c5);
    hashInsert(clientesB2, c6);

    // --- Inserir balcões no sistema ---
    insertBalcaoSistema(sistema, balcao1);
    insertBalcaoSistema(sistema, balcao2);

    // Consultar a informacao de um cliente, fornecendo o seu número de cartao de cidadao
    printf("=== Consulta individual ===\n");
    consultarClienteSistema(clientesB1, 11223344);
    consultarClienteSistema(clientesB2, 99887766);


    // Consultar a lista de clientes de um balcao, fornecendo o seu id
    printf("\n=== Clientes do Balcao 1 ===\n");
    int idBalcao_1 = 1;
    Clientes clientesBalcao1 = consultBalcao(sistema, idBalcao_1);
    printClientesHash(clientesBalcao1, idBalcao_1);

    printf("\n=== Clientes do Balcao 2 ===\n");
    int idBalcao_2 = 2;
    Clientes clientesBalcao2 = consultBalcao(sistema, idBalcao_2);
    printClientesHash(clientesBalcao2, idBalcao_2);

    // Adicionar um cliente a uma fila de espera, tendo o id do balcao, nº CC e nome do servico
    putchar ('\n');
    adicionarClienteServico(sistema, 1, 12345678, "Renovar Cartao");
    adicionarClienteServico(sistema, 1, 11223344, "Renovar Cartao");
    adicionarClienteServico(sistema, 1, 33445566, "Renovar Cartao");
    adicionarClienteServico(sistema, 1, 87654321, "Renovar Cartao");
    adicionarClienteServico(sistema, 1, 55667788, "Novo Cartao");
    adicionarClienteServico(sistema, 1, 99887766, "Novo Cartao");

    adicionarClienteServico(sistema, 2, 12345678, "Renovar Cartao");
    adicionarClienteServico(sistema, 2, 55667788, "Renovar Cartao");
    adicionarClienteServico(sistema, 2, 33445566, "Novo Cartao");
    
    // Chamar o primeiro cliente na fila, fornecendo o id do balcao e o nome do servico
    printf("\n\n=== Chamadas de clientes no Balcao 1 ===\n");
    chamarClienteServico(sistema, 1, "Renovar Cartao");
    chamarClienteServico(sistema, 1, "Renovar Cartao");
    chamarClienteServico(sistema, 1, "Renovar Cartao");
    chamarClienteServico(sistema, 1, "Renovar Cartao");

    printf("\n\n=== Chamadas de clientes no Balcao 2 ===\n");
    chamarClienteServico(sistema, 2, "Novo Cartao");
    chamarClienteServico(sistema, 2, "Renovar Cartao");
    chamarClienteServico(sistema, 2, "Renovar Cartao");
    putchar ('\n');

    // --- Libertar memória ---
    freeSistema(sistema);

    return 0;
}
