package DomusControl.device;

import org.junit.jupiter.api.Test;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class ReleTeste {

    @Test
    void testConstrutores() {
        Rele r = new Rele("R1", "MarcaR", "ModeloR", 5.0);

        assertEquals("R1", r.getId());
        assertEquals("MarcaR", r.getMarca());
        assertEquals("ModeloR", r.getModelo());
        assertEquals(5.0, r.getConsumoPorHora());
        assertFalse(r.isLigado());
    }

    @Test
    void testLigarDesligar() {
        Rele r = new Rele();

        LocalDateTime t1 = LocalDateTime.of(2026,1,1,10,0);
        LocalDateTime t2 = LocalDateTime.of(2026,1,1,12,0);

        r.ligar(t1);
        assertTrue(r.isLigado());

        r.desligar(t2);
        assertFalse(r.isLigado());
    }

    @Test
    void testConsumoTempoLigado() {
        Rele r = new Rele("R1", "M", "X", 10.0);

        LocalDateTime t1 = LocalDateTime.of(2026,1,1,10,0);
        LocalDateTime t2 = LocalDateTime.of(2026,1,1,12,0);

        r.ligar(t1);

        double consumo = r.consumoTotal(t2);

        assertTrue(consumo > 0);
    }

    @Test
    void testClone() {
        Rele r1 = new Rele("R1", "M", "X", 10.0);
        r1.ligar(LocalDateTime.of(2026,1,1,10,0));

        Rele r2 = r1.clone();

        assertEquals(r1, r2);
    }
}