import java.util.Set;

public class TesteCasaInteligente {

    public static void main(String[] args) {
        CasaInteligente casa = new CasaInteligente();

        casa.addLampada(new Lampada(2, 1));
        casa.addLampada(new Lampada(1, 2));
        casa.addLampada(new Lampada(1.1, 2.3));
        casa.addLampada(new Lampada(2, 2));
        casa.addLampada(new Lampada(0.5,0.2));
        casa.addLampada(new Lampada(0.1,0.3));

        System.out.print(casa.toString());
        System.out.println("Lampadas adicionadas.\n");

        casa.ligaLampadaNormal(0);
        System.out.println("Lampada 0 ligada em modo NORMAL.");

        casa.ligaLampadaEco(1);
        System.out.println("Lampada 1 ligada em modo ECO.");

        System.out.println("Quantidade em modo ECO: " + casa.qtEmEco());

        casa.removeLampada(3);
        System.out.println("Lampada da posição 3 removida.");

        casa.ligaTodasEco();
        System.out.println("Todas as lampadas em modo ECO.");
        System.out.println("Quantidade em modo ECO: " + casa.qtEmEco());

        casa.ligaTodasMax();
        System.out.println("Todas as lampadas em modo MAX.");

        System.out.println("Consumo total da casa: " + casa.consumoTotal() + "\n");

        System.out.println(casa.toString());
        Lampada maisGasta = casa.maisGastadora();
        System.out.println("Lampada mais gastadora: " + maisGasta.toString());

        casa.ligaLampadaEco(0);
        Set<Lampada> eco = casa.lampadasEmModoEco();
        System.out.println("Lampadas em modo ECO: " + eco.size());

        casa.reset();
        System.out.println("Reset efetuado.");

        System.out.println(casa.toString());

        Set<Lampada> top3 = casa.podiumEconomia();
        System.out.println("Top 3 lampadas mais economicas:");
        for (Lampada l : top3) {
            System.out.println(l);
        }
    }
}