import java.util.Arrays;

public class TesteCasaInteligente {
    public static void main(String[] args) throws InterruptedException {
        CasaInteligente casa = new CasaInteligente();

        // i. Layout
        casa.setUpLayout(Arrays.asList("Sala", "Quarto", "Cozinha"));
        System.out.println("Divisões existentes: Sala? " + casa.existeDivisao("Sala"));

        // ii. Adicionar lâmpadas
        Lampada l1 = new Lampada("L1", 10, 2);
        LampadaLed l2 = new LampadaLed("L2", 5, 1);
        Lampada l3 = new Lampada("L3", 8, 2);
        casa.addLampada(l1, "Sala");
        casa.addLampada(l2, "Sala");
        casa.addLampada(l3, "Quarto");

        // iv. Lâmpadas em divisão
        System.out.println("Lâmpadas na Sala:");
        for (Lampada l : casa.lampadasEmDivisao("Sala")) {
            System.out.println(" - " + l.getId());
        }

        // v. Set estado
        casa.setEstado("Sala", Lampada.Estado.ON);
        Thread.sleep(2000); // simula 2 segundos ligados
        System.out.println("Estado de L1 após set ON: " + casa.getLampadas().get("Sala").stream().filter(l -> l.getId().equals("L1"))
                                                                                                .findFirst().orElse(null));

        // vi. Divisão mais iluminada
        System.out.println("Divisão mais iluminada: " + casa.maisIluminada());

        // vii. Consumo total
        System.out.println("Consumo total da casa: " + casa.consumoCasa());

        // viii. Remover lâmpada
        Lampada removida = casa.removeLamp("L2");
        System.out.println("Lâmpada removida: " + (removida != null ? removida.getId() : "null"));
        System.out.println("Divisão Sala após remoção:");
        for (Lampada l : casa.lampadasEmDivisao("Sala")) {
            System.out.println(" - " + l.getId());
        }

        // ix. Lâmpada LED mais económica
        casa.setEstado("Sala", Lampada.Estado.OFF);
        LampadaLed ledEconomica = casa.maisEconomica();
        System.out.println("LED mais económica: " + (ledEconomica != null ? ledEconomica.getId() : "null"));
    }
}
