package DomusControl.device;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;

public class SensorLuminosidadeTeste {

    @Test
    void testSensorLuminosidadeValorCloneEquals() throws Exception {
        SensorLuminosidade s1 = new SensorLuminosidade("l1", "philips", "light", 0.5);

        s1.setValor(10.0);
        assertEquals(10.0, s1.getValor());

        SensorLuminosidade s2 = s1.clone();
        assertEquals(s1, s2);

        s2.setValor(99.9);
        assertEquals(99.9, s2.getValor());
        assertNotEquals(s1, s2);
    }

    @Test
    void testSensorLuminosidadeLigadoConsistencia() {
        SensorLuminosidade s = new SensorLuminosidade("l1", "philips", "light", 0.5);

        s.ligar(LocalDateTime.now());
        assertTrue(s.isLigado());

        s.desligar(LocalDateTime.now());
        assertFalse(s.isLigado());
    }
}