package aula2.exercicios;

import java.util.Arrays;

public class Exercicio4 {

    public String[] removeRepetidas (String[] palavras) {
        String[] semRepetidas = new String[palavras.length];
        int k = 0;  

        for (String s : palavras) {
            if (!existeString(semRepetidas,s)) {
                semRepetidas[k++] = s;
            }
        }

        return Arrays.copyOf(semRepetidas, k);
    }

    public String maiorString (String[] palavras) {
        String maxString = palavras[0];
        int maxSize = maxString.length();
        
        for (int i = 1; i < palavras.length; i++) {
            if (palavras[i].length() > maxSize) {
                maxSize = palavras[i].length();
                maxString = palavras[i];
            }
        }

        return maxString;
    }

    private boolean existeString(String[] palavras,String p) {
        for (String s : palavras) {
            if (s == null) return false;
            if (s.equals(p)) return true;
        }

        return false;
    }   
    
    public String[] repetidasString (String[] palavras) {
        String[] repetidas = new String[palavras.length];
        int k = 0;

        for (String p : palavras) {
            int count = contaString(palavras, p);
            if (count > 1 && !existeString(repetidas, p)) {
                repetidas[k++] = p;
            }
        }

        return Arrays.copyOf(repetidas, k); // devolve até ao k
    }

    public int contaString (String[] palavras,String p) {
        int count = 0;

        for (String s : palavras) {
            if (s.equals(p)) count++;
        }
        
        return count;
    }


}
