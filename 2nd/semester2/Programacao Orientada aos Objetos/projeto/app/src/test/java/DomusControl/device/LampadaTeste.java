package DomusControl.device;

import org.junit.jupiter.api.Test;

import DomusControl.exceptions.dispositivo.CorInvalidadeException;
import DomusControl.exceptions.dispositivo.IntensidadeInvalidaException;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class LampadaTeste {

    @Test
    void testConstrutores() {
        Lampada l = new Lampada("L1", "Philips", "X1", 5.0);

        assertEquals(0, l.getIntensidadeLuminosa());
        assertEquals(2700, l.getTemperaturaCor());
        assertFalse(l.isLigado());
    }

    @Test
    void testIntensidadeInvalida() {
        Lampada l = new Lampada();

        // valor negativo
        assertThrows(IntensidadeInvalidaException.class, () -> 
            l.setIntensidadeLuminosa(-10)
        );

        // valor acima de 100
        assertThrows(IntensidadeInvalidaException.class, () -> 
            l.setIntensidadeLuminosa(150)
        );
    }

    @Test
    void testTemperaturaCorInvalida() {
        Lampada l = new Lampada();

        // abaixo do mínimo
        assertThrows(CorInvalidadeException.class, () -> 
            l.setTemperaturaCor(2000)
        );

        // acima do máximo
        assertThrows(CorInvalidadeException.class, () -> 
            l.setTemperaturaCor(5000)
        );
    }

    @Test
    void testLigarDefault() {
        Lampada l = new Lampada();

        l.ligar(LocalDateTime.of(2026,1,1,10,0));

        assertTrue(l.isLigado());
        assertEquals(50, l.getIntensidadeLuminosa());
        assertEquals(2700, l.getTemperaturaCor());
    }

    @Test
    void testLigarComValores() throws Exception {
        Lampada l = new Lampada();

        l.ligar(LocalDateTime.of(2026,1,1,10,0), 80, 3000);

        assertEquals(80, l.getIntensidadeLuminosa());
        assertEquals(3000, l.getTemperaturaCor());
    }

    @Test
    void testDesligar() throws Exception {
        Lampada l = new Lampada();

        l.ligar(LocalDateTime.of(2026,1,1,10,0), 70, 3000);
        l.desligar(LocalDateTime.of(2026,1,1,12,0));

        assertFalse(l.isLigado());
        assertTrue(l.consumoTotal(LocalDateTime.of(2026,1,1,12,0)) > 0);
        assertEquals(0, l.getIntensidadeLuminosa());
    }

    @Test
    void testClone() throws Exception {
        Lampada l1 = new Lampada("L1", "Philips", "X1", 5.0);
        l1.ligar(LocalDateTime.of(2026,1,1,10,0), 70, 3000);

        Lampada l2 = l1.clone();

        assertEquals(l1, l2);
    }
}