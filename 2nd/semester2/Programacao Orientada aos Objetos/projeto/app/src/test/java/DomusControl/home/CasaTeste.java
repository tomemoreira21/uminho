package DomusControl.home;

import org.junit.jupiter.api.Test;

import DomusControl.automation.Automacao;
import DomusControl.automation.AutomacaoEstado;
import DomusControl.automation.AutomacaoEvento;
import DomusControl.automation.Cenario;
import DomusControl.automation.actions.abertura.Abrir;
import DomusControl.automation.actions.abertura.Fechar;
import DomusControl.automation.actions.generica.AcaoPorFiltro;
import DomusControl.automation.actions.onoff.Desligar;
import DomusControl.automation.actions.onoff.Ligar;
import DomusControl.automation.actions.onoff.coluna.AlterarVolume;
import DomusControl.automation.actions.onoff.lampada.AlterarLuminosidade;
import DomusControl.automation.actions.onoff.sensor.AlterarValorMedido;
import DomusControl.automation.conditions.CondicaoComparativaSensor;
import DomusControl.automation.conditions.CondicaoHorarioExato;
import DomusControl.automation.conditions.CondicaoHorarioIntervalo;
import DomusControl.automation.conditions.TipoComparacao;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.automation.core.Condicao;
import DomusControl.device.ColunaSom;
import DomusControl.device.Cortina;
import DomusControl.device.Dispositivo;
import DomusControl.device.Lampada;
import DomusControl.device.SensorChuva;
import DomusControl.device.SensorLuminosidade;
import DomusControl.exceptions.casa.AcessoNegadoException;
import DomusControl.exceptions.casa.AcessoRepetidoException;
import DomusControl.exceptions.casa.DivisaoInexistenteException;
import DomusControl.exceptions.dispositivo.DispositivoNaoExisteException;
import DomusControl.users.Papel;
import DomusControl.users.Utilizador;

import static org.junit.jupiter.api.Assertions.*;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.List;
import java.util.Map;

public class CasaTeste {
    @Test
    void testIsAdminAndAddDivisao() {
        // Criar utilizadores
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Utilizador user = new Utilizador("Maria", "maria@email.com");

        // Criar casa
        Casa casa = new Casa("Casa do João");

        // Dar papéis
        assertDoesNotThrow(() -> casa.addUtilizador(admin, Papel.ADMIN));
        assertDoesNotThrow(() -> casa.addUtilizador(user, Papel.USER));

        // Apenas admin consegue adicionar divisão
        assertDoesNotThrow(() -> casa.addDivisao(admin,"Sala"));  // Admin não deve lançar exceção
        assertThrows(AcessoNegadoException.class, () -> casa.addDivisao(user,"Cozinha")); // User deve lançar exceção

        // Verificar que a divisão foi realmente adicionada
        assertEquals(1, casa.getDivisoes().size());
        assertTrue(casa.getDivisoes().containsKey("Sala"));
    }

    @Test
    void testAddDispositivoADivisao() {
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Utilizador user = new Utilizador("Maria", "maria@email.com");
        Casa casa = new Casa("Casa do João");

        assertDoesNotThrow(() -> casa.addUtilizador(admin, Papel.ADMIN));
        assertDoesNotThrow(() -> casa.addUtilizador(user, Papel.USER));

        assertDoesNotThrow(() -> casa.addDivisao(admin, "Sala"));

        Dispositivo lampada = new Lampada("L1","Xiaomi","LED",2);

        // Apenas admin consegue adicionar dispositivo
        assertDoesNotThrow(() -> casa.addDispositivoADivisao(admin, "Sala", lampada)); // o admin consegue adicionar dispositivos a divisoes sem problema
        assertThrows(AcessoNegadoException.class, () -> casa.addDispositivoADivisao(user, "Sala", new ColunaSom("C1", "JBL", null, 3)));  // não deve funcionar pois o user não é um administrador
        assertThrows(DivisaoInexistenteException.class, () -> casa.addDispositivoADivisao(admin, "Cozinha", lampada)); // divisao inexistente


        assertDoesNotThrow(() -> assertEquals(1, casa.getNumDispositivosDiv("Sala")));
        assertDoesNotThrow(() -> assertNotNull(casa.getDispositivo("L1")));
    }

    @Test
    void testConsumoMedioPorDivisao() throws Exception {
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Casa casa = new Casa("Casa Teste");
        casa.addUtilizador(admin, Papel.ADMIN);

        casa.addDivisao(admin, "Sala");
        casa.addDivisao(admin, "Quarto");

        LocalDateTime agora = LocalDateTime.of(2026,1,1,12,0);
        casa.setTempoAtual(agora);

        // Criar dispositivos
        Lampada l1 = new Lampada("l1", "Philips", "Hue", 10);
        Lampada l2 = new Lampada("l2", "Philips", "Hue", 20);
        Lampada l3 = new Lampada("l3", "Philips", "Hue", 30);

        // Ligar para gerar consumo
        l1.ligar(agora.minusHours(1));
        l2.ligar(agora.minusHours(1));
        l3.ligar(agora.minusHours(1));

        casa.addDispositivoADivisao(admin, "Sala", l1);
        casa.addDispositivoADivisao(admin, "Sala", l2);
        casa.addDispositivoADivisao(admin, "Quarto", l3);

        Map<String, Double> consumo = casa.getConsumoMedioPorDivisao();

        // Sala: média de l1 e l2
        double esperadoSala = (
            casa.getDispositivo("l1").consumoTotal(agora) +
            casa.getDispositivo("l2").consumoTotal(agora)
        ) / 2;

        // Quarto: só l3
        double esperadoQuarto = casa.getDispositivo("l3").consumoTotal(agora);

        assertEquals(esperadoSala, consumo.get("Sala"), 0.0001);
        assertEquals(esperadoQuarto, consumo.get("Quarto"), 0.0001);
    }

    @Test
    //adicionar casos de teste de desempates 
    void testTresDispositivosMaisUsados() throws Exception {
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Casa casa = new Casa("Casa Teste");
        casa.addUtilizador(admin, Papel.ADMIN);

        casa.addDivisao(admin, "Sala");

        LocalDateTime agora = LocalDateTime.of(2026,1,1,12,0);
        casa.setTempoAtual(agora);

        // Criar dispositivos
        Lampada l1 = new Lampada("l1", "Philips", "Hue", 10);
        Lampada l2 = new Lampada("l2", "Philips", "Hue", 10);
        Lampada l3 = new Lampada("l3", "Philips", "Hue", 10);
        Lampada l4 = new Lampada("l4", "Philips", "Hue", 10);

        // Simular tempos diferentes
        l1.ligar(agora.minusHours(5)); // mais usado
        l2.ligar(agora.minusHours(4));
        l3.ligar(agora.minusHours(3));
        l4.ligar(agora.minusHours(1)); // menos usado

        casa.addDispositivoADivisao(admin, "Sala", l1);
        casa.addDispositivoADivisao(admin, "Sala", l2);
        casa.addDispositivoADivisao(admin, "Sala", l3);
        casa.addDispositivoADivisao(admin, "Sala", l4);

        List<Dispositivo> top3 = casa.getTresDispositivosMaisUsados();

        assertEquals(3, top3.size());

        // Espera-se ordem: l1, l2, l3
        assertEquals("l1", top3.get(0).getId());
        assertEquals("l2", top3.get(1).getId());
        assertEquals("l3", top3.get(2).getId());
    }

    @Test 
    void testAtuarDispositivo() {
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Utilizador user = new Utilizador("Maria", "maria@email.com");
        Casa casa = new Casa("Casa do João");

        assertDoesNotThrow(() -> casa.addUtilizador(admin, Papel.ADMIN));

        // mesmo utilizador, com dois tipos de acessos numa mesma casa (deve dar a exception)
        assertThrows(AcessoRepetidoException.class, () -> casa.addUtilizador(admin, Papel.USER));

        assertDoesNotThrow(() -> casa.addUtilizador(user, Papel.USER));

        assertDoesNotThrow(() -> casa.addDivisao(admin, "Sala"));

        // Criar um dispositivo e adicioná-lo à sala
        Dispositivo lampada = new Lampada("L1", "Xiaomi", "LED", 2);
        assertDoesNotThrow(() -> casa.addDispositivoADivisao(admin, "Sala", lampada));

        AcaoSimples ligarL1 = new Ligar("L1");
        AcaoSimples ligarL2 = new Ligar("L2");

        assertDoesNotThrow(() -> casa.atuarDispositivo(user, ligarL1));
        assertThrows(DispositivoNaoExisteException.class, () ->  casa.atuarDispositivo(user, ligarL2));

        assertDoesNotThrow(() -> ((Lampada)casa.getDispositivo("L1")).isLigado());
    }

    @Test
    void testAutomacaoFecharAsCortinas() throws Exception {
        // Utilizadores
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Casa casa = new Casa("Casa do João");
        casa.addUtilizador(admin, Papel.ADMIN);

        // Divisões
        casa.addDivisao(admin, "Sala");
        casa.addDivisao(admin, "Cozinha");
        casa.addDivisao(admin, "Quarto");

        // Cortinas (3 diferentes)
        Cortina cortinaSala = new Cortina("c1", "marca", "modelo", 0,0.03);
        Cortina cortinaCozinha = new Cortina("c2", "marca", "modelo", 0,0.03);
        Cortina cortinaQuarto = new Cortina("c3", "marca", "modelo", 0,0.03);

        // Garantir que começam abertas
        cortinaSala.abrir();
        cortinaCozinha.abrir();
        cortinaQuarto.abrir();

        assertTrue(cortinaSala.isAberta());
        assertTrue(cortinaCozinha.isAberta());
        assertTrue(cortinaQuarto.isAberta());

        // Adicionar às divisões
        casa.addDispositivoADivisao(admin,"Sala",cortinaSala);
        casa.addDispositivoADivisao(admin, "Cozinha", cortinaCozinha);
        casa.addDispositivoADivisao(admin, "Quarto", cortinaQuarto);
    
        // Sensor de chuva
        SensorChuva sensorChuva = new SensorChuva("s1", "netatmo", "rain", 0);
        sensorChuva.setValor(10.0); // está a chover

        casa.addDispositivo(admin, sensorChuva);

        // Condição: chuva > 0
        Condicao condicao = new CondicaoComparativaSensor("s1", 0.0, TipoComparacao.MAIOR);

        // Criar ações de fechar todas as cortinas
        List<AcaoComInversa> acaoFecharTodasAsCortinas = List.of(
            new AcaoPorFiltro(
                (c,d) -> d instanceof Cortina,
                d -> new Fechar(d.getId()))
        );

        // Criar automacao
        Automacao automacao = new AutomacaoEstado(condicao, acaoFecharTodasAsCortinas, admin);

        casa.addAutomacao(automacao);

        // Verificações
        assertTrue(((Cortina)casa.getDispositivo("c1")).isFechada());
        assertTrue(((Cortina)casa.getDispositivo("c2")).isFechada());
        assertTrue(((Cortina)casa.getDispositivo("c3")).isFechada());

        casa.atuarDispositivo(admin, new AlterarValorMedido("s1", 0)); // deixa de chover

        // Verificação se estão abertas
        assertFalse(((Cortina)casa.getDispositivo("c1")).isFechada());
        assertFalse(((Cortina)casa.getDispositivo("c2")).isFechada());
        assertFalse(((Cortina)casa.getDispositivo("c3")).isFechada());
    }

    @Test
    void testAutomacaoLigarLampadasSePoucaLuz()  throws Exception {
        // Utilizador
        Utilizador admin = new Utilizador("Maria", "maria@email.com");
        Casa casa = new Casa("Casa do João");
        casa.addUtilizador(admin, Papel.ADMIN);
        casa.setTempoAtual(LocalDateTime.now());

        // Divisões e lâmpadas
        casa.addDivisao(admin, "Sala");

        Lampada lampada1 = new Lampada("l1", "philips", "hue", 3);
        Lampada lampada2 = new Lampada("l2", "philips", "hue", 3);
        
        casa.addDispositivoADivisao(admin, "Sala", lampada1);
        casa.addDispositivoADivisao(admin, "Sala", lampada2);

        assertFalse(lampada1.isLigado());
        assertFalse(lampada2.isLigado());

        // Sensor de luminosidade
        SensorLuminosidade sensorLum = new SensorLuminosidade("s2", "netatmo", "light", 0);
        sensorLum.setValor(10.0); // luminosidade baixa

        casa.addDispositivo(admin, sensorLum);

        // Condição: luminosidade < 50
        Condicao condicao = new CondicaoComparativaSensor("s2", 50.0, TipoComparacao.MENOR);

        // Ações
        List<AcaoComInversa> acoesLigarLampadas = List.of(
            new AcaoPorFiltro(
                (c,d) -> d instanceof Lampada,
                d -> new Ligar(d.getId()))
        );


        // Criar automacao
        Automacao automacao = new AutomacaoEstado(condicao, acoesLigarLampadas, admin);

        casa.addAutomacao(automacao);

        // Verificar que as lâmpadas ligaram
        assertTrue(((Lampada)casa.getDispositivo("l1")).isLigado());
        assertTrue(((Lampada)casa.getDispositivo("l2")).isLigado());

        // Deve desligar automaticamente pois já subiu a luminosidade
        casa.atuarDispositivo(admin, new AlterarValorMedido("s2", 60));

        // Verificar que as lâmpadas desligaram
        assertFalse(((Lampada)casa.getDispositivo("l1")).isLigado());
        assertFalse(((Lampada)casa.getDispositivo("l2")).isLigado());
    }

    @Test
    void testEscalonamentoIntervaloHorario() throws Exception {
        Utilizador admin = new Utilizador("Maria", "maria@email.com");
        Casa casa = new Casa("Casa do João");
        casa.addUtilizador(admin, Papel.ADMIN);

        casa.addDivisao(admin, "Sala");

        Lampada lampada = new Lampada("l1", "philips", "hue", 3);
        casa.addDispositivoADivisao(admin, "Sala", lampada);

        // Intervalo de tempo: 3 segundos antes -> 3 segundos apos
        LocalDateTime agora = LocalDateTime.of(2026,1,1,12,0);
        casa.setTempoAtual(agora);

        LocalTime inicio = agora.toLocalTime().minusSeconds(3);
        LocalTime fim = agora.toLocalTime().plusSeconds(3);

        CondicaoHorarioIntervalo condicao = new CondicaoHorarioIntervalo(inicio, fim);

        List<AcaoComInversa> acaoLigarLampadaL1 = List.of(new Ligar("l1"));

        // Criar automacao
        Automacao automacao = new AutomacaoEstado(condicao, acaoLigarLampadaL1, admin);
        casa.addAutomacao(automacao);

        // --- Dentro do intervalo → ON dispara ---
        casa.executarAutomacoesTemporais();
        assertTrue(((Lampada)casa.getDispositivo("l1")).isLigado());

        casa.avancarTempo(Duration.ofSeconds(10));

        assertFalse(((Lampada)casa.getDispositivo("l1")).isLigado()); // está desligado
    }

    @Test
    void testEscalonamentoHoraExataAbrirCortinas() throws Exception {
        Utilizador admin = new Utilizador("Maria", "maria@email.com");
        Casa casa = new Casa("Casa do João");
        casa.addUtilizador(admin, Papel.ADMIN);

        casa.addDivisao(admin, "Quarto");

        Cortina cortina1 = new Cortina("c1", "marca", "modelo", 1,0.03);
        Cortina cortina2 = new Cortina("c2", "marca", "modelo", 1,0.03);


        casa.addDispositivoADivisao(admin, "Quarto", cortina1);
        casa.addDispositivoADivisao(admin, "Quarto", cortina2);

        assertTrue(((Cortina)casa.getDispositivo("c1")).isFechada());
        assertTrue(((Cortina)casa.getDispositivo("c2")).isFechada());

        // Condição: hora exata (agora)
        LocalDateTime agora = LocalDateTime.now();
        casa.setTempoAtual(agora);

        Condicao condicao = new CondicaoHorarioExato(agora.toLocalTime());

        List<Acao> acoesAbrirCortinas = List.of(
            new AcaoPorFiltro(
                (c,d) -> d instanceof Cortina,
                d -> new Abrir(d.getId()))
        );

        // Criar automacao
        Automacao automacao = new AutomacaoEvento(condicao, acoesAbrirCortinas, admin);
        casa.addAutomacao(automacao);

        casa.executarAutomacoesTemporais();

        assertTrue(((Cortina)casa.getDispositivo("c1")).isAberta());
        assertTrue(((Cortina)casa.getDispositivo("c2")).isAberta());

        casa.atuarDispositivo(admin, new Fechar("c1"));
        casa.atuarDispositivo(admin, new Fechar("c2"));

        casa.avancarTempo(Duration.ofDays(1));

        assertTrue(((Cortina)casa.getDispositivo("c1")).isAberta());
        assertTrue(((Cortina)casa.getDispositivo("c2")).isAberta());
    }

    @Test
    void testCenarioVerCinema() throws Exception {
        // Criar utilizador e casa
        Utilizador admin = new Utilizador("João", "joao@email.com");
        Casa casa = new Casa("Casa do João");
        casa.addUtilizador(admin, Papel.ADMIN);

        LocalDateTime agora = LocalDateTime.of(2026,1,1,12,0);
        casa.setTempoAtual(agora);

        casa.addDivisao(admin, "Sala de Estar");

        // Criar dispositivos
        Lampada lampada = new Lampada("l1", "Philips", "Hue", 100);
        Cortina cortina = new Cortina("c1", "Ikea", "SmartCurtain", 0,0.03);
        ColunaSom coluna = new ColunaSom("s1", "Bose", "SoundMax",2);

        // Ligar dispositivos inicialmente
        lampada.ligar(agora);
        cortina.abrir();;
        coluna.ligar(agora);

        casa.addDispositivoADivisao(admin, "Sala de Estar", lampada);
        casa.addDispositivoADivisao(admin, "Sala de Estar", cortina);
        casa.addDispositivoADivisao(admin, "Sala de Estar", coluna);

        // Verificar estado inicial
        assertTrue(((Lampada)casa.getDispositivo("l1")).isLigado());
        assertTrue(((Cortina)casa.getDispositivo("c1")).isAberta());
        assertTrue(((ColunaSom)casa.getDispositivo("s1")).isLigado());

        // Criar ações do cenário
        List<Acao> acoes = List.of(
            new AlterarLuminosidade("l1", 20), // reduzir intensidade
            new Fechar("c1"),     // fechar cortina
            new AlterarVolume("s1", 70) // aumentar volume das colunas
        );

        // Criar cenário
        Cenario verCinema = new Cenario("Ver Cinema", acoes, admin);

        // Adicionar cenário à casa
        casa.addCenario(verCinema);

        // Executar cenário
        casa.executarCenario(admin,"Ver Cinema");

        // Verificar estados após execução
        assertEquals(20, ((Lampada)casa.getDispositivo("l1")).getIntensidadeLuminosa());
        assertTrue(((Cortina)casa.getDispositivo("c1")).isFechada());
        assertEquals(70, ((ColunaSom)casa.getDispositivo("s1")).getVolume());
    }

    @Test
    void testSugestaoViaAtuarDispositivo() throws Exception {
        Utilizador user = new Utilizador("Vitor", "vitor@email.com");
        Casa casa = new Casa("Casa Teste");
        casa.addUtilizador(user, Papel.ADMIN);

        casa.addDivisao(user, "Sala");

        Lampada lampada = new Lampada("l1", "Philips", "Hue", 100);
        casa.addDispositivoADivisao(user, "Sala", lampada);

        LocalDateTime t1 = LocalDateTime.of(2026,1,1,20,0);
        casa.setTempoAtual(t1);

        for (int dia = 1; dia <= 7; dia++) {
            casa.atuarDispositivo(user, new Ligar("l1"));
            casa.atuarDispositivo(user, new Desligar("l1")); 

            casa.avancarTempo(Duration.ofDays(1));
        }

        // Analisar
        casa.analisarSugestoes();

        List<Automacao> sugestoes = casa.getAnalisador().getSugestoes();

        assertFalse(sugestoes.isEmpty(), "Deveria gerar sugestão");

        AutomacaoEvento evento = (AutomacaoEvento) sugestoes.get(0);

        boolean temLigar = evento.getAcoes().stream()
            .anyMatch(a -> a instanceof Ligar);

        assertTrue(temLigar);
    }
    
}
