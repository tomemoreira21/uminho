
public class TesteProgramaLampada {

    public static void main(String[] args) throws InterruptedException {
        Lampada l = new Lampada(2, 1);

        System.out.println("Estado inicial: " + l.getEstado());
        System.out.println("Custo inicial: " + l.getCustoTotal());

        // Liga a lâmpada
        l.lampON();
        System.out.println("\nLigou (ON)");
        Thread.sleep(2000); // 2 segundos

        l.lampOFF();
        System.out.println("Desligou (OFF)");
        System.out.printf("Custo após ON: %.6f%n", l.getCustoTotal()); // 2000 *2 = 4000

        // Modo ECO
        l.lampECO();
        System.out.println("\nMudou para ECO");
        Thread.sleep(3000); // 3 segundos 

        l.lampOFF();
        System.out.println("Desligou (OFF)");
        System.out.printf("Custo após ECO: %.6f%n", l.getCustoTotal()); // 4000 + 3000 = 7000

        System.out.println("\nCusto total final: " + l.getCustoTotal());
    }
}

