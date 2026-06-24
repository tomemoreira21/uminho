package DomusControl;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import DomusControl.automation.actions.onoff.Ligar;
import DomusControl.device.Dispositivo;
import DomusControl.device.Lampada;
import DomusControl.home.Casa;
import DomusControl.users.Utilizador;
import DomusControl.users.Papel;

import static org.junit.jupiter.api.Assertions.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Path;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

class AppTest {

    @Test
    void testConstrutoresERobustez() {
        DomusControl app = new DomusControl();
        assertNotNull(app.getCasas());
        
        DomusControl app2 = new DomusControl(new HashMap<>(), new HashMap<>());
        assertEquals(0, app2.getCasas().size());

        Map<String, Casa> casas = new HashMap<>();
        Casa c1 = new Casa("Original");
        casas.put(c1.getNome(), c1);

        DomusControl app3 = new DomusControl(casas, new HashMap<>());
        
        c1.setNome("Alterada"); 
        Casa naApp = app3.getCasas().values().iterator().next();

        assertNotEquals("Alterada", naApp.getNome());
    }

    @Test
    void testDeepCopyIntegrity() {
        DomusControl app = new DomusControl();
        Casa c1 = new Casa("Sintra");

        Map<String, Casa> input = new HashMap<>();
        input.put(c1.getNome(), c1);
        
        app.setCasas(input);
        
        Map<String, Casa> deDentro = app.getCasas();
        deDentro.clear();

        assertFalse(app.getCasas().isEmpty());

        Casa objetoDeDentro = app.getCasas().values().iterator().next();
        objetoDeDentro.setNome("Nome Alterado");
        
        Casa objetoInternoReal = app.getCasas().values().iterator().next();

        assertNotEquals("Nome Alterado", objetoInternoReal.getNome());
    }

    @Test
    void testEqualsHashCodeConsistencia() {
        DomusControl a1 = new DomusControl();
        DomusControl a2 = new DomusControl();

        Utilizador u1 = new Utilizador("Nuno", "nuno@mail.com");

        Map<String, Utilizador> users = new HashMap<>();
        users.put(u1.getNome(), u1);
        
        a1.setUtilizadores(users);

        assertNotEquals(a1, a2);

        a2.setUtilizadores(users);

        assertEquals(a1, a2);
    }

    @Test
    void testAddCasa() throws Exception {
        DomusControl app = new DomusControl(); 

        app.addUtilizador("Nuno", "nuno@email.com");
        app.addCasa("nuno@email.com","Braga"); // u1 fica logo como ADMIN

        // Verifica se foi adicionada
        assertEquals(1, app.getCasas().size());

        // Verifica se existe com o mesmo nome
        assertTrue(app.getCasas().containsKey("Braga"));

        Casa casaGuardada = app.getCasas().get("Braga").clone();

        // Não deve ser a mesma referência (clone!)
        assertNotSame(app.getCasa("Braga"), casaGuardada);

        // Mas deve ser igual em conteúdo
        assertEquals(app.getCasa("Braga").getNome(), casaGuardada.getNome());
    }

    @Test
    void testAddUtilizador() throws Exception {
        DomusControl app = new DomusControl();
        app.addUtilizador("Ana","ana@test.com");

        Utilizador u1 = app.getUtilizador("ana@test.com");

        assertEquals(1, app.getUtilizadores().size());

        assertTrue(app.getUtilizadores().containsKey(u1.getEmail()));

        Utilizador userGuardado = app.getUtilizadores().get(u1.getEmail());

        assertNotSame(u1, userGuardado);

        assertEquals(u1.getNome(), userGuardado.getNome());
    }

    @Test
    void testCasaComMaiorConsumo() throws Exception {
        DomusControl app = new DomusControl();
        Utilizador admin = new Utilizador("Admin", "admin@mail.com");

        app.addUtilizador("Admin", "admin@mail.com");
        app.addCasa(admin.getEmail(), "Casa 1");
        app.addCasa(admin.getEmail(), "Casa 2");

        LocalDateTime agora = LocalDateTime.of(2026,1,1,12,0);

        app.executarNaCasa("Casa 1", admin.getEmail(),
            (casa, u) -> casa.setTempoAtual(agora)
        );

        app.executarNaCasa("Casa 2", admin.getEmail(),
            (casa, u) -> casa.setTempoAtual(agora)
        );

        // Dispositivos
        Dispositivo l1 = new Lampada("l1","A","B",10);
        Dispositivo l2 = new Lampada("l2","A","B",50);

        app.executarNaCasa("Casa 1", admin.getEmail(),
            (casa, u) -> casa.addDispositivo(u, l1)
        );

        app.executarNaCasa("Casa 2", admin.getEmail(),
            (casa, u) -> casa.addDispositivo(u, l2)
        );

        app.executarNaCasa("Casa 1", admin.getEmail(),
            (casa, u) -> casa.atuarDispositivo(u, new Ligar("l1"))
        );

        app.executarNaCasa("Casa 2", admin.getEmail(),
            (casa, u) -> casa.atuarDispositivo(u, new Ligar("l2"))
        );

        // avanço de tempo por casa
        app.executarNaCasa("Casa 1", admin.getEmail(),
            (casa, u) -> casa.avancarTempo(Duration.ofHours(5))
        );

        app.executarNaCasa("Casa 2", admin.getEmail(),
            (casa, u) -> casa.avancarTempo(Duration.ofHours(5))
        );

        Casa result = app.getCasaComMaiorConsumo();

        Casa c1 = app.getCasa("Casa 1");
        Casa c2 = app.getCasa("Casa 2");

        System.out.println("C1 consumo: " + c1.getConsumoTotalCasa());
        System.out.println("C2 consumo: " + c2.getConsumoTotalCasa());

        assertNotNull(result);
        assertEquals(c2, result);
    }

    @Test
    void testTopTresDivisoes() throws Exception {
        DomusControl app = new DomusControl();
        Utilizador admin = new Utilizador("Admin", "admin@mail.com");

        app.addUtilizador("Admin", "admin@mail.com");
        app.addCasa(admin.getEmail(),"Casa 1");
        app.addCasa(admin.getEmail(), "Casa 2");

        app.executarNaCasa("Casa 1", admin.getEmail(), (casa, u) -> {
            casa.addDivisao(u, "Sala");
            casa.addDivisao(u, "Quarto");

            for(int i = 0; i < 5; i++)
                casa.addDispositivoADivisao(u, "Sala", new Lampada("s"+i,"a","b",1));

            for(int i = 0; i < 3; i++)
                casa.addDispositivoADivisao(u, "Quarto", new Lampada("q"+i,"a","b",1));
        });

        app.executarNaCasa("Casa 2", admin.getEmail(), (casa, u) -> {
            casa.addDivisao(u, "Cozinha");

            for(int i = 0; i < 4; i++)
                casa.addDispositivoADivisao(u, "Cozinha", new Lampada("c"+i,"a","b",1));
        });

        var top = app.getTopTresDivisoesComMaisDipositivos();

        assertEquals(3, top.size());

        assertEquals("Sala", top.get(0).getNomeDivisao());
        assertEquals("Cozinha", top.get(1).getNomeDivisao());
        assertEquals("Quarto", top.get(2).getNomeDivisao());
    }

    @Test
    void testUtilizadorComMaisCasasComoAdmin() throws Exception {
        DomusControl app = new DomusControl();

        Utilizador u1 = new Utilizador("User1", "u1@mail.com");
        Utilizador u2 = new Utilizador("User2", "u2@mail.com");

        app.addUtilizador("User1", "u1@mail.com");
        app.addUtilizador("User2", "u2@mail.com");

        // u1 é admin em 2 casas e u2 admin da casa 3
        app.addCasa(u1.getEmail(),"Casa 1");
        app.addCasa(u1.getEmail(),"Casa 2");
        app.addCasa(u2.getEmail(),"Casa 3");

        Utilizador result = app.utilizadorComMaisCasasComoAdmin();

        assertNotNull(result);
        assertEquals(u1.getNome(), result.getNome());
    }

    @Test
    void testCloneIndependencia() {
        DomusControl original = new DomusControl();

        Map<String, Casa> casas = new HashMap<>();
        Casa c1 = new Casa("Porto");
        Casa c2 = new Casa("Lisboa");

        casas.put(c1.getNome(), c1);
        casas.put(c2.getNome(), c2);

        original.setCasas(casas);
        
        DomusControl clone = original.clone();
        
        assertEquals(original, clone);
        assertNotSame(original, clone);
        
        original.setCasas(new HashMap<>());

        assertNotEquals(0, clone.getCasas().size());
    }

    @Test
    void testToStringFormat() {
        DomusControl app = new DomusControl();
        String ts = app.toString();

        assertNotNull(ts);
        assertTrue(ts.contains("App = ["));
        assertTrue(ts.endsWith("];\n"));
    }

    @Test
    void testIntegracaoAcessos() throws Exception {
        Casa casa = new Casa("Vivenda");
        Utilizador user = new Utilizador("Admin", "admin@domus.com");
        
        casa.addUtilizador(user, Papel.ADMIN);
        
        assertTrue(casa.getAcessos().stream()
                .anyMatch(a -> a.getUtilizador().equals(user)));

        assertTrue(user.getAcessos().size() > 0);
    }

    @TempDir
    Path tempDir;

    @Test
    void testSaveAndLoadFullCycle() throws IOException, ClassNotFoundException {
        DomusControl original = new DomusControl();
        
        Casa c1 = new Casa("Casa de Campo");
        Utilizador u1 = new Utilizador("Ricardo", "ricardo@domus.pt");
        
        Map<String, Casa> casas = new HashMap<>();
        casas.put(c1.getNome(), c1);

        Map<String, Utilizador> users = new HashMap<>();
        users.put(u1.getEmail(), u1);

        original.setCasas(casas);
        original.setUtilizadores(users);

        File file = tempDir.resolve("app_test.dat").toFile();
        String path = file.getAbsolutePath();

        original.guardarEstado(path);
        
        assertTrue(file.exists());

        DomusControl carregada = DomusControl.carregaEstado(path);

        assertEquals(original, carregada);
        
        Casa casaCarregada = carregada.getCasas().values().iterator().next();
        assertEquals("Casa de Campo", casaCarregada.getNome());
        
        Utilizador userCarregado = carregada.getUtilizadores().values().iterator().next();
        assertEquals("Ricardo", userCarregado.getNome());
    }

    @Test
    void testLoadMissingFile() {
        assertThrows(FileNotFoundException.class, () -> {
            DomusControl.carregaEstado("ficheiro_que_nao_existe.dat");
        });
    }

    @Test
    void testSaveLoadEmptyApp() throws IOException, ClassNotFoundException {
        DomusControl vazia = new DomusControl();
        File file = tempDir.resolve("empty_app.dat").toFile();
        String path = file.getAbsolutePath();

        vazia.guardarEstado(path);
        DomusControl carregada = DomusControl.carregaEstado(path);

        assertNotNull(carregada);
        assertTrue(carregada.getCasas().isEmpty());
        assertTrue(carregada.getUtilizadores().isEmpty());
    }

    @Test
    void testLoadedObjectIndependence() throws IOException, ClassNotFoundException {
        DomusControl original = new DomusControl();

        Casa c = new Casa("Original");
        Map<String, Casa> casas = new HashMap<>();
        casas.put(c.getNome(), c);

        original.setCasas(casas);
        
        File file = tempDir.resolve("independence.dat").toFile();
        String path = file.getAbsolutePath();

        original.guardarEstado(path);
        DomusControl carregada = DomusControl.carregaEstado(path);

        // Alterar original
        Casa nova = new Casa("Modificada");
        Map<String, Casa> novasCasas = new HashMap<>();
        novasCasas.put(nova.getNome(), nova);

        original.setCasas(novasCasas);
        
        Casa casaCarregada = carregada.getCasas().values().iterator().next();
        assertEquals("Original", casaCarregada.getNome());
    }
}