package aula2.exercicios;

import java.util.Arrays;
import java.util.Scanner;

public class TesteProgramaEx1 {
    static int[] array = new int[4];

    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio1 e1 = new Exercicio1();

        System.out.print ("Número de elementos: ");
        int N = sc.nextInt();
        int[] valores = new int[N];

        System.out.println ("Insere os elementos");
        for (int i = 0; i < N; i++) {
            valores[i] = sc.nextInt();
        }

        // faz o copy
        e1.recebeArray(valores, N);

        int vMin = e1.determinaMin(valores);
        System.out.format ("Valor Mínimo: %d\n",vMin);

        int[] novo = e1.determinaIntervalo(valores, 1, 3);
        System.out.println ("Intervalo de 1 até 3: ");
        System.out.print (Arrays.toString(novo));

        System.out.print ("\nNúmero de elementos: ");
        int Nnovo = sc.nextInt();
        int[] valoresNew = new int[Nnovo];

        System.out.println ("Insere os elementos");
        for (int i = 0; i < Nnovo; i++) {
            valoresNew[i] = sc.nextInt();
        }

        int[] merge = e1.comuns_arrays(valores, valoresNew);
        System.out.print (Arrays.toString(merge) + "\n");

        sc.close();
        }
}