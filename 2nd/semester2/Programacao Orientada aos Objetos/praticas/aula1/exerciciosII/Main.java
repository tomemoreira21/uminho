package exerciciosII;

import java.time.LocalDateTime;
import java.util.Scanner;

public class Main {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);

        // Exercicio 1
        System.out.println ("=== Exercício 1 ===");
        Conversor f = new Conversor();
        
        System.out.print("Insere a temperatura em ºC: ");
        double valorT = sc.nextDouble();
        double valorF = f.celsiusParaFarenheit(valorT);
        System.out.format ("Resposta em Farenheit: %.2f ºF\n",valorF);

        // Exercicio 2
        System.out.println ("=== Exercício 2 ===");
        Calcula valor = new Calcula();

        System.out.println ("Insere dois números:");
        int v1 = sc.nextInt();        
        int v2 = sc.nextInt();
        int max = valor.maximoNumeros(v1,v2);
        System.out.format("Max: %d\n", max);

        sc.nextLine(); // limpa o buffer
        // Exercicio 3
        System.out.println ("=== Exercício 3 ===");
        Descricao d = new Descricao();

        System.out.print ("Insere o nome: ");
        String nome = sc.nextLine();
        System.out.print ("Insere o saldo: ");
        float saldo = sc.nextFloat();
        String res = d.criaDescricaoConta(nome, saldo);
        System.out.print(res + '\n');

        // Exercicio 4
        System.out.println ("=== Exercício 4 ===");
        ConversorMoedas c = new ConversorMoedas();

        System.out.print ("Insere o valor em euros (€): ");
        double euros = sc.nextDouble();
        System.out.print ("Insere a taxa de conversão para libras: ");
        double tax = sc.nextDouble();
        double libras = c.eurosParaLibras(euros,tax);
        System.out.format ("Valor em libras: %.2f\n",libras);

        // Exercicio 5
        System.out.println ("=== Exercício 5 ===");
        Ordenacao o = new Ordenacao();
        Integer[] array = new Integer[2];
        
        System.out.println ("Insere dois numeros: ");
        for (int i = 0; i < 2; i++) {
            array[i] = sc.nextInt();
        }

        o.ordenaArrayDesc(array);
        float media = o.calculaMedia(array);
        System.out.print ("Os dois números ordenados de forma decrescente: ");
        for (Integer e : array) {
            System.out.format ("%d ",e);
        }

        System.out.format("\nMédia: %.2f\n",media);

        // Exercicio 6
        System.out.println ("=== Exercício 6 ===");
        Fatorial fac = new Fatorial();
        
        System.out.print("Insere o número que pretende calcular fatorial: ");
        int num = sc.nextInt();
        long num_fac = fac.factorial(num);
        System.out.format("Fatorial: %d\n",num_fac);    
        
        // Exercicio 7
        System.out.println ("=== Exercício 7 ===");
        LocalDateTime agora = LocalDateTime.now();
        long tempo = fac.tempoGasto();
        LocalDateTime horaFinal = LocalDateTime.now(); 

        System.out.println("Hora inicial: " + agora);
        System.out.format ("Tempo Gasto: %d ms\n",tempo);
        System.out.println("Hora final: " + horaFinal);

        // Exercicio 8
        System.out.println ("=== Exercício 8 ===");
        Calculadora calc = new Calculadora();

        System.out.println ("Insere dois números reais:");
        double op1 = sc.nextDouble();
        double op2 = sc.nextDouble();
        System.out.format("%.2f + %.2f = %.2f\n", op1,op2,calc.soma(op1, op2));
        System.out.format("%.2f - %.2f = %.2f\n", op1,op2,calc.subtracao(op1, op2));
        System.out.format("%.2f x %.2f = %.2f\n", op1,op2,calc.multiplicar(op1, op2));
        System.out.format("%.2f / %.2f = %.2f\n", op1,op2,calc.dividir(op1, op2));

        sc.close();
    }
}
