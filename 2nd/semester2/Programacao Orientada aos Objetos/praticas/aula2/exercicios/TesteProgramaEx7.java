package aula2.exercicios;

import java.util.Arrays;
import java.util.Scanner;

public class TesteProgramaEx7 {

    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio7 e = new Exercicio7();
        int[] numerosCertos = new int[5];
        int[] estrelasCertas = new int[2];

        for (int i = 0; i < 5; i++) {
            numerosCertos[i] = (int)(Math.random() * 50) + 1;
        }

        for (int i = 0; i < 2; i++) {
            estrelasCertas[i] = (int)(Math.random() * 9) + 1;
        }

        System.out.println ("Números sorteados: " + Arrays.toString(numerosCertos));
        System.out.println ("Estrelas sorteadas: " + Arrays.toString(estrelasCertas));

        int[] palpiteNumeros = new int[5];
        int[] palpiteEstrelas = new int[2];

        System.out.println("\nInsere os números (1 a 50)");
        for (int i = 0; i < 5; i++) 
            palpiteNumeros[i] = sc.nextInt();

        System.out.println("Insere as estrelas (1 a 9)");
        for (int i = 0; i < 2; i++) 
            palpiteEstrelas[i] = sc.nextInt();

        e.constroiChaveCerta(numerosCertos,estrelasCertas);

        int[] numerosAcertados = e.comparaIguais(palpiteNumeros);
        System.out.print ("Números corretos: ");
        System.out.format(Arrays.toString(numerosAcertados) + " (%d acertos)\n",numerosAcertados.length);

        int[] estrelasAcertadas = e.comparaIguais(palpiteEstrelas);
        System.out.print ("Estrelas corretas: ");
        System.out.format(Arrays.toString(estrelasAcertadas) + " (%d acertos)\n",estrelasAcertadas.length);

        boolean iguais = e.acertaRespota(palpiteNumeros, palpiteEstrelas);
        System.out.format ("Acertaste a resposta? %s\n",(iguais) ? "Sim" : "Não");
        if (iguais == true) 
            e.imprimeCorreto(); 

        sc.close();

    }

}
