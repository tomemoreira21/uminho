package aula2.exercicios;

import java.util.Arrays;

public class Exercício3 {

    public void ordenaArray (int[] valores) {
        Arrays.sort(valores);
    }

    public int procuraBin (int[] valores,int elem) {
        int[] copia = Arrays.copyOf(valores, valores.length);
        ordenaArray(copia);
        return Arrays.binarySearch(copia, elem);
    }
}
