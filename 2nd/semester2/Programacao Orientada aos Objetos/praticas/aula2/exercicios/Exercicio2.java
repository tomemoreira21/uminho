package aula2.exercicios;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class Exercicio2 {
    private LocalDate[] datas = new LocalDate[4];

    public boolean insereData (LocalDate data) {
        int index = -1;
        
        for (int i = 0; i < datas.length; i++) {
            if (datas[i] == null) {
                index = i;
                break;
            }
        }

        if (index == -1) return false; // não existe espaço para inserir
        else {
            datas[index] = data;
            return true;
        }
    }

    public LocalDate dataMaisProxima (LocalDate data) {
        LocalDate maisRecente = null;
        long min_diff = Integer.MAX_VALUE;

        for (int i = 0; i < datas.length; i++) {
            if (datas[i] != null) {
                long dias_diff = ChronoUnit.DAYS.between(datas[i],data);

                if (dias_diff < 0) continue;

                if (dias_diff < min_diff) {
                        min_diff = dias_diff;
                        maisRecente = datas[i];
                }
            }
        }

        return maisRecente;
    }

    public String toString() {
        String concat = "";

        for (int i = 0; i < datas.length; i++) {
            concat += (" " + datas[i].toString());
        }

        return concat;
    }


}
