package aula2.exercicios;

import java.time.LocalDate;

public class TesteProgramaEx2 {

    public static void main (String[] args) {
        LocalDate data1 = LocalDate.of(2026,1,2);
        LocalDate data2 = LocalDate.of (2026,1,15);
        LocalDate data3 = LocalDate.of (2026,2,4);
        LocalDate data4 = LocalDate.of (2026,2,6);
        LocalDate data5 = LocalDate.of (2026,2,13);

        Exercicio2 e = new Exercicio2();

        e.insereData(data1);
        e.insereData(data2);
        e.insereData(data3);
        e.insereData(data4);
        boolean res = e.insereData(data5);
        if (!res) 
            System.out.format ("Não foi possível inserir a data %s ...\n",data5.toString());

        System.out.print ("Datas Inseridas:");
        System.out.print(e.toString() + "\n");

        LocalDate maisProx = e.dataMaisProxima(LocalDate.now()); 
        System.out.format ("Data mais próxima de %s: ",LocalDate.now().toString());
        System.out.print (maisProx);

        String s = e.toString();
        System.out.print ("\nConcat das datas:");
        System.out.print(s + "\n");
    }       


}
