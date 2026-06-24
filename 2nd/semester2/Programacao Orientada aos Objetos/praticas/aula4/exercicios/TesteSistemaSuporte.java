import java.time.LocalDateTime;

public class TesteSistemaSuporte {
    public static void main (String[] args) {
        SistemadeSuporte sistema = new SistemadeSuporte();

        // criar pedidos
        PedidoSuporte p1 = new PedidoSuporte(
                "joao",
                LocalDateTime.now(),
                "Problema PC",
                "Computador não liga"
        );

        PedidoSuporte p2 = new PedidoSuporte(
                "maria",
                LocalDateTime.now().minusMinutes(5),
                "Internet",
                "Sem acesso à rede"
        );

        PedidoSuporte p3 = new PedidoSuporte(
                "julio",
                LocalDateTime.now().minusMinutes(10),
                "Problema Keyboard",
                "Teclas partidas"
        );

        // inserir pedidos
        sistema.inserePedido(p1);
        sistema.inserePedido(p2);
        sistema.inserePedido(p3);

        // resolver pedidos
        sistema.resolvePedido(p1, "Carlos", "Fonte de alimentação trocada");
        sistema.resolvePedido(p2, "Ana", "Router reiniciado");
        sistema.resolvePedido(p3, "Carlos", "Alteração da tipologia de rede");

        // procurar pedido
        PedidoSuporte encontrado = sistema.procuraPedido("joao", p1.getDataPedido());
        if (encontrado != null) {
            System.out.println("Pedido encontrado: " + encontrado.getAssunto());
        }

        // listar resolvidos
        System.out.println("Pedidos resolvidos: " + sistema.resolvidos().size());

        // colaborador com mais resoluções
        System.out.println("Top técnico: " + sistema.colaboradorTop());

        // tempo médio de resolução
        System.out.println("Tempo médio: " + sistema.tempoMedioResolucao() + " minutos");

        // pedido mais longo
        PedidoSuporte maisLongo = sistema.pedidoMaisLongo();
        if (maisLongo != null) {
            System.out.println("Pedido mais longo: " + maisLongo.getAssunto());
        }

        // pedido mais curto
        PedidoSuporte maisCurto = sistema.pedidoMaisCurto();
        if (maisCurto != null) {
            System.out.println("Pedido mais curto: " + maisCurto.getAssunto());
        }



    }
}
