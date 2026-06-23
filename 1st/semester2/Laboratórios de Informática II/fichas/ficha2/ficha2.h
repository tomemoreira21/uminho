#ifndef FICHA2_H
#define FICHA2_H

#define MAX_DIG 1000

typedef struct  {
    char N [MAX_DIG];
    int S;
    int maxProduto[MAX_DIG];
} numero;


void inicializaArray (int arr[]);
void calculaProduto (char s[],int tamanho,int produto []);
int tamanhoReal (int num []);
int maiorNumero (int num1[],int num2[]);
void maiorSubProduto(numero *v);
void imprimeMaiorProduto (int num[]);
void maiorProduto (numero v[],int C);


#endif