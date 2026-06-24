package DomusControl.device;

import org.junit.jupiter.api.Test;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class DispositivoOnOffTeste {

    @Test
    void testLigadoDesligadoConsumo() {
        Lampada l = new Lampada("L1","M","X",10.0);

        LocalDateTime t1 = LocalDateTime.of(2026,1,1,10,0);
        LocalDateTime t2 = LocalDateTime.of(2026,1,1,12,0);

        l.ligar(t1);
        l.desligar(t2);

        // 2 horas * 10 = 20
        assertEquals(20.0, l.consumoTotal(t2), 0.0001);
    }

    @Test
    void testConsumoEnquantoLigado() {
        Lampada l = new Lampada("L1","M","X",10.0);

        LocalDateTime t1 = LocalDateTime.of(2026,1,1,10,0);
        LocalDateTime t2 = LocalDateTime.of(2026,1,1,12,0);

        l.ligar(t1);

        double consumo = l.consumoTotal(t2);

        // 2 horas * 10 = 20
        assertEquals(20.0, consumo, 0.0001);
    }

    @Test
    void testNaoDesligadoNaoConsome() {
        Lampada l = new Lampada("L1","M","X",10.0);

        LocalDateTime t = LocalDateTime.of(2026,1,1,12,0);

        assertEquals(0.0, l.consumoTotal(t), 0.0001);
    }
}