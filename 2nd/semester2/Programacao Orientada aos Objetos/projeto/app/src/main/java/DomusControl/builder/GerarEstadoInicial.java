package DomusControl.builder;

import DomusControl.DomusControl;

public class GerarEstadoInicial {
    public static void main(String[] args) {
        try {
            DomusControl dc = SetupInicial.criarEstado();
            dc.guardarEstado("app/estado.dat");
            System.out.println("Estado guardado com sucesso!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}