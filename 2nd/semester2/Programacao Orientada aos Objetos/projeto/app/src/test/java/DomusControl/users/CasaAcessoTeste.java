package DomusControl.users;

import DomusControl.home.Casa;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class CasaAcessoTeste {

    @Test
    void testConstrutores() {
        Utilizador u = new Utilizador("Joao", "j@x.com");
        Casa c = new Casa("Casa1");

        CasaAcesso ca = new CasaAcesso(u, c, Papel.ADMIN);

        assertEquals(u, ca.getUtilizador());
        assertEquals(c, ca.getCasa());
        assertEquals(Papel.ADMIN, ca.getPapel());

        CasaAcesso ca2 = new CasaAcesso(ca);
        assertEquals(ca, ca2);
    }

    @Test
    void testSettersGetters() {
        Utilizador u = new Utilizador("Ana", "a@x.com");
        Casa c = new Casa("Casa2");

        CasaAcesso ca = new CasaAcesso();

        ca.setUser(u);
        ca.setCasa(c);
        ca.setPapel(Papel.ADMIN);

        assertEquals(u, ca.getUtilizador());
        assertEquals(c, ca.getCasa());
        assertEquals(Papel.ADMIN, ca.getPapel());
    }

    @Test
    void testClone() {
        Utilizador u = new Utilizador("Joao", "j@x.com");
        Casa c = new Casa("Casa1");

        CasaAcesso ca1 = new CasaAcesso(u, c, Papel.USER);
        CasaAcesso ca2 = ca1.clone();

        assertEquals(ca1, ca2);
    }

    @Test
    void testEquals() {
        Utilizador u = new Utilizador("Joao", "j@x.com");
        Casa c = new Casa("Casa1");

        CasaAcesso ca1 = new CasaAcesso(u, c, Papel.ADMIN);
        CasaAcesso ca2 = new CasaAcesso(u, c, Papel.ADMIN);
        CasaAcesso ca3 = new CasaAcesso(u, c, Papel.USER);

        assertEquals(ca1, ca2);
        assertNotEquals(ca1, ca3);
    }

    @Test
    void testIsAdminIsUser() {
        Utilizador u = new Utilizador("Joao", "j@x.com");
        Casa c = new Casa("Casa1");

        CasaAcesso admin = new CasaAcesso(u, c, Papel.ADMIN);
        CasaAcesso user = new CasaAcesso(u, c, Papel.USER);

        assertTrue(admin.isAdmin());
        assertFalse(admin.isUser());

        assertTrue(user.isUser());
        assertFalse(user.isAdmin());
    }
}
