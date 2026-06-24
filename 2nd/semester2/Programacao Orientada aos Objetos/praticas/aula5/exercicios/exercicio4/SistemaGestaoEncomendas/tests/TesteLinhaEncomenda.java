import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TesteLinhaEncomenda {
    
   @Test
    public void testaCalculaValorLinhaEnc() {
        Produto p = new Produto("P1","keyboard", 100.0); // adapta ao teu construtor
        LinhaDeEncomenda l = new LinhaDeEncomenda(p, 2, 10);

        double esperado = 100 * 2;          // 200
        esperado *= 0.9;                    // desconto 10% → 180
        esperado *= 1.23;                   // imposto 23% → 221.4

        assertEquals(esperado, l.calculaValorLinhaEnc(), 0.001);
    }

    @Test
    public void testaCalculaValorDesconto() {
        Produto p = new Produto("P1","keyboard", 100.0); 
        LinhaDeEncomenda l = new LinhaDeEncomenda(p, 2, 10);

        double esperado = 0.10 * (100 * 2); // 20

        assertEquals(esperado, l.calculaValorDesconto(), 0.001);
    }

    @Test
    public void testaConstrutor() {
        Produto p = new Produto("P1","keyboard", 50.0); 
        LinhaDeEncomenda l = new LinhaDeEncomenda(p, 3, 5);

        assertEquals(3, l.getQuantidade());
        assertEquals(5, l.getDescontoComercial());
        assertEquals(50.0, l.getProduto().getPreco(), 0.001);
    }

    @Test
    public void testaEquals() {
        Produto p1 = new Produto("P1","keyboard", 100.0); 
        Produto p2 = new Produto("P1","keyboard", 100.0); 

        LinhaDeEncomenda l1 = new LinhaDeEncomenda(p1, 2, 10);
        LinhaDeEncomenda l2 = new LinhaDeEncomenda(p2, 2, 10);

        assertTrue(l1.equals(l2), "Os objetos não são iguais");
    }

}



