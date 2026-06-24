package DomusControl.device;

import org.junit.jupiter.api.Test;

import DomusControl.exceptions.dispositivo.VolumeInvalidoException;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class ColunaSomTeste {

    @Test
    void testConstrutores() {
        ColunaSom c1 = new ColunaSom("CS1", "MarcaC", "ModeloC", 10.0);

        assertEquals("CS1", c1.getId());
        assertEquals("MarcaC", c1.getMarca());
        assertEquals("ModeloC", c1.getModelo());
        assertEquals(10.0, c1.getConsumoPorHora());
        assertEquals(0, c1.getVolume());
        assertFalse(c1.isLigado());

        ColunaSom c2 = new ColunaSom(c1);
        assertEquals(c1, c2);
    }

    @Test
    void testVolume() {
        ColunaSom c = new ColunaSom();

        // válido
        assertDoesNotThrow(() ->  c.setVolume(50));
        assertEquals(50, c.getVolume());

        // inválido -> negativo
        assertThrows(VolumeInvalidoException.class, () -> c.setVolume(-10));
        assertEquals(50, c.getVolume()); // não altera o valor

        // inválido acima de 100
        assertThrows(VolumeInvalidoException.class, () -> c.setVolume(120));
        assertEquals(50, c.getVolume());
    }

    @Test
    void testLigarComVolume()  throws Exception {
        ColunaSom c = new ColunaSom();

        LocalDateTime t1 = LocalDateTime.of(2026, 1, 1, 10, 0);

        c.ligar(t1, 80);

        assertTrue(c.isLigado());
        assertEquals(80, c.getVolume());
        assertEquals(c.getNumAtivacoes(),1);
    }

    @Test
    void testDesligarResetVolume() throws Exception {
        ColunaSom c = new ColunaSom();

        LocalDateTime t1 = LocalDateTime.of(2026, 1, 1, 10, 0);
        LocalDateTime t2 = LocalDateTime.of(2026, 1, 1, 12, 0);

        c.ligar(t1, 60);
        c.desligar(t2);

        assertFalse(c.isLigado());
        assertEquals(0, c.getVolume());
    }

    @Test
    void testClone() throws Exception {
        ColunaSom c1 = new ColunaSom("CS1", "MarcaC", "ModeloC", 10.0);
        c1.ligar(LocalDateTime.of(2026,1,1,10,0), 70);

        ColunaSom c2 = c1.clone();

        assertEquals(c1, c2);
    }
}