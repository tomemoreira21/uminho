#include <stdio.h>

// 1 
// a) 
/*
O output vai ser: 

1 1 4 (i = 0)
2 2 6 (i = 1)
3 3 8 (i = 2)
4 4 10 (i = 3)
5 5 12 (i = 4)
*/

// b)
/*
O output vai ser: 
13

*/

// 2 
void swapM (int *x,int *y) {
    int temp; 

    temp = *x; 
    *x = * y;
    *y = temp;
}

// 3 
void swap1 (int v[],int i,int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v [j] = temp;
} 

void swap2 (int v[],int i,int j) {
    int temp;

    temp = *(v+i);
    *(v+i) = *(v+j);
    *(v+j) = temp;
}


// 4 
int soma (int v[],int N) {
    int r = 0; 

    for (int i = 0; i < N; i++) r+= v[i];

    return r;
}

// 5 
void inverteArray1 (int v[],int N) {
    
    for (int i = 0; i < N/2; i++) {
        swap1 (v,i,N - i - 1);
    }
}

void inverteArray2 (int v[],int N) {
    int i = 0,j = N -1;

    for (int i = 0; i < j;i++,j--) {
        swap1 (v,i,j);
    } 
}

// 6 
int maximum (int v[],int N,int *m) {
    if (N <= 0) return -1;
    
    *m = v[0];

    for (int i = 1; i < N;i++) {
        if (v[i] > *m) *m = v[i];
    }

    return 0;
}

int max (int v [],int N) {
    int m = v[0];

    for (int i = 1; i < N; i++) {
        if (v[i] > m) m = v[i];
    }

    return m;
}
// 7
void quadrados1 (int q[],int N) {

    for (int i = -1; i < N - 1; i++) {
        q [i+1] = i*i + (2*i + 1);
    }

}

void quadrados2 (int q[],int N) {

    for (int i = 0; i < N; i++) {
        q [i] = i*i;
    }
}

void quadrados3 (int q[],int N) {
    int delta = 1;

    q [0] = 0;

    for (int i = 1; i < N;i++) {
        q[i] = q[i-1] + delta;
        delta += 2;
    }
}

// 8
// a) 
void pascal (int v[],int N) {
    v[0] = 1;

    for (int i = 1; i <= N; i++) {
        v [i] = 1;
        for (int j = i - 1; j > 0; j--) {
            v[j] = v[j] + v[j-1];
        } 
    }
 }

// b) 
// usando a Pascal
void escrevePascal1 (int v[],int N) {

    for (int i = 0; i <= N; i++) {
        pascal (v,i);
        for (int j = 0; j <= i; j++) {
            printf ("%d ",v[j]);
        }
        putchar ('\n');
    }
}

void escrevePascal2 (int v[],int N) {
    v[0] = 1;
    printf ("%d ",v[0]);putchar ('\n');

    for (int i = 1; i <= N; i++) {
        v[i] = 1;

        for (int j = i - 1; j > 0; j--) {
            v [j] = v[j] + v[j-1];
        }

        for (int l = 0; l <= i; l++) {
            printf ("%d ",v[l]);
        }
        putchar ('\n');
    }
   
}

int main () {
    int v [5];

    escrevePascal2 (v,5);
    return 0;
}
