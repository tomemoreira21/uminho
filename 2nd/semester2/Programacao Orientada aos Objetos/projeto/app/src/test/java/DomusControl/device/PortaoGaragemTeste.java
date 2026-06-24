package DomusControl.device;

import org.junit.jupiter.api.Test;

import DomusControl.exceptions.dispositivo.AberturaInvalidaException;

import static org.junit.jupiter.api.Assertions.*;

public class PortaoGaragemTeste {

    @Test
    void testPortaoBasico() {
        PortaoGaragem p = new PortaoGaragem("P1","MarcaP","ModeloP",10,0.03);

        // válido
        assertDoesNotThrow(() ->  p.setAbertura(30));
        assertEquals(30, p.getAbertura());

        // inválido -> valor negativo
        assertThrows(AberturaInvalidaException.class, () ->  p.setAbertura(-1));
        assertEquals(30, p.getAbertura());
        
        // inválido -> valor acima de 100
        assertThrows(AberturaInvalidaException.class, () ->  p.setAbertura(130));
        assertEquals(30, p.getAbertura());

        p.abrir();
        assertEquals(100, p.getAbertura());

        p.fechar();
        assertEquals(0, p.getAbertura());
    }

    @Test
    void testCloneEEquals() throws Exception {
        PortaoGaragem p1 = new PortaoGaragem("P1","MarcaP","ModeloP",10,0.03);
        p1.setAbertura(70);

        PortaoGaragem p2 = p1.clone();

        assertEquals(p1, p2);
        assertNotSame(p1, p2);
    }

    @Test
    void testEstados() {
        PortaoGaragem p = new PortaoGaragem("P1","MarcaP","ModeloP",10,0.03);

        assertTrue(p.isFechada());
        assertFalse(p.isAberta());

        p.abrir();

        assertTrue(p.isAberta());
        assertFalse(p.isFechada());
    }
}