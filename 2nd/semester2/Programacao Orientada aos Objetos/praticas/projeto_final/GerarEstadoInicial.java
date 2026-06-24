import java.io.IOException;

public class GerarEstadoInicial {
    public static void main(String[] args) throws Exception {

        try {
            // 1. Criar sistema com povoamento
            CarRental cr = Povoamento.povoar();

            // 2. Guardar no ficheiro
            cr.guardaEstado("estado.dat");

            System.out.println("Ficheiro guardar.dat criado com sucesso!");

        } catch (IOException e) {
            System.out.println("Erro ao guardar estado: " + e.getMessage());
        }
    }
}