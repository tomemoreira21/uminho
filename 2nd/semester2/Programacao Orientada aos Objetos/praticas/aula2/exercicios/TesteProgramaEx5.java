package aula2.exercicios;

import java.util.Arrays;
import java.util.Scanner;

public class TesteProgramaEx5 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio5 e = new Exercicio5();
        int[][] notas = new int[5][5];

        for (int i = 0; i < 5;i++) {
            System.out.format ("Notas do Aluno %d\n",i);
            for (int j = 0; j < 5; j++) {
                System.out.format ("Disciplina %d: ",j);
                notas[i][j] = sc.nextInt();
            }
        }

        e.atualizaNotasTurma(notas);

        System.out.format("Somas das notas da UC %d: %d\n",1,e.somaNotas(notas, 1));
        System.out.format("Média das notas do aluno %d: %.2f\n",0,e.mediaAluno(notas, 0));
        System.out.format("Média das notas da UC %d: %.2f\n",2,e.mediaUC(notas, 2));
        System.out.format("Nota mais alta: %d\n",e.maxNotas(notas));
        System.out.format("Nota mais baixa: %d\n",e.minNotas(notas));
        System.out.format ("Notas com valores acima de %d\n",15);
        System.out.print (Arrays.toString(e.notasAcima(notas, 15)));
        System.out.println ("\nString com todas as notas");
        System.out.print (e.notasAlunos(notas));
        System.out.format ("Index da UC com média mais alta: %d\n",e.indexMaxMedia(notas));

        sc.close();

    }
}
