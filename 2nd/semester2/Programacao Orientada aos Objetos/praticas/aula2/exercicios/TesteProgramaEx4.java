package aula2.exercicios;

import java.util.Arrays;
import java.util.Scanner;

public class TesteProgramaEx4 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio4 e = new Exercicio4();

        System.out.print ("Número de palavras que pretendes inserir: ");
        int N = sc.nextInt();
        sc.nextLine(); // consome o enter que ficou no buffer
        String[] palavras = new String[N];

        System.out.println ("Insere as palavras");
        for (int i = 0; i < N; i++) {
            palavras[i] = sc.nextLine();
        }   

        System.out.print ("Array original: ");
        System.out.print (Arrays.toString(palavras) + "\n");
        
        String[] semRepetidas = e.removeRepetidas(palavras);
        System.out.print ("Array sem as palavras repetidas: ");
        System.out.print (Arrays.toString(semRepetidas) + "\n");

        String s = e.maiorString(palavras);
        System.out.format ("Maior String: %s (%d length)\n",s,s.length());

        String[] repetidasArray = e.repetidasString(palavras);
        System.out.print ("Array com as palavras repetidas: ");
        System.out.print (Arrays.toString(repetidasArray) + "\n");

        int conta1 = e.contaString(palavras, "ola");
        int conta2 = e.contaString(palavras, "jupiter");

        System.out.format ("A palavra %s aparece %d vezes\n","ola",conta1);
        System.out.format ("A palavra %s aparece %d vezes\n","jupiter",conta2);

        sc.close();
    }
}
