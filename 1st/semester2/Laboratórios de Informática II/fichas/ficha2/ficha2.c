#include "ficha2.h"
#include <string.h>
#include <stdio.h>

#define MAX_DIG 1000

void inicializaArray (int arr[]) {
    for (int i = 0; i < MAX_DIG;i++) arr[i] = 0;
}

void calculaProduto (char s[],int tamanho,int produto []) {
    int temp[MAX_DIG];
    inicializaArray (temp);
    temp [0] = 1;

    for (int i = 0;i < tamanho;i++) {
        int carry = 0;
        int digito = s[i] - '0';

        for (int j = 0; j < MAX_DIG;j++) {
            int val = temp[j] * digito + carry;
            temp[j] = val % 10;
            carry = val/10;
        }
    }

    for (int i = 0; i < MAX_DIG; i++) {
        produto[i] = temp[i];
    }
}

int tamanhoReal (int num []) {
    for (int i = MAX_DIG - 1; i>= 0; i--) {
        if (num [i] != 0) return i;
    }

    return 0;
}

int maiorNumero (int num1[],int num2[]) {
    int tamNum1 = tamanhoReal (num1);
    int tamNum2 = tamanhoReal (num2);

    if (tamNum1 > tamNum2) return 1;
    else if (tamNum1 < tamNum2) return -1;

    for (int i = tamNum1; i >= 0; i--) {
        if (num1[i] > num2[i]) return 1;
        if (num1[i] < num2[i]) return -1;
    }

    return 0; // devolve 0 se forem iguais
}

void maiorSubProduto(numero *v) {
    int len = strlen(v->N);

    if (v->S > len) return;

    char numeroStr [MAX_DIG];
    int produtoAtual [MAX_DIG];

    inicializaArray (v->maxProduto);

    for (int i = 0; i <= len - v->S; i++) {
    
        for (int j = 0; j < v->S; j++) {
            numeroStr[j] = v->N[i + j];
        }
        numeroStr[v->S] = '\0'; 

        inicializaArray (produtoAtual);

        calculaProduto(numeroStr, v->S, produtoAtual);

        if (maiorNumero (produtoAtual,v->maxProduto) > 0) {
            for (int i = 0; i < MAX_DIG;i++) {
                v->maxProduto [i] = produtoAtual [i];
            }
        }
    }
}

void imprimeMaiorProduto (int num[]) {
    int tamanho = tamanhoReal (num);

    for (int i = tamanho; i >= 0; i--) {
        printf ("%d",num[i]);
    }
    putchar ('\n');
}


void maiorProduto (numero v[],int C) {
    for (int i = 0; i < C; i++) {
        maiorSubProduto (&v[i]);   
    }
}
