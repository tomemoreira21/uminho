#include <stdio.h> 

// 1 
float multInt1 (int n,float m) {
    float r = 0;
    
    while (n > 0) {
        r += m;
        n --;
    }

    return r;
}

// 2
float multInt2 (int n, float m) {
    float r = 0;

    while (n > 0) {
        if (n % 2 != 0) r += m;
        n /= 2; // x = x >> 1 -> pegar na representação binária e retirar o último e adicionar o 0 à esquerda
        m *= 2; // m = m << 1;
    }  

    return r;
}

// exercicio extra (escreve os divisores de um número)
void escDiv (int n) {

    for (int i = 1; i <=n; i++) {
        if (n % i == 0) printf ("%d ",i);
    }

    putchar ('\n');
}

// 3 (começa no menor dos a e b) 
int mdc1 (int a,int b) {
    int menor;

    if (a < b) menor = a; else menor = b;

    for (int i = menor; i > 0; i--) {
        if (a % i == 0 && b % i == 0) return i;
    }
}

// 4
int mdc2 (int a,int b) {

    while (a != 0 && b != 0) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return (a+b);
}

// 5 
int mdc3 (int a,int b) {

    while (a != 0 && b != 0) {
        if (a > b) a = a % b;
        else b = b % a;
    }

    return (a+b);
}

// outra forma 
int mdc4 (int a,int b) {
    int temp;

    while (a != 0 && b != 0) {
        temp = a;
        a = b; 
        b = temp % b;
    }
    return (a+b);
}

// outra forma muito pouco otimizada 
int mdc5 (int a,int b) {
    if (b == 0) return a;
    else return (mdc5 (b,a%b));
}

// 6
// a)
int fib1 (int n) {
    if (n < 2) return 1;
    else return (fib1 (n-1) + fib1 (n-2));
}

// b) 
int fib2 (int n) {
    int n1 = 1,n2 = 1,temp;

    if (n < 2) return 1;

    for (int i = 2; i < n;i++) {
        temp = n1;
        n1 = n2;
        n2 = temp + n2;
    }

    return (n1+n2);
}

// outra forma explorada na aula teórica com array
int fib3 (int n) {
    int t[n+1];

    t[0] = t[1] = 1;

    for (int i = 2; i <= n; i++) {
        t [i] = t[i-2] + t[i-1];
    }

    return (t[n]);
}
