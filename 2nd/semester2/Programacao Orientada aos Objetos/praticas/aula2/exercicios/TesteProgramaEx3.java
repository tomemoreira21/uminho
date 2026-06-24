package aula2.exercicios;

import java.util.Arrays;

public class TesteProgramaEx3 {

    public static void main(String[] args) {
        Exercício3 e = new Exercício3();
        int[] valores = {10,2,3,5,19};

        System.out.println("Array Inicial: " + Arrays.toString(valores));

        // Procura binária
        int e1 = e.procuraBin(valores, 3);
        int e2 = e.procuraBin(valores, 20);
        System.out.format ("Valor 3: %s\n",(e1 < 0) ? "false" : "true");
        System.out.format ("Valor 20: %s\n",(e2 < 0) ? "false" : "true");

        // ORDENA O ARRAY
        e.ordenaArray(valores);
        System.out.println ("Array Ordenado: " + Arrays.toString(valores));
    }


}
