package exerciciosII;

import java.util.Collections;
import java.util.Arrays;

public class Ordenacao {
    public void ordenaArrayDesc (Integer[] numeros) {
        Arrays.sort(numeros,Collections.reverseOrder());
    }

    public float calculaMedia (Integer[] numeros) {
        int soma = 0;
        int len = numeros.length;

        for (int i = 0; i < len; i++) {
            soma += numeros[i];
        }

        return (float)soma/len;
    }
}
