package DomusControl.device;

import org.junit.jupiter.api.Test;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class DispositivoMedicaoTeste {

    @Test
    void testLigadoConsumoSensorChuva() throws Exception {
        SensorChuva s = new SensorChuva("s1", "netatmo", "rain", 10.0);

        LocalDateTime t1 = LocalDateTime.of(2026, 1, 1, 10, 0);
        LocalDateTime t2 = LocalDateTime.of(2026, 1, 1, 12, 0);

        s.ligar(t1);
        s.setValor(50.0);
        s.desligar(t2);

        // 2 horas * 10 = 20
        assertEquals(20.0, s.consumoTotal(t2), 0.0001);
        assertEquals(2, s.getNumAtivacoes());
    }

    @Test
    void testConsumoEnquantoLigadoSensorLuminosidade() throws Exception {
        SensorLuminosidade s = new SensorLuminosidade("l1", "philips", "light", 5.0);

        LocalDateTime t1 = LocalDateTime.of(2026, 1, 1, 10, 0);
        LocalDateTime t2 = LocalDateTime.of(2026, 1, 1, 12, 0);

        s.ligar(t1);
        s.setValor(30.0);

        double consumo = s.consumoTotal(t2);

        // 2 horas * 5 = 10
        assertEquals(10.0, consumo, 0.0001);
    }

    @Test
    void testNaoLigadoNaoConsomeSensor() throws Exception {
        SensorChuva s = new SensorChuva("s1", "netatmo", "rain", 10.0);

        LocalDateTime t = LocalDateTime.of(2026, 1, 1, 12, 0);

        s.setValor(70.0);

        assertEquals(0.0, s.consumoTotal(t), 0.0001);
    }

    @Test
    void testValorNaoAfetaConsumo() throws Exception {
        SensorLuminosidade s = new SensorLuminosidade("l1", "philips", "light", 8.0);

        LocalDateTime t1 = LocalDateTime.of(2026, 1, 1, 10, 0);
        LocalDateTime t2 = LocalDateTime.of(2026, 1, 1, 11, 0);

        s.ligar(t1);

        s.setValor(10.0);
        double c1 = s.consumoTotal(t2);

        s.setValor(90.0);
        double c2 = s.consumoTotal(t2);

        // consumo NÃO depende do valor
        assertEquals(c1, c2, 0.0001);
    }
}