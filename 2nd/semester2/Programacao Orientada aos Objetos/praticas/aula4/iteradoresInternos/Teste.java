import java.util.*;

public class Teste {
    public static void main (String[] args) {
        ArrayList<String> nomes = new ArrayList<>();
        nomes.add("Julio");
        nomes.add("Carla");
        nomes.add("Bruno");

        long cont = nomes.stream().count();
        System.out.format ("Length: %d\n",cont);

        System.out.println(nomes.stream().reduce("",(a,b) -> a + b));

        System.out.println ("----------------------------");
        nomes.stream().map(nome -> nome.toUpperCase())
                     .forEach(nome -> System.out.println (nome));

        System.out.println ("----------------------------");
        System.out.println(nomes.stream().map(nome -> nome.toLowerCase()).toList());

        System.out.println ("----------------------------");
        System.out.println(nomes.stream() 
                .filter(nome -> !nome.startsWith("J")).toList());
    }
}
