#include <stdio.h>

// Funções sobre strings
// 1
int serVogal (char c) {
    char vogais[] = "AEIOUaeiou";

    for (int i = 0; vogais [i] != '\0';i++) {
        if (c == vogais[i]) return 1;
    }

    return 0;
}

int contaVogais (char *s) {
    int c = 0; 

    for (int i = 0; s[i] != '\0';i++) {
        if (serVogal (s[i])) c++;
    }

    return c;
}

// 2 
// Usando um array auxiliar 
int retiraVogaisRepArray (char *s) {
    int len = 0,j = 1, c = 0, i ; 
    while (s[len] != '\0') len ++;

    char aux [len];
    aux [0] = s[0];

    for (int i = 1; s[i] != '\0';i++) {
        if (serVogal (s[i]) && s[i] == s[i-1]) c++;
        else aux [j++] = s[i];
    }

    aux [j] = '\0';

    for (i = 0; aux[i] != '\0';i++) s[i] = aux[i];

    s[i] = '\0';

    return c;

}

// Sem usar um array auxiliar
int retiraVogaisRep (char *s) {
    int j = 1,c = 0; 

    for (int i = 1; s[i] != '\0';i++) {
        if (serVogal (s[i]) && s[i] == s[i-1]) c++;
        else s[j++] = s[i];
    }

    s[j] = '\0';
    return c;
}

// 3 
// Usando um array auxiliar
int duplicaVogaisArray (char *s) {
    int len = 0, c = 0, pos, j = 0,i; 
    while (s[len] != '\0') len ++;

    char aux[len];

    for (int i = 0; s[i] != '\0';i++) {
        aux [j++] = s[i];
        if (serVogal (s[i])) {
            aux [j++] = s[i];
            c++;
        }
    
    }
    
    aux[j] = '\0';

    for (i = 0; aux[i] != '\0';i++) s[i] = aux[i];

    s[i] = '\0';

    return c;
}


// Sem usar um array auxiliar
int duplicaVogais (char *s) {
    int pos, c = 0, len = 0;

    while (s[len] != '\0') len ++;  
    
    for (int i = 0; s[i] != '\0';i++) {
        if (serVogal (s[i])) {
            pos = i+1;
            for (int j = len; j > pos; j--) {
                s[j] = s[j-1];
            }
            s[pos] = s[i];
            len ++; c++;
            i++;
        }
    }

    s[len] = '\0';

    return c;
}

// Arrays ordenados
// 1 
int ordenado (int v[],int N) {

    for (int i = 1; i < N; i++) {
        if (v[i] < v[i-1]) return 0;
    }

    return 1;
}

// 2 
void merge (int a[],int na,int b[],int nb,int r[]) {
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb) {
        if (a[i] < b[j]) {
            r[k++] = a[i++];
        } else {
            r[k++] = b[j++];
        }
    }

    while (i < na) {
        r[k++] = a[i++];
    }

    while (j < nb) {
        r[k++] = b[j++];
    }

}

// 3  
int partition1 (int v[],int N,int x) {
    int a = 0, b = 0,temp;

    for (int i = 0; i < N; i++) {
        if (v[b] <= x) {
            temp = v[a];
            v[a] = v[b];
            v[b] = temp;
            b++;a++;
        } else {
            b++;
        }
    }

    return a;
}

int partition2 (int v[],int N,int x) {
    int a = 0, b = N - 1, temp;

    while (a < b) {
        
        while (a < N && v[a] <= x) a++;

        while (b >= 0 && v[b] > x) b--;
    
        if (a < b) {
            temp = v[a];
            v[a] = v[b];
            v[b] = temp;
        }
    }

    return a;

}

int main () {
    int v[] = {1,10,2,5};
    printf ("%d\n",partition2 (v,4,3));
    return 0;
}   