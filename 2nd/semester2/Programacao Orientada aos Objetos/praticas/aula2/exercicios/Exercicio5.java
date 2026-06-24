package aula2.exercicios;

public class Exercicio5 {
    private int[][] notasTurma;
    private static final int MAX = 5;

    public void atualizaNotasTurma (int[][] notas) {
        notasTurma = new int[MAX][MAX];

        for (int j = 0; j < MAX; j++) {
            for (int i = 0; i < MAX; i++) {
                notasTurma[j][i] = notas[j][i];
            }
        }
    }

    public int somaNotas (int[][] notas,int UC) {
        notasTurma = notas;
        int soma = 0;

        for (int i = 0; i < MAX; i++) {
            soma += notasTurma[i][UC];
        }

        return soma;
    }   

    public float mediaAluno (int[][] notas,int pos) {
        notasTurma = notas;
        int soma = 0;

        for (int i = 0; i < MAX; i++) {
            soma += notasTurma[pos][i];
        }

        return (float)soma/MAX;
    }

    public float mediaUC (int[][] notas,int UC) {
        notasTurma = notas;
        return (float)somaNotas(notasTurma, UC)/MAX;
    }

    public int maxNotas (int[][] notas) {
        notasTurma = notas;
        int max = Integer.MIN_VALUE;

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (notasTurma[i][j] > max) 
                    max = notasTurma[i][j];
            }
        }

        return max;
    }

    public int minNotas (int[][] notas) {
        notasTurma = notas;
        int min = Integer.MAX_VALUE;

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (notasTurma[i][j] < min) 
                    min = notasTurma[i][j];
            }
        }

        return min;
    }

    public int[] notasAcima (int[][] notas,int valor) {
        notasTurma = notas;
        int[] novo = new int[MAX * MAX];
        int k = 0;

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (notasTurma[i][j] > valor) {
                    novo[k++] = notasTurma[i][j];
                }
            }
        }

        return novo;
    }

    public String notasAlunos (int[][] notas) {
        notasTurma = notas;
        String s = "";

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                s += (notas[i][j] + " ");;
            }
        }

        return (s + "\n");
    }


    public int indexMaxMedia (int[][] notas) {
        notasTurma = notas;
        float maxMedia = Float.MIN_VALUE;
        int index = -1;

        for (int i = 0; i < MAX; i++) {
            float valorM = mediaUC(notasTurma, i);
            if (valorM > maxMedia) {
                maxMedia = valorM;
                index = i;
            }
        }

        return index;
    }
        
}