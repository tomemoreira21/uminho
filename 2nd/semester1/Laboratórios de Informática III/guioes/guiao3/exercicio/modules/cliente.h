#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct cliente *Cliente;
typedef struct address *Address;
typedef struct node *Node;
typedef struct clientes *Clientes;

// Getters e Setters
int getNum (Cliente c); 
char *getName (Cliente c);
char *getDate (Cliente c);
Address getAddress(Cliente c); 
char* getStreet(Address a);
int getDoorNum(Address a);
int getClientesSize(Clientes cList);
int getClientesCount(Clientes cList); 
Node* getClientesTable(Clientes cList); 
Cliente getNodeClienteHash(Node n);
Node getNodeNext(Node n);
int getIdade(char *data_nascimento);

void setNum(Cliente c, int num);
void setName(Cliente c, const char* nome);
void setDate(Cliente c, const char* data);
void setAddress(Cliente c, Address morada);
void setStreet(Address a, const char* rua);
void setDoorNum(Address a, int numPorta);

// Funções implementadas
Clientes createHashTable(int size);
int hashClientes (Clientes h,int numCC);
Node create_node (Cliente c);
Cliente create_cliente(int num, char *nome, char *data, char *rua, int numPorta);
void hashInsert (Clientes h,Cliente c);
Cliente consultCliente (Clientes h,int numCC);


#endif