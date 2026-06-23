#include <stdio.h> 
#include <limits.h>

// 1 
void maior () {
    int maior,n;

    printf ("Insere um número inteiro (digita 0 para terminar):");
    scanf ("%d",&n);

    maior = n; 

    while (n != 0) {
        printf ("Insere um número inteiro (digita 0 para terminar):");
        scanf ("%d",&n);

        if (n == 0) break;

        if (n > maior) maior = n; 

    }

    printf ("O maior elemento da sequência: %d \n",maior);
}

// 2 
void media () {
    int soma,valores,n;
    
    printf ("Insere um número inteiro (digita 0 para terminar):");
    scanf ("%d",&n);

    soma = n; 
    valores = 1;

    while (n != 0) {
        printf ("Insere um número inteiro (digita 0 para terminar):");
        scanf ("%d",&n);
        
        if (n == 0) break;
        
        soma += n; 
        valores ++;
    }

    printf ("Média da sequência: %d \n",soma/valores);
}

// 3 
void segundomaior() {
    int smaior,maior,n;

    printf ("Insere uma sequência de números inteiro (digita 0 para terminar):");
    scanf ("%d",&n);

    maior = n; 
    smaior = INT_MIN;

    while (n != 0) {
        printf ("Insere um número inteiro (digita 0 para terminar):");
        scanf ("%d",&n);

        if (n == 0) break;

        if (n > maior) {
            smaior = maior;
            maior = n;
        }

        if (n < maior && n > smaior) smaior = n;
    }

    printf ("2ºmaior da sequência : %d \n",smaior);
}

// 4
int bitsUm (unsigned int n) {
    int r = 0;

    while (n != 0) {
        if (n % 2 == 1) r++; 
        n = n >> 1;
    }
    return r;
}

// 5
int trailingZ (unsigned int n) {
    int r = 0;

    while (n != 0) {
        if (n % 2 == 0) r++;
        n = n >> 1;
    }
    return r;
}

// 6
int qDig (unsigned int n) {
    int r = 0;

    while (n != 0) {
        r++;   
        n /= 10;
    }

    return r;
}

// 7
char *strcat (char s1[],char s2[]) {
    int c1 = 0;

    for (int i = 0; s1[i] != '\0';i++) c1++;

    for (int i = 0; s2[i] != '\0';i++) {
        s1[c1] = s2 [i];
        c1++;
    }
    s1[c1] = '\0';

    return s1;
}

// 8
char *strcpy (char *dest,char source[]) {
    int i;

    for (i = 0; source [i] != '\0';i++) {
        *(dest + i) = source [i];
    }

    * (dest + i) = '\0';
    
    return dest;
}

// 9
int strcmp (char s1[],char s2[]) {
    int i = 0; 

    for (i = 0; s1[i] != '\0' && s2[i] != '\0';i++) {
        if (s1[i] < s2[i]) return -1;

        if (s1[i] > s2[i]) return 1;
    }
    
    if (s1[i] == '\0' && s2[i] != '\0') return -1;
    if (s1[i] != '\0' && s2[i] == '\0') return 1; 
    
    return 0;
}

// 10
char *strstr (char s1[], char s2[]) {
    int j;

    for (int i = 0; s1[i] != '\0';i++) {
        j = 0;
        while (s1[i+j] == s2[j] && s2[j] != '\0') j++;

        if (s2[j] == '\0') return &s1[i];
    }
    return NULL;
}

// 11
void strrev1 (char s[]) {
    int c = 0,temp;

    for (int i = 0; s[i] != '\0';i++) c++;

    for (int i = 0; i < c/2;i++) {
        temp = s[i];
        s[i] = s[c - i - 1];
        s [c - i - 1] = temp;
    }
}

void strrev2 (char s[]) {
    int c = 0,temp;

    for (int i = 0; s[i] != '\0';i++) c++;

    int i = 0, j = c -1;

    while (i < j) {
        temp = s[i];
        s [i] = s[j];
        s[j] = temp;
        i++;j--;
    }
}


// 12 
// Função auxiliar necessária para verificar se o caractere é uma vogal
int serVogal (char c) {
    char vogais[] = "AEIOUaeiou";

    for (int i = 0; vogais[i] != '\0'; i++) {
        if (c == vogais[i]) return 1;
    }
    return 0;
}

void strnoV (char s[]) {
    int j = 0;

    for (int i = 0; s[i] != '\0';i++) {
        if (!serVogal (s[i])) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';

}

// 13
void truncW (char t[], int n) {
    int dentroDaPalavra = 0, j = 0, c = 0;

    for (int i = 0; t[i] != '\0';i++) {
        if (t[i] != ' ') {
            if (c < n) {
                t[j++] = t[i];
            }
            c++;
            dentroDaPalavra = 1;
        } else {
            if (dentroDaPalavra) {
                t[j++] = t[i];
            }
            dentroDaPalavra = 0;
            c = 0;
        }
    }
    
    t[j] = '\0';
}

// 14 
char charMaisfreq (char s[]) {
    int contagem [256] = {0};
    char maisFreq = s[0];
    int maxFreq = 0;

    if (s[0] == '\0') return 0;

    for (int i = 0; s[i] != '\0';i++) {
        contagem [s[i]]++;
        if (contagem [s[i]] > maxFreq) {
            maxFreq = contagem [s[i]];
            maisFreq = s[i];
        }
    }

    return maisFreq;
}

// 15 
int iguaisConsecutivos (char s[]) {
    int comp = 1, compMax = 1;

    for (int i = 1; s[i] != '\0';i++) {
        if (s[i] == s[i-1]) comp++;
        else {
            if (comp > compMax) compMax = comp;
            comp = 1;
        }
    }

    return compMax;
}

// 16 
int difConsecutivos (char s[]) {
    int comp,freqMax = 1,k,j,i; 

    for (i = 0; s[i] != '\0';i++) {
        for (j = i + 1; s[j] != '\0';j++) {
            for (k = i; k < j; k++) {
                if (s[j] == s[k]) break;
            }
            if (k < j) break;
        }

        comp = j - i;

        if (comp > freqMax) freqMax = comp;
    }
    return freqMax;
}

    
// 17
int maiorPrefixo (char s1[],char s2[]) {
    int comp = 0;

    while (s1[comp] == s2[comp]) comp++;

    return comp;
}

// 18
int maiorSufixo (char s1[],char s2[]) {
    int comp1 = 0,comp2 = 0, c = 0;

    while (s1[comp1] != '\0') comp1 ++;
    while (s2[comp2] != '\0') comp2 ++;

    int i = comp1 - 1, j = comp2 - 1;

    while (s1[i] == s2[j] && i >= 0 && j >= 0) {
        c++;
        i--;j--;
    }

    return c;
}

// 19
int sufPref (char s1[],char s2[]) {
    int j = 0,freqMax = 0; 

    for (int i = 0; s1[i] != '\0';i++) {
        if (s1[i] == s2[j]) {
            while (s1[i+j] == s2[j] && s1[i+j] != '\0' && s2[j] != '\0') j++;
        } 

        if (j > freqMax) freqMax = j;
        j = 0;

    }

    return freqMax;

}
// 20
int contaPal (char s[]) {
    int p = 0;

    for (int i = 0; s[i] != '\0';i++) {
        if (s[i] != ' ') {
            if (s[i+1] == ' ' || s[i+1] == '\0') p++;
        } 
    }

    return p;
}
// 21
int contaVogais (char s[]) {
    int v = 0;

    for (int i = 0; s[i] != '\0';i++) {
        if (serVogal (s[i])) v ++;
    }
    return v;
}

// 22
int contida (char a[],char b[]) {

    for (int i = 0; a[i] != '\0';i++) {
        int encontra = 0;
        for (int j = 0; b[j] != '\0';j++) {
            if (a[i] == b[j]) {
                encontra = 1;
                break;
            } 
        }
        if (!encontra) return 0;
    }

    return 1;
}


// 23
int palindrome (char s[]) {
    int comp = 0,p = 1;

    while (s[comp] != '\0') comp ++;
  
    for (int i = 0; i < comp / 2;i++) {
        if (s[i] != s[comp - i - 1]) return 0;
    }
  return 1;
}

// 24
int rempRep (char x[]) {
    int j = 1;

    for (int i = 1; x[i] != '\0';i++) {
        if (x[i] != x[i-1]) x[j++] = x[i];
    }

    x[j] = '\0';
    
    return j;
}

// 25  
int limpaEspacos (char t[]) {
    int j = 1;

    for (int i = 1; t[i] != '\0';i++) {
        if (t[i] != ' ') t[j++] = t[i];
        else {
            if (t[i-1] != ' ') t[j++] = t[i];
        }
    }
    
    t[j] = '\0';

    return j;
}

// 26 
void insere (int v[],int N,int x) {
    int pos, i = 0;

    while (i < N && v[i] < x) i++;
    
    pos = i;
    for (int i = N; i > pos; i--) {
        v[i] = v[i-1];
    }

    v[pos] = x;
}

// 27 
void merge (int r [], int a[], int b[], int na, int nb) {
    int i = 0,k = 0, j = 0;

    while (j < na && i < nb) {
        if (a[j] <= b[i]) {
            r[k++] = a[j++];
        } 

        else {
            r[k++] = b[i++];
        }
    }

    while (j < na) { 
        r [k++] = a[j++];
    }

    while (i < nb) { 
        r [k++] = b[i++];
    }
}

// 28
int crescente (int a[],int i,int j) {
    if (i > j) return 0;  
    
    for (int var = i; var < j ;var++) {
        if (a[var] > a[var+1]) return 0;
    }
    return 1;
}

// 29 
int retiraNeg (int v[],int n) {
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] >= 0) v[j++] = v[i];
    }

    return j;
}


// 30
int menosFreq (int v[],int N) {
    int freq = 1, freqMin = N, numMin = v[0];

    for (int i = 1; i < N; i++) {
        if (v[i] == v[i-1]) {
            freq ++;
        } else {
            if (freq < freqMin) {
                freqMin = freq;
                numMin = v[i-1]; 
            }
            freq = 1;
         }
   }
    return numMin;
}

// 31
int maisFreq (int v[],int N) {
    int freq = 1, freqMax = 1, numMax = v[0];

    for (int i = 1; i < N; i++) {
        if (v[i] == v[i-1]) {
            freq ++;
        } else {
            if (freq > freqMax) {
                freqMax = freq;
                numMax = v[i - 1];
            }
            freq = 1;
        }
    }

    return numMax;
}

// 32
int maxCresc (int v[],int N) {
    int freq = 1, freqMax = 1;

    for (int i = 1; i < N; i++) {
        if (v[i] > v[i-1]) freq++;
        else {
            if (freq > freqMax) {
                freqMax = freq;
            }
            freq = 1;
        }
    }
    return freqMax;
}

// 33
int jaExiste (int v[],int n,int e) {
    for (int i = 0; i < n; i++) {
        if (v[i] == e) return 1;
    }

    return 0;
}

int elimRep (int v[],int n) {
    int arr [n],j = 1;
    arr[0] = v[0];

    for (int i = 1; i < n; i++) {
        if (!jaExiste (arr,j,v[i])) {
            arr[j++] = v[i];
        }
    }

    for (int i = 0; i < j; i++) v[i] = arr[i];

    return j;
}

// 34 
int elimRepOrd (int v[],int n) {
    int j = 1;

    for (int i = 1; i < n; i++) {
        if (v[i] != v[i-1]) {
            v[j++] = v[i];
        }
    }

    return j;
}


// 35
int comunsOrd (int a[],int na,int b[],int nb) {
    int c = 0, i = 0, j = 0;

    while (i < na && j < nb) {
        if (a[i] == b[j]) {
            c++;
            i++;j++;
        }

        else if (a[i] < b[j]) i++;
        else j++;
    }

    return c;
}

// 36
int comuns (int a[],int na,int b[],int nb) {
    int c = 0;
    int r[na];

    for (int j = 0; j < na; j++) {
        if (!jaExiste (r,c,a[j])) {
            for (int i = 0; i  < nb; i++) {
                if (a[j] == b[i]) {
                    r[c++] = a[j];
                    break;
                }
            }
        }
    }
    return c;
}

// 37 
int minInd (int v[],int n) {
    int m = 0;

    for (int i = 1; i < n; i++) {
        if (v[i] < v[m]) {
            m = i;
        }
    }

    return m;
}

// 38
void somasAc (int v[],int Ac[],int N) {
    int r = 0;

    for (int i = 0; i < N; i++) {
        r += v[i];
        Ac[i] = r;
    }
}

// 39 
int triSup (int N, float m [N] [N]) {

    for (int l = 0; l < N; l++) {
        for (int c = 0; c < l; c++) {
            if (m [l] [c] != 0) return 0;
            }
        }

    return 1;

}

// 40 
void transposta (int N,float m [N] [N]) {
    float temp;

    for (int l = 0; l < N; l++) {
        for (int c = l + 1; c < N; c++) {
            temp = m [l] [c];
            m [l] [c] = m [c] [l];
            m [c] [l] = temp;
        }
    }

}

// 41
void addTo (int N,int M,int a [N] [M],int b [N] [M]) {

    for (int l = 0; l < N; l++) {
        for (int c = 0 ; c < N; c++) {
            a [l] [c] = a [l] [c] + b [l] [c];
        }
    }
}

// 42 
int unionSet (int N,int v1[N],int v2[N],int r[N]) {

    for (int i = 0 ; i < N; i++) {
        r[i] = (v1[i] == 0 && v2[i] == 0) ? 0 : 1;
    }

}

// 43 
int intersectSet (int N, int v1[N], int v2[N],int r[N]) {

    for (int i = 0; i < N; i++) {
        r[i] = (v1[i] == 1 && v2[i] == 1) ? 1 : 0;
    }

}

// 44
int intersectMSet (int N, int v1[N], int v2[N],int r[N]) {

    for (int i = 0; i < N; i++) {
        r[i] = (v1[i] < v2[i]) ? v1[i] : v2[i];
    }

}

// 45
int unionMSet (int N, int v1[N], int v2[N], int r[N]) {

    for (int i = 0; i < N; i++) {
        r[i] = (v1[i] > v2[i]) ? v1[i] : v2[i];
    }
}

// 46
int cardinalMSet (int N,int v[N]) {
    int c = 0;

    for (int i = 0; i < N; i++) {
        if (v[i] != 0) c += v[i];
    }

    return c;
}

// 47 
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;
typedef struct posicao {
    int x, y;
} Posicao;

Posicao posFinal (Posicao inicial,Movimento mov[],int N) {
    int x = inicial.x, y = inicial.y;

    for (int i = 0; i < N; i++) {
        if (mov[i] == Norte) y++;
        else if (mov[i] == Sul) y--;
        else if (mov[i] == Este) x++;
        else if (mov[i] == Oeste) x--;
    }

    Posicao final = {x,y};
    return final;

}

// 48
int caminho (Posicao inicial, Posicao final, Movimento mov[], int N) {
    int xi = inicial.x,yi = inicial.y,xf = final.x,yf = final.y,i = 0, d = 1;

    while (i < N && (xi != xf || yi != yf)) {
        if (xi > xf) {
            mov[i++] = Oeste;
            xi -= d;
        }
        else if (xi < xf) {
            mov[i++] = Este;
            xi += d;
        }
        else if (yi > yf) {
            mov [i++] = Sul;
            yi -= d;
        }
        else if (yi < yf) {
            mov[i++] = Norte;
            yi += d;
        }
    }

    if (xi == xf && yi == yf) return i;
    

    return -1;
}

// 49
int maisCentral (Posicao pos[], int N) {
    int dMin = (pos[0].x * pos[0].x) + (pos[0].y * pos[0].y), dAtual;
    int i = 0;

    for (int j = 1; j < N; j++) {
        dAtual = (pos[j].x * pos[j].x) + (pos[j].y * pos[j].y);
        if (dAtual < dMin) {
            dMin = dAtual;
            i = j;
        }
    }

    return i;
}

// 50 
int serAdjacente (Posicao p1,Posicao p2) {
    int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;

    return (x1 == x2 && (y1 == y2 - 1 || y1 == y2 + 1 ) ||
            y1 == y2 && (x1 == x2 - 1 || x1 == x2 + 1));

}

int vizinhos (Posicao p,Posicao pos[],int N) {
    int c = 0;
    
    for (int i = 0; i < N; i++) {
        if (serAdjacente (p,pos[i])) c++;
    }

    return c;
}

int main() {
    int v[] = {1,1,2,2,2,3};
    printf ("%d\n",elimRepOrd (v,6));
    return 0;
}
