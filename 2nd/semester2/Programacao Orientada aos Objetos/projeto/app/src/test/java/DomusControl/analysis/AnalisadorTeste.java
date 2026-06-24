package DomusControl.analysis;

import org.junit.jupiter.api.Test;

import DomusControl.device.Dispositivo;
import DomusControl.device.Lampada;
import DomusControl.users.Utilizador;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

public class AnalisadorTeste {

    @Test
    void testNaoContaRepeticoesMesmoDia() {
        Analisador a = new Analisador();

        Dispositivo d = new Lampada("123", "Goove", "XPTO", 1.0);
        Utilizador u = new Utilizador("João", "joao@gmail.com");

        LocalDateTime t = LocalDateTime.of(2025, 1, 1, 14, 5);

        Padrao p1 = new Padrao(t, null, d.getId(), u.getEmail());
        Padrao p2 = new Padrao(t.plusMinutes(2), null, d.getId(), u.getEmail());

        a.registarPadrao(p1,t);
        a.registarPadrao(p2,t); // mesmo dia → não deve contar

        assertEquals(1, a.getBuffer().values().iterator().next());
    }

    @Test
    void testContaDiasDiferentes() {
        Analisador a = new Analisador();

        Dispositivo d = new Lampada("123", "Goove", "XPTO", 1.0);
        Utilizador u = new Utilizador("João", "joao@gmail.com");

        LocalDateTime t1 = LocalDateTime.of(2025, 1, 1, 14, 5);
        LocalDateTime t2 = LocalDateTime.of(2025, 1, 2, 14, 5);

        Padrao p1 = new Padrao(t1, null, d.getId(), u.getEmail());
        Padrao p2 = new Padrao(t2, null, d.getId(), u.getEmail());

        a.registarPadrao(p1,t1);
        a.registarPadrao(p2,t2);

        assertEquals(2, a.getBuffer().values().iterator().next());
    }

    @Test
    void testAgrupamentoIntervalo() {
        Analisador a = new Analisador();

        Dispositivo d = new Lampada("123", "Goove", "XPTO", 1.0);
        Utilizador u = new Utilizador("João", "joao@gmail.com");

        LocalDateTime t1 = LocalDateTime.of(2025, 1, 1, 14, 0);
        LocalDateTime t2 = LocalDateTime.of(2025, 1, 1, 14, 8);

        Padrao p1 = new Padrao(t1, null, d.getId(), u.getEmail());
        Padrao p2 = new Padrao(t2, null, d.getId(), u.getEmail());

        for (int i = 0; i < 10; i++) {
            a.registarPadrao(p1,t1);
            a.registarPadrao(p2,t2);
        }

        assertTrue(a.getBuffer().size() >= 1);
    }
}