package aula2.exercicios;

import java.util.Arrays;

public class Exercicio7 {
    private final int size_numeros = 5;
    private final int size_estrelas = 2;

    private int[] numeros = new int[size_numeros]; // contém os números corretos
    private int[] estrelas = new int[size_estrelas]; // contém as estrelas corretas

    public void constroiChaveCerta (int[] n,int[] e) {
        for (int i = 0; i < size_numeros; i++) 
            numeros[i] = n[i]; 

        for (int j = 0; j < size_estrelas; j++) 
            estrelas[j] = e[j];
    }

    private boolean existeArray (int[] a,int elem) {
        for (int i = 0; i < a.length; i++) {
            if (a[i] == -1) break;
            if (a[i] == elem) return true;
        }

        return false;
    }

    public int[] comparaIguais (int[] res) {
        int[] iguais = new int[res.length];
        int k = 0;
        Arrays.fill(iguais, -1);

        for (int i = 0; i < res.length; i++) {
            boolean existe = existeArray((res.length == size_numeros) ? numeros : estrelas,res[i]);
            if (existe && !existeArray(iguais,res[i])) {
                iguais[k++] = res[i];
            }
        }

        return Arrays.copyOf(iguais, k);
    }

    public boolean acertaRespota (int[] numerosDados,int[] estrelasDadas) {
        for (int i = 0; i < size_numeros; i++) {
            if (!existeArray(numeros,numerosDados[i])) return false;
        }

        for (int i = 0; i < size_estrelas; i++) {
            if (!existeArray(estrelas,estrelasDadas[i])) return false;
        }

        return true;
        
    }

    private int[] concatChave() {
        int[] chave = Arrays.copyOf(numeros, size_numeros + size_estrelas);
        for (int i = 0; i < size_estrelas; i++)
            chave[size_numeros + i] = estrelas[i];

        return chave;
    }

    public void imprimeCorreto () {
        int[] chave = concatChave();
        int N = 50,i = 0;

        for (int j = 0; j < N; j++) {
            int index = i % 7;

            for (int k = 0; k < 7; k++) {
                System.out.print(chave[index] + " ");
                index = (index + 1) % 7;
            }

            System.out.print("\n");
            i += 2;
        }
    }
}
