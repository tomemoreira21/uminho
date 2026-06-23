#include <stdio.h>

typedef struct aluno {
    int numero;
    char nome[100];
    int miniT [6];
    float teste;
} Aluno;

// 1 
int nota (Aluno a) {
    float notaMT = 0, notaFinal;

    for (int i = 0; i < 6; i++) {
        notaMT += a.miniT[i];
    }

    if (notaMT < 0.5) return 0;

    notaFinal = (notaMT * 10) * 0.20 + a.teste * 0.80; 

    return ((notaFinal < 9.5 ? 0 : (notaFinal + 0.5)));
}

// 2 
int procuraNum (int num, Aluno t[],int N) {
    int i = 0, j = N - 1,m;

    while (i <= j) {
        m = i + (j-i) / 2;

        if (t[m].numero == num) return m;

        else if (t[m].numero > num) j = m - 1; 
        
        else i = m + 1;
    }
    return -1;
}

// 3
int partition (Aluno t[],int N,int num) {
    Aluno temp;
    int a = 0, b = 0;

    for (int i = 0; i < N; i++) {
        if (t[b].numero <= num) {
            temp = t[a];
            t[a] = t[b];
            t[b] = temp;
            a++;b++;
        } else {
            b++;
        }
    }
    return a;
}

void swap (Aluno t[],int x,int y) {
    Aluno temp;

    temp = t[x];
    t[x]= t[y];
    t[y] = temp;
}

void ordenaPorNum (Aluno t[],int N) {
    int p;

    if (N > 1) {
        p = partition (t,N - 1,t[N-1].numero);
        swap (t,p,N - 1);
        ordenaPorNum (t,p);
        ordenaPorNum (t+p+1,N - p - 1);
    }
} 

// 4
void criaIndPorUm (Aluno t[],int N,int ind[]) {
    int temp;

    for (int i = 0; i < N; i++) ind[i] = i;

    for (int j = 0; j < N - 1; j++) {
        for (int k = 0; k < N - j - 1;k++) {
            if (t[ind[k]].numero > t[ind[k+1]].numero) {
                temp = ind[k];
                ind[k] = ind[k+1];
                ind[k+1] = temp;
            }
        }
    }
}

// 5 
void imprimeTurma (int ind[],Aluno t[],int N) {
    printf (" Numero       Nome               MiniT                      Teste\n");

    for (int i = 0; i < N; i++) {
        printf (" %d         %s ",t[ind[i]].numero,t[ind[i]].nome);
        for (int k = 0; k < 6; k++) {
            printf ("    %d ",t[ind[i]].miniT[k]);
        }
        printf ("       %2.f \n",t[ind[i]].teste);
    }

}

// 6 
int procuraNum2 (int num,Aluno t[],int N,int ind[]) {
    int i = 0, j = N - 1,m;

    while (i <= j) {
        m = i + (j-i)/2;

        if (num == t[ind[m]].numero) return m;

        else if (t[ind[m]].numero > num) j = m - 1;

        else i = m + 1;
    }   

    return -1;
}

// 7 
void criaIndPorNome (Aluno t [], int N, int ind[]) {
    int temp;

    for (int i = 0; i < N; i++) ind[i] = i;

    for (int j = 0; j < N - 1; j++) {
        for (int k = 0; k < N - j - 1; k++) {
            if (t[ind[k]].nome > t[ind[k+1]].nome) {
                temp = ind[k];
                ind[k] = ind[k+1];
                ind[k+1] = temp;
            }
        }
    }
}

// Função extra @imprime só para testar
void imprime (Aluno t[],int N) {
    printf (" Numero       Nome               MiniT                      Teste\n");

    for (int i = 0; i < N; i++) {
        printf (" %d         %s ",t[i].numero,t[i].nome);
        for (int k = 0; k < 6; k++) {
            printf ("    %d ",t[i].miniT[k]);
        }
        printf ("       %2.f \n",t[i].teste);
    }

}

int main () {
    Aluno t[4] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
    ,{2222, "Joana", {2,2,2,1,0,0}, 14.5}
    ,{7777, "Maria", {2,2,2,2,2,1}, 18.5}
    ,{3333, "Paulo", {0,0,2,2,2,1}, 8.7}
    };
    int ind [4] = {1,3,0,2};

    ordenaPorNum (t,4);

    imprime (t,4);

    

}