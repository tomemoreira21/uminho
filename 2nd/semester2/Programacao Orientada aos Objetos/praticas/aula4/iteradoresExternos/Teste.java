import java.util.*;

public class Teste {
    public static void main (String[] args) {
        ArrayList<String> nomes = new ArrayList<>();
        nomes.add("Ana");
        nomes.add("Bruno");
        nomes.add("Carla");

        Iterator<String> it = nomes.iterator();

        while (it.hasNext()) {
            String nome = it.next();
            
            if (nome.startsWith("B")) {
                it.remove();
            }
        }

        System.out.println(nomes);
    }
}
