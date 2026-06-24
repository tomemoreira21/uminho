package DomusControl.analysis;

import org.junit.jupiter.api.Test;

import DomusControl.automation.actions.TipoAcao;
import DomusControl.device.Dispositivo;
import DomusControl.device.Lampada;
import DomusControl.users.Utilizador;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class PadraoTeste {

    @Test
    void testArredondamentoIntervalo() {
        Padrao.setIntervaloMinutos(10);

        LocalDateTime t = LocalDateTime.of(2025, 1, 1, 14, 47);

        Dispositivo d = new Lampada("123", "Goove", "XPTO", 1.0);
        Utilizador u = new Utilizador("João", "joao@gmail.com");

        Padrao p = new Padrao(t, TipoAcao.LIGAR, d.getId() , u.getEmail());

        assertEquals(40, p.getHoraAprox().getMinute());
    }

    @Test
    void testEqualsHashCode() {
        LocalDateTime t1 = LocalDateTime.of(2025, 1, 1, 14, 12);
        LocalDateTime t2 = LocalDateTime.of(2025, 1, 2, 14, 14);

        Padrao.setIntervaloMinutos(10);

        Dispositivo d = new Lampada("123", "Goove", "XPTO", 1.0);
        Utilizador u = new Utilizador("João", "joao@gmail.com");

        Padrao p1 = new Padrao(t1, TipoAcao.LIGAR, d.getId(), u.getEmail());
        Padrao p2 = new Padrao(t2, TipoAcao.LIGAR, d.getId(), u.getEmail());

        assertEquals(p1, p2); // mesma hora arredondada
        assertEquals(p1.hashCode(), p2.hashCode());
    }
}