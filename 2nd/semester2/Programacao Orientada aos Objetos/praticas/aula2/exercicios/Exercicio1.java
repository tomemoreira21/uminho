package aula2.exercicios;

import java.util.Arrays;

public class Exercicio1 {
    private int[] numeros;

    public void recebeArray (int[] vector,int dimensao) {
        this.numeros = new int[dimensao];

        for (int i = 0; i < dimensao; i++) {
            numeros[i] = vector[i];
        }
    }

    public int determinaMin (int[] valores) {
        numeros = valores;
        int min = numeros[0];

        for (int i = 1; i < numeros.length; i++) {
            if (numeros[i] < min) {
                min = numeros[i];
            }
        }

        return min;
    }

    public int[] determinaIntervalo (int[] valores,int init,int last) {
        return Arrays.copyOfRange(valores, init, last + 1); 
    }

    private boolean existeArray (int[] valores,int elem) {
        for (int i = 0; i < valores.length; i++) {
            if (valores[i] == elem) return true;
            if (valores[i] == -1) break;
        }

        return false;
    }

    public int[] comuns_arrays (int[] a1,int[] a2) {
        int[] novo = new int[(a1.length > a2.length) ? a2.length : a1.length];   
        Arrays.fill(novo,-1);
        int k = 0;

        for (int i = 0; i < a1.length; i++) {
            int elem = a1[i];
            for (int j = 0; j < a2.length; j++) {
                if (a2[j] == elem && !existeArray(novo, elem)) {
                    novo[k++] = elem;
                    break;
                }
            }
        }

        return Arrays.copyOf(novo, k);
    }

}
