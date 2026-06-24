package exerciciosI;

import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;

public class Exercicio {

    // Exercício 1
    int[] diasDoMes = { 
        31, // janeiro
        28, // fevereiro
        31, // março
        30, // abril
        31, // maio
        30, // junho
        31, // julho
        31, // agosto
        30, // setembro
        31, // outubro
        30, // novembro
        31  // dezembro
    };

    String[] diaSemana = {"Domingo","Segunda-Feira","Terça-Feira","Quarta-Feira","Quinta-Feira","Sexta-Feira","Sábado"};

    private boolean anoBissexto (int ano) {
        return ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0));
    }

    public int devolveDiaDaSemana (int dia,int mes,int ano) {
        int soma = (ano - 1900) * 365;
        soma += ((ano - 1900) / 4);

        if (anoBissexto(ano) && (mes == 1 || mes == 2))
                soma--;

        for (int i = 1; i < mes; i++) {
            soma += diasDoMes[i-1]; 
        }

        soma += dia;

        return soma % 7;
    }

    // Exercício 2
    public String somaDatas (int dias1,LocalTime data1,int dias2,LocalTime data2) {
        int somaDias = dias1 + dias2; 

        Duration d1 = Duration.ofHours(data1.getHour())
                    .plusMinutes(data1.getMinute())
                    .plusSeconds(data1.getSecond());

        Duration d2 = Duration.ofHours(data2.getHour())
                    .plusMinutes(data2.getMinute())
                    .plusSeconds(data2.getSecond());

        Duration total = d1.plus(d2);

        // dias extras vindos das horas
        somaDias += total.toDays();

        long segundosRestantes = total.minusDays(total.toDays()).getSeconds(); // obtém os segundos, tirando os dias
        long horas = segundosRestantes / 3600;
        long minutos = (segundosRestantes % 3600) / 60;
        long segundos = segundosRestantes % 60;

        return somaDias + "D " + horas + "H " + minutos + "M " + segundos + "S";
    }
    
    // Exercício 3
    int[] classificacoes = {
        0, // [0,5[
        0, // [5,10[
        0, // [10,15[
        0  // [15,20]
    };

    public void determinaIntervalo (float nota) {
        if (nota < 0 || nota > 20) return;

        int index;
        if (nota == 20) {
            index = 3;
        } else {
            index = (int)nota/5;
        }
        
        classificacoes[index]++;
    }

    public void outputClassificacoes () {
        System.out.format ("[0,5[ : %d notas\n",classificacoes[0]);
        System.out.format ("[5,10[ : %d notas\n",classificacoes[1]);
        System.out.format ("[10,15[ : %d notas\n",classificacoes[2]);
        System.out.format ("[15,20] : %d notas\n",classificacoes[3]);
    }

    // Exercício 4
    class ResultadosTemperaturas {
        float media;
        int maiorVariacao;
        int dia;
    }

    public ResultadosTemperaturas temperaturas (int[] valores,int n) {
        ResultadosTemperaturas res = new ResultadosTemperaturas();
        
        int soma = valores[0];
        res.maiorVariacao = 0;
        res.dia = 1;

        for (int i = 1; i < n; i++) {
            soma += valores[i];
            
            int dif = valores[i] - valores[i-1];

            if (Math.abs(dif) > Math.abs(res.maiorVariacao)) {
                res.maiorVariacao = dif;
                res.dia = i + 1;
            }
        }

        res.media = (float)soma/n;

        return res;
    }

    public void outputTemperaturas(ResultadosTemperaturas r,int n) {
        System.out.format ("A média das %d temperaturas foi de %.2f graus.\n",n,r.media);
        System.out.format ("A maior variação registou-se entre os dias %d e %d, tendo a temperatura %s %d graus.\n",
                r.dia - 1,r.dia,(r.maiorVariacao < 0) ? "descido" : "subido",Math.abs(r.maiorVariacao));
    }

    // Exercício 5
    class ResultadosTriangulo {
        double area;
        double perimetro;
    }

    public ResultadosTriangulo calculaValoresAP (double base,double altura) {
        ResultadosTriangulo res = new ResultadosTriangulo();

        double lado = Math.sqrt(Math.pow(base/2,2) + Math.pow(altura, 2));

        res.area = (base * altura) / 2;
        res.perimetro = lado*2 + base;

        return res;
    }

    // Exercício 6
    // se não consegues dividir o número por nenhum número entre 2 e n-1, para otimizar basta ir à raiz quadrada → é primo
    public boolean serPrimo (int n) {
        if (n <= 1) return false;

        for (int i = 2; i*i <= n; i++) {
            if (n % i == 0) return false;
        }

        return true;
    }

    // Exercício 7
    public long idadeHoras (int ano,int mes,int dia) {
        LocalDate dataNascimento = LocalDate.of (ano,mes,dia);
        LocalDate hoje = LocalDate.now();
        
        long dias = ChronoUnit.DAYS.between(dataNascimento, hoje);
        long horas = dias * 24;
    
        return horas;
    }

}
