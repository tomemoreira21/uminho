public class TesteProgramaCarro {
    public static void main(String[] args) {

        // Criar carro
        Carro c1 = new Carro("Tesla", "Model S", 2024,
                             0.20,   // consumo por km a 100 km/h
                             0,      // distancia total
                             0,      // media inicio
                             0,      // distancia ultima
                             0,      // energia total
                             0,      // media ultima
                             0.05,   // regeneração por km
                             Carro.Estado.OFF);

        // Mostrar estado inicial
        System.out.println("Estado inicial:");
        System.out.println("Estado: " + c1.getEstado());
        System.out.println("Distância total: " + c1.getDistanciaTotalKm());
        System.out.println("Energia total: " + c1.getEnergiaTotalConsumida());
        System.out.println("----------------------------------");

        // Ligar carro
        c1.ligaCarro();
        System.out.println("Carro ligado: " + c1.getEstado());

        // Avançar 5000 metros a 120 km/h
        c1.avancaCarro(5000, 120);

        System.out.println("\nApós avançar 5km a 120km/h:");
        System.out.println("Distância total: " + c1.getDistanciaTotalKm());
        System.out.println("Energia total: " + c1.getEnergiaTotalConsumida());
        System.out.println("Distância última viagem: " + c1.getDistanciaUltimaKm());
        System.out.println("Média última viagem: " + c1.getMediaConsumoUltima());
        System.out.println("Média desde início: " + c1.getMediaConsumoInicio());
        System.out.println("----------------------------------");

        // Travar 1000 metros
        c1.travaCarro(1000);

        System.out.println("\nApós travar 1km:");
        System.out.println("Energia total: " + c1.getEnergiaTotalConsumida());
        System.out.println("Média desde início: " + c1.getMediaConsumoInicio());
        System.out.println("----------------------------------");

        // Nova viagem
        c1.avancaCarro(10000, 80);

        System.out.println("\nApós avançar 10km a 80km/h:");
        System.out.println("Distância total: " + c1.getDistanciaTotalKm());
        System.out.println("Energia total: " + c1.getEnergiaTotalConsumida());
        System.out.println("Média desde início: " + c1.getMediaConsumoInicio());
        System.out.println("----------------------------------");

        // Reset última viagem
        c1.resetUltimaViagem();
        System.out.println("\nApós reset última viagem:");
        System.out.println("Distância última: " + c1.getDistanciaUltimaKm());
        System.out.println("Média última: " + c1.getMediaConsumoUltima());

        // Desligar carro
        c1.desligaCarro();
        System.out.println("\nCarro desligado: " + c1.getEstado());
    }
}
