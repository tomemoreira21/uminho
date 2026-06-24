package DomusControl.device;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;

public class SensorChuvaTeste {

    @Test
    void testSensorChuvaValorCloneEquals() throws Exception {
        SensorChuva s1 = new SensorChuva("s1", "netatmo", "rain", 0.5);

        s1.setValor(25.5);
        assertEquals(25.5, s1.getValor());

        SensorChuva s2 = s1.clone();
        assertEquals(s1, s2);

        s2.setValor(80.0);
        assertEquals(80.0, s2.getValor());
        assertNotEquals(s1, s2);
    }

    @Test
    void testSensorChuvaLigadoConsistencia() {
        SensorChuva s = new SensorChuva("s1", "netatmo", "rain", 0.5);

        s.ligar(LocalDateTime.now());
        assertTrue(s.isLigado());

        s.desligar(LocalDateTime.now());
        assertFalse(s.isLigado());
    }
}