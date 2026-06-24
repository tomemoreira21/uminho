public class Povoamento {

    public static CarRental povoar() throws Exception {
        CarRental cr = new CarRental();

        // Carro Elétrico
        CarroEletrico ce = new CarroEletrico(
            "E1", "Tesla", "Model 3",
            2022, 60.0, 400.0,
            0.0, 0.0,          // numeroKms, totaisKm
            75.0, 15.0, 0.20  // bateria
        );

        // Carro Combustão
        CarroCombustao cc = new CarroCombustao(
            "C1", "BMW", "320d",
            2020, 80.0, 600.0,
            0.0, 0.0,          // numeroKms, totaisKm
            50.0, 5.5, 1.80   // depósito
        );

        // Carro Híbrido
        CarroHibrido ch = new CarroHibrido(
            "H1", "Toyota", "Prius",
            2021, 70.0, 800.0,
            0.0, 0.0,          // numeroKms, totaisKm
            40.0, 4.0, 1.75,  // combustão
            8.0, 10.0, 0.18   // elétrico
        );

        cr.adiciona(ce);
        cr.adiciona(cc);
        cr.adiciona(ch);

        return cr;
    }
}