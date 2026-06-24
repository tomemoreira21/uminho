#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"

struct address {
    char *rua;
    int numPorta;
};

struct cliente {
    int num_cartao;
    char *nome;
    char *data_nascimento; // "21/07/2025"
    Address morada; 
};

struct node {
    Cliente cliente;
    struct node *prox;
};

struct clientes {
    int size;          // número atual de buckets
    int count;         // número de clientes disponiveis
    Node *table;  // array de listas
};

// Getters
int getNum (Cliente c) {
    return c->num_cartao;
}

char *getName (Cliente c) {
    return strdup (c->nome);
}

char *getDate (Cliente c) {
    return strdup (c->data_nascimento);
}

Address getAddress(Cliente c) {
    return c->morada;
}

char* getStreet(Address a) {
    return strdup(a->rua);
}

int getDoorNum(Address a) {
    return a->numPorta;
}

int getClientesSize(Clientes cList) {
    return cList->size;
}

int getClientesCount(Clientes cList) {
    return cList->count;
}

Node* getClientesTable(Clientes cList) {
    return cList->table;
}

Cliente getNodeClienteHash(Node n) {
    return n->cliente;
}

Node getNodeNext(Node n) {
    return n->prox;
}

int getIdade(char *data_nascimento) {
    if (!data_nascimento) return 0;

    int dia = 0, mes = 0, ano = 0;

    dia = (data_nascimento[0]-'0')*10 + (data_nascimento[1]-'0');
    mes = (data_nascimento[3]-'0')*10 + (data_nascimento[4]-'0');
    ano = (data_nascimento[6]-'0')*1000 + (data_nascimento[7]-'0')*100 
        + (data_nascimento[8]-'0')*10 + (data_nascimento[9]-'0');

    time_t t = time(NULL);
    struct tm *today = localtime(&t);

    int idade = today->tm_year + 1900 - ano;

    if ((mes > (today->tm_mon + 1)) || 
        (mes == (today->tm_mon + 1) && dia > today->tm_mday)) {
        idade--;
    }

    return idade;
}

// Setters
void setNum (Cliente c,int num) {
    c->num_cartao = num;
}

void setName (Cliente c,const char *nome) {
    free (c->nome);
    c->nome = strdup (nome);
}

void setDate (Cliente c,const char *data) {
    free (c->data_nascimento);
    c->data_nascimento = strdup (data);
}

void setStreet (Address a, const char* rua) {
    free (a->rua);
    a->rua = strdup (rua);
}

void setDoorNum (Address a,int numPorta) {
    a->numPorta = numPorta;
}

void setAddress (Cliente c,Address morada) {
    if (c->morada == NULL) {
        c->morada = malloc(sizeof(struct address));
    }

    setStreet (c->morada,morada->rua);
    setDoorNum (c->morada,morada->numPorta);
}

// Funções gerais
Clientes createHashTable(int size) {
    Clientes h = malloc(sizeof(struct clientes));
    if (h == NULL) return NULL;

    h->size = size;
    h->count = 0;
    h->table = calloc(size, sizeof(struct node));
    if (h->table == NULL) {
        free(h);
        return NULL;
    }

    return h;
}

int hashClientes (Clientes h,int numCC) {
    return numCC % h->size;
}

Node create_node (Cliente c) {
    Node res = malloc (sizeof (struct node));
    res->cliente = c;
    res->prox = NULL;

    return res;
}

Cliente create_cliente(int num, char *nome, char *data, char *rua, int numPorta) {
    Cliente c = malloc(sizeof(struct cliente));
    c->num_cartao = num;
    c->nome = strdup(nome);
    c->data_nascimento = strdup(data);

    Address a = malloc(sizeof(struct address));
    a->rua = strdup(rua);
    a->numPorta = numPorta;

    c->morada = a;
    return c;
}

void hashInsert (Clientes h,Cliente c) {
    int index = hashClientes (h,c->num_cartao);

    Node novo = create_node (c);
    novo->prox = h->table[index];
    h->count++;

    h->table[index] = novo;
}

Cliente consultCliente (Clientes h,int numCC) {
    int index = hashClientes (h,numCC);
    Node atual = h->table[index];

    while (atual != NULL) {
        if (atual->cliente->num_cartao == numCC) return atual->cliente;
        atual = atual->prox;
    }

    return NULL;
}


