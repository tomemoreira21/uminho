package exerciciosI;

import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Scanner;

import exerciciosI.Exercicio.ResultadosTemperaturas;
import exerciciosI.Exercicio.ResultadosTriangulo;

public class Main {

    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicio e = new Exercicio();

        // Exercício 1
        System.out.print ("Insere o dia (1..31): ");    
        int dia = sc.nextInt();
        System.out.print ("Insere o mês (1..12): ");    
        int mes= sc.nextInt();
        System.out.print ("Insere o ano (1900..2100): ");    
        int ano = sc.nextInt();

        int valor = e.devolveDiaDaSemana(dia,mes,ano);
        System.out.format("Dia da Semana: %s\n",e.diaSemana[valor]);

        // Exercício 2
        System.out.println ("== Data 1 ==");
        System.out.println ("Insere valores (dias,horas,minutos,segundos): ");
        int dias1 = sc.nextInt();
        int horas1 = sc.nextInt();
        int minutos1 = sc.nextInt();
        int segundos1 = sc.nextInt();
        System.out.println ("== Data 2 ==");
        System.out.println ("Insere valores (dias,horas,minutos,segundos): ");
        int dias2 = sc.nextInt();
        int horas2 = sc.nextInt();
        int minutos2 = sc.nextInt();
        int segundos2 = sc.nextInt();

        LocalTime horaInicial = LocalTime.of (horas1,minutos1,segundos1);
        LocalTime horaFinal = LocalTime.of (horas2,minutos2,segundos2);
        String res = e.somaDatas(dias1, horaInicial, dias2, horaFinal);
        System.out.format ("Resultado: %s\n",res);

        // Exercicío 3
        System.out.print ("Quantas notas deseja inserir: ");
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            System.out.print ("Nota obtida (0-20): ");
            float nota = sc.nextFloat();
            e.determinaIntervalo(nota);
        }

        e.outputClassificacoes();

        // Exercício 4
        System.out.print ("Quantas temperaturas deseja inserir (pelo menos duas): ");
        int N = sc.nextInt();
        int[] valores = new int[N];

        for (int i = 0; i < N; i++) {
            System.out.print ("Temperatura inteira registada: ");
            valores[i] = sc.nextInt();
        }

        ResultadosTemperaturas t = e.temperaturas(valores, N);
        e.outputTemperaturas(t, N);

        // Exercício 5
        while (true) {
            System.out.print ("Insere a base do triângulo (insere 0 para terminar): ");
            double base = sc.nextDouble();
            if (base == 0) break;
            System.out.print ("Insere a altura do triâgulo: ");
            double altura = sc.nextDouble();

            ResultadosTriangulo s = e.calculaValoresAP(base, altura);
            System.out.format ("Área: %.5f\n",s.area);
            System.out.format("Perímetro: %.5f\n", s.perimetro);
        }

        // Exercício 6
        boolean terminaJogo = false;
        while (!terminaJogo) {
            System.out.print("Insere um número inteiro: ");
            int nI = sc.nextInt();
            System.out.print("Números primos: ");
            for (int i = 1; i <= nI; i++) {
                if (e.serPrimo(i)) System.out.format("%d ",i);
            }
        
            System.out.print ("\nPretende jogar novamente? [S/N]: ");
            char resposta = sc.next().toUpperCase().charAt(0); // fica apenas com o primeiro char da string
            if (resposta == 'N') terminaJogo = true;
        }

        // Exercício 7
        sc.nextLine(); // limpar o buffer
        System.out.print ("Insere a tua data de nascimento (dd-mm-aaaa): ");
        String input = sc.nextLine();

        String[] partes = input.split("-");
        int day = Integer.parseInt(partes[0]);
        int month = Integer.parseInt(partes[1]);
        int year = Integer.parseInt(partes[2]);

        System.out.print ("Data e Hora Atual: ");
        System.out.print(LocalDateTime.now());
        long idadeH = e.idadeHoras(year,month,day);
        System.out.format ("\nIdade em horas: %d\n",idadeH);

        sc.close();


    }


}