package aula2.exercicios;

import java.util.Arrays;
import java.util.Scanner;

public class TesteProgramaEx6 {

    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio6 e = new Exercicio6();

        System.out.print ("Nº de linhas: ");
        int L = sc.nextInt();
        System.out.print ("Nº de colunas: ");
        int C = sc.nextInt();

        int[][] matriz = new int[L][C];
        for (int i = 0; i < L; i++) {
            System.out.format ("Insere os valores da linha %d\n",i+1);
            for (int j = 0; j < C; j++) {
                System.out.format ("matriz[%d][%d] = ",i,j);
                matriz[i][j] = sc.nextInt();
            }
        }

        int[][] matriz2 = {{1,2,3},{5,1,2},{-1,2,3}}; // matriz 3 x 3
        int[][] res = e.somaMatrizes(matriz, matriz2);
        System.out.println ("Matriz resultante da soma");
        for (int i = 0; i < L; i++) {
            System.out.print (Arrays.toString(res[i]) + "\n");
        }

        System.out.format ("equal(matriz,matriz2): %s\n",(e.matrizIguais(matriz, matriz2)) ? "Sim" : "Não");

        int[][] oposta = e.matrizOposta(matriz);
        System.out.println ("Matriz oposta à dada");
        for (int i = 0; i < L; i++) {
            System.out.print (Arrays.toString(oposta[i]) + "\n");
        }

        sc.close();
    }
    
}
