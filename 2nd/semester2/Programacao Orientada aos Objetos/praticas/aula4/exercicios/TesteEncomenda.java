import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class TesteEncomenda {
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
        List<LinhaDeEncomenda> linhaE1 = new ArrayList<LinhaDeEncomenda>(); 
        Encomenda e1 = new Encomenda(c1,LocalDate.of(2026, 1, 20),linhaE1);
        e1.adicionaLinha(l1);
        e1.adicionaLinha(l2);
        e1.adicionaLinha(l4);


        Cliente c2 = new Cliente("Tomé Moreira", 81292918, "PVL, Lanhoso");
        List<LinhaDeEncomenda> linhaE2 = new ArrayList<LinhaDeEncomenda>(); 
        Encomenda e2 = new Encomenda(c2, LocalDate.now(),linhaE2);
        e2.adicionaLinha(l1);
        e2.adicionaLinha(l2);
        e2.adicionaLinha(l3);
        e2.adicionaLinha(l4);
        e2.adicionaLinha(l5);
        e2.adicionaLinha(l6);

        List<Encomenda> listEncomendas1 = new ArrayList<Encomenda>();
        SistemaGestaoEncomendas sge1 = new SistemaGestaoEncomendas(listEncomendas1);
        sge1.insereEncomenda(e1);
        sge1.insereEncomenda(e2);

        System.out.format("---------------------------- Sistema Gestao 1 ------------------------------\n");
        System.out.println(sge1.toString());

        System.out.format("---------------------------- Pesquisa Encomenda ------------------------------\n");
        Encomenda enc = sge1.pesquisaNrEncomenda(e1.getNumero());

        if (enc != null) {
            System.out.println(enc.toString());
        }
        else {
            System.out.println("Encomenda não encontrada.");
        }

        System.out.format("\n---------------------------- Encomenda de Maior Valor ------------------------------\n");
        Encomenda maior = sge1.calculaEncMaiorValor();

        if (maior != null) {
            System.out.println(maior.toString());
            System.out.format("Valor Total: %.2f\n", maior.calculaValorTotal());
        }

        System.out.format("\n---------------------------- Numero Total de Produtos ------------------------------\n");
        System.out.println("Total de produtos no sistema: " + sge1.numeroTotalProdutos());

        System.out.format("\n---------------------------- Inserir Encomenda ------------------------------\n");
        Encomenda e3 = e1.clone();
        e3.setNumero(3);
        sge1.insereEncomenda(e3);
        System.out.println("Encomenda inserida.");
        System.out.println(sge1.toString());

        System.out.format("\n---------------------------- Remover Encomenda ------------------------------\n");
        sge1.removeEncomenda(e1.getNumero());
        System.out.println("Encomenda removida.");
        System.out.println(sge1.toString());
    }

}
