package DomusControl.device;

import org.junit.jupiter.api.Test;

import DomusControl.exceptions.dispositivo.AberturaInvalidaException;

import static org.junit.jupiter.api.Assertions.*;

public class CortinaTeste {

    @Test
    void testCortinaBasico() throws Exception {
        Cortina c = new Cortina("C1","MarcaC","ModeloC",5,0.05);

        c.setAbertura(60);
        assertEquals(60, c.getAbertura());

        c.abrir();
        assertEquals(100, c.getAbertura());

        c.fechar();
        assertEquals(0, c.getAbertura());
    }

    @Test
    void testCloneEEquals() throws Exception {
        Cortina c1 = new Cortina("C1","MarcaC","ModeloC",5,0.05);
        c1.setAbertura(40);

        Cortina c2 = c1.clone();

        assertEquals(c1, c2);
        assertNotSame(c1, c2);
    }

    @Test
    void testSetAberturaLimites() {
        Cortina c = new Cortina("C1","MarcaC","ModeloC",5,0.05);

        // inválido -> acima de 100
        assertThrows(AberturaInvalidaException.class, () ->  c.setAbertura(120)); 
        assertEquals(0, c.getAbertura());

        // inválido -> negativo
        assertThrows(AberturaInvalidaException.class, () -> c.setAbertura(-10)); 
        assertEquals(0, c.getAbertura());
    }
}