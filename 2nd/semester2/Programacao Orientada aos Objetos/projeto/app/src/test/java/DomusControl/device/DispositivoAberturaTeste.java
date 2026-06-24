package DomusControl.device;

import org.junit.jupiter.api.Test;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class DispositivoAberturaTeste {

    @Test
    void testConsumoAbrirTotal() {
        Cortina c = new Cortina("C1","M","X",10.0,0.05);

        c.abrir();

        // consumo = tempoTotal * consumoPorHora
        double esperado = c.getTempoTotal() * c.getConsumoPorHora();
        LocalDateTime agora = LocalDateTime.now();

        assertTrue(c.consumoTotal(agora) > 0);
        assertEquals(esperado, c.consumoTotal(agora), 0.0001);
    }

    @Test
    void testConsumoParcial() throws Exception {
        Cortina c = new Cortina("C1","M","X",10.0,0.05);

        c.setAbertura(50); // metade → metade do tempo

        double esperado = (0.5 * c.getTempoTotal()) * c.getConsumoPorHora();

        assertEquals(esperado, c.consumoTotal(LocalDateTime.now()), 0.0001);
    }

    @Test
    void testAbrirEFechar() {
        PortaoGaragem p = new PortaoGaragem("P1","M","X",10.0,0.03);

        p.abrir();
        p.fechar();

        double esperado = 2 * p.getTempoTotal() * p.getConsumoPorHora();

        assertEquals(esperado, p.consumoTotal(LocalDateTime.now()), 0.0001);
    }

    @Test
    void testSemAlteracoesSemConsumo() {
        Cortina c = new Cortina("C1","M","X",10.0,0.03);

        assertEquals(0.0, c.consumoTotal(LocalDateTime.now()), 0.0001);
    }
}