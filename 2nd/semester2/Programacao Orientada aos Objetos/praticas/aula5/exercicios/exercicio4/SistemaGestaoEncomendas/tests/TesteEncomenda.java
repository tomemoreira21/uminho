import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class TesteEncomenda {
     @Test
    public void testaConstrutorECopia() {
        Cliente c = new Cliente("Joao",19882, "PVL");
        LinhaDeEncomenda l1 = new LinhaDeEncomenda(new Produto("P1", "Keyboard", 100.0), 2, 10);
        List<LinhaDeEncomenda> linhas = new ArrayList<>();
        linhas.add(l1);

        Encomenda e = new Encomenda(c, LocalDate.of(2026, 3, 24), linhas);
        Encomenda copy = e.clone();

        assertEquals(e, copy, "Clone da encomenda deve ser igual à original");
        assertNotSame(e, copy, "Clone deve ser instância diferente da original");
    }

    @Test
    public void testaCalculaValorTotalEDesconto() {
        Produto p1 = new Produto("P1","Keyboard", 100.0);
        Produto p2 = new Produto("P2","Mouse", 50.0);

        LinhaDeEncomenda l1 = new LinhaDeEncomenda(p1, 2, 10); // 2*100*0.9*1.23 = 221.4
        LinhaDeEncomenda l2 = new LinhaDeEncomenda(p2, 1, 0);   // 1*50*1.23 = 61.5

        List<LinhaDeEncomenda> linhas = new ArrayList<>();
        linhas.add(l1);
        linhas.add(l2);

        Encomenda e = new Encomenda(new Cliente("Ana",19182, "PVL") ,LocalDate.now(), linhas);

        double esperadoTotal = 221.4 + 61.5;
        double esperadoDesconto = l1.calculaValorDesconto() + l2.calculaValorDesconto();

        assertEquals(esperadoTotal, e.calculaValorTotal(), 0.01, "Valor total calculado incorretamente");
        assertEquals(esperadoDesconto, e.calculaValorDesconto(), 0.01, "Desconto total calculado incorretamente");
    }

    @Test
    public void testaAdicionarERemoverLinha() {
        Produto p = new Produto("P1","Keyboard", 100.0);
        LinhaDeEncomenda l = new LinhaDeEncomenda(p, 2, 10);

        Encomenda e = new Encomenda();
        e.adicionaLinha(l);

        assertTrue(e.existeProdutoEncomenda("P1"), "Produto deve existir após adicionar linha");
        assertEquals(2, e.numeroTotalProdutos(), "Número total de produtos incorreto");

        e.removeProduto("P1");
        assertFalse(e.existeProdutoEncomenda("P1"), "Produto não deve existir após remover linha");
        assertEquals(0, e.numeroTotalProdutos(), "Número total de produtos deve ser 0 após remoção");
    }

    @Test
    public void testaEqualsEHashCode() {
        Cliente c1 = new Cliente("Joao",19882, "PVL");
        LinhaDeEncomenda l1 = new LinhaDeEncomenda(new Produto("P1","Keyboard",100.0), 1, 0);
        List<LinhaDeEncomenda> linhas = new ArrayList<>();
        linhas.add(l1);

        Encomenda e1 = new Encomenda(c1, LocalDate.now(), linhas);
        Encomenda e2 = new Encomenda(c1, LocalDate.now(), linhas);

        // pois o nr encomenda sao diferentes
        assertNotEquals(e1, e2, "Encomendas com mesmos dados devem ser iguais"); 
        assertNotEquals(e1.hashCode(), e2.hashCode(), "HashCode de encomendas iguais deve ser igual");

        // Teste de desigualdade
        e2.adicionaLinha(new LinhaDeEncomenda(new Produto("P2","Mouse",50.0),1,0));
        assertNotEquals(e1, e2, "Encomendas diferentes não devem ser iguais");
    }
}
