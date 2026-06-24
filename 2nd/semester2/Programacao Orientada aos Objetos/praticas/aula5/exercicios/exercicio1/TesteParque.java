public class TesteParque {
    public static void main(String[] args) {
        // Criar um parque vazio
        Parque parque = new Parque();

        // Criar alguns lugares
        Lugar l1 = new Lugar("AA-00-11", "Joao", 30, true);
        Lugar l2 = new Lugar("BB-22-33", "Maria", 15, false);
        Lugar l3 = new Lugar("CC-44-55", "Pedro", 45, true);

        // Registar ocupações
        parque.registaOcupacao(l1);
        parque.registaOcupacao(l2);
        parque.registaOcupacao(l3);

        // Testar todas as matrículas
        System.out.println("Matriculas: " + parque.todasMatriculas());

        // Testar total de minutos
        System.out.println("Total minutos (v1): " + parque.quantidadeTotalMinutos_v1());
        System.out.println("Total minutos (v2): " + parque.quantidadeTotalMinutos_v2());

        // Testar existência
        System.out.println("Existe AA-00-11? " + parque.existeLugar("AA-00-11"));

        // Alterar tempo
        parque.alteraTempo("BB-22-33", 50);

        // Testar filtro (tempo > 20 e permanente)
        System.out.println("Matriculas com tempo > 20 e permanentes:");
        System.out.println(parque.matriculasTempo_v1(20));
        System.out.println(parque.matriculasTempo_v2(20));

        // Devolver lugar
        Lugar l = parque.devolveLugar("AA-00-11");
        System.out.println("Lugar devolvido: " + l.getMatricula() + " - " + l.getMinutos());

        // Remover lugar
        parque.removeLugar("CC-44-55");
        System.out.println("Depois de remover CC-44-55: " + parque.todasMatriculas());
    }
}