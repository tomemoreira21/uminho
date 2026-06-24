package aula2.exercicios;

import java.util.Arrays;

public class Exercicio6 {

    public int[][] somaMatrizes (int[][] matriz1, int[][] matriz2) {
        int L1 = matriz1.length,C1 = matriz1[0].length;
        int L2 = matriz2.length,C2 = matriz2[0].length;

        if (L1 != L2 || C1 != C2) return null;
        
        int[][] matrizRes = new int[L1][C1];

        for (int i = 0; i < matriz1.length; i++) {
            for (int j = 0; j < matriz1[i].length; j++) {
                matrizRes[i][j] = matriz1[i][j] + matriz2[i][j];
            }
        }

        return matrizRes;
    }

    public boolean matrizIguais (int[][] matriz1, int[][] matriz2) {
        return Arrays.deepEquals(matriz1, matriz2);
    }   

    public int[][] matrizOposta (int[][] matriz) {
        int[][] matrizRes = new int[matriz.length][matriz[0].length];

        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[i].length;j++) {
                matrizRes[i][j] = -matriz[i][j];
            }
        }

        return matrizRes;
    }


}
