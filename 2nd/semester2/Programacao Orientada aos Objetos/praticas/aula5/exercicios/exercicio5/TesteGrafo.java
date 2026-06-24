public class TesteGrafo {
    public static void main(String[] args) {
        Grafo g = new Grafo();

        // Construir grafo
        g.addArco(1, 2);
        g.addArco(1, 3);
        g.addArco(2, 4);
        g.addArco(3, 4);
        g.addArco(4, 5);
        g.addArco(6, 6); // ciclo (self-loop)

        // isSink
        System.out.println("isSink(5): " + g.isSink(5)); // true
        System.out.println("isSink(1): " + g.isSink(1)); // false

        // isSource
        System.out.println("isSource(1): " + g.isSource(1)); // true
        System.out.println("isSource(4): " + g.isSource(4)); // false

        // size
        System.out.println("Tamanho do grafo (n + m): " + g.size());

        // haCaminho
        System.out.println("Ha caminho 1 -> 5: " + g.haCaminho(1, 5)); // true
        System.out.println("Ha caminho 2 -> 3: " + g.haCaminho(2, 3)); // false

        // getCaminho
        System.out.println("Caminho 1 -> 5: " + g.getCaminho(1, 5));
        System.out.println("Caminho 2 -> 3: " + g.getCaminho(2, 3)); // null

        // fanOut
        System.out.println("fanOut(1): " + g.fanOut(1));

        // fanIn
        System.out.println("fanIn(4): " + g.fanIn(4));

        // Subgrafo
        Grafo g2 = new Grafo();
        g2.addArco(1, 2);
        g2.addArco(2, 4);

        System.out.println("g2 é subgrafo de g: " + g2.subGrafo(g)); // true
        System.out.println("g é subgrafo de g2: " + g.subGrafo(g2)); // false
    }
}
