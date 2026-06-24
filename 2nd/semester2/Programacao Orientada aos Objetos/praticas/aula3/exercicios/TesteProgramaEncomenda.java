import java.time.LocalDateTime;

public class TesteProgramaEncomenda {
    public static void main(String[] args) {
        Produto p1 = new Produto("P001", "Teclado Mecânico", 50.0);
        Produto p2 = new Produto("P002", "Mouse Gamer", 30.0);
        Produto p3 = new Produto("P003", "Monitor 24", 150.0);
        Produto p4 = new Produto("P004", "Headset", 40.0);
        Produto p5 = new Produto("P005", "Webcam", 25.0);
        Produto p6 = new Produto("P006", "Mousepad", 10.0);

        LinhaDeEncomenda l1 = new LinhaDeEncomenda(p1, 2, 10);
        LinhaDeEncomenda l2 = new LinhaDeEncomenda(p2, 1, 10);
        LinhaDeEncomenda l3 = new LinhaDeEncomenda(p3, 3, 10);
        LinhaDeEncomenda l4 = new LinhaDeEncomenda(p4, 2, 10);
        LinhaDeEncomenda l5 = new LinhaDeEncomenda(p5, 4, 10);
        LinhaDeEncomenda l6 = new LinhaDeEncomenda(p6, 5, 10);

        Cliente c1 = new Cliente("Júlio Alecrim", 8921828, "Maximinense, Braga");
        Encomenda e1 = new Encomenda(c1,LocalDateTime.of(2026, 1, 20, 16, 0));
        e1.adicionaLinha(l1);
        e1.adicionaLinha(l2);
        e1.adicionaLinha(l4);
        
        Cliente c = new Cliente("Tomé Moreira", 81292918, "PVL, Lanhoso");
        Encomenda e = new Encomenda(c, LocalDateTime.now());
        e.adicionaLinha(l1);
        e.adicionaLinha(l2);
        e.adicionaLinha(l3);
        e.adicionaLinha(l4);
        e.adicionaLinha(l5);
        e.adicionaLinha(l6);

        System.out.format ("---------------------------- Encomenda %d  ------------------------------\n",e1.getNumero());
        System.out.println (e1.toString());

        System.out.format ("---------------------------- Encomenda %d ------------------------------\n",e.getNumero());
        System.out.println (e.toString());

        System.out.format ("Valor Total: %.2f\n",e.calculaValorTotal());
        System.out.format ("Valor Total Desconto: %.2f\n",e.calculaValorDesconto());
        System.out.format("Nº Total de Produtos: %d\n",e.numeroTotalProdutos());
        System.out.println("Existe (P005): " + e.existeProdutoEncomenda("P005"));
        System.out.println("Existe (P007): " + e.existeProdutoEncomenda("P007"));

        e.removeProduto("P003");
        e.removeProduto("28218082108");
        System.out.format ("\nEstado da Encomenda %d após a remoção do produto P003\n",e.getNumero());
        System.out.print(e.toString());
    }
    

}
