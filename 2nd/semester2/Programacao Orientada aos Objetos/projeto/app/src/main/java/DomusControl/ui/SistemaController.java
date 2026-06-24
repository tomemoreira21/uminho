package DomusControl.ui;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

import DomusControl.DomusControl;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.Condicao;
import DomusControl.automation.interfaces_genericas.FactoryAcao;
import DomusControl.automation.interfaces_genericas.FiltroDispositivo;
import DomusControl.automation.actions.onoff.Ligar;
import DomusControl.automation.actions.onoff.Desligar;
import DomusControl.automation.actions.onoff.lampada.AlterarLuminosidade;
import DomusControl.automation.actions.onoff.lampada.AlterarCor;
import DomusControl.automation.actions.onoff.coluna.AlterarVolume;
import DomusControl.automation.actions.onoff.sensor.AlterarValorMedido;
import DomusControl.automation.conditions.CondicaoComparativaSensor;
import DomusControl.automation.conditions.CondicaoHorarioExato;
import DomusControl.automation.conditions.CondicaoHorarioIntervalo;
import DomusControl.automation.conditions.TipoComparacao;
import DomusControl.automation.Automacao;
import DomusControl.automation.AutomacaoEstado;
import DomusControl.automation.AutomacaoEvento;
import DomusControl.automation.Cenario;
import DomusControl.automation.actions.abertura.Abrir;
import DomusControl.automation.actions.abertura.Fechar;
import DomusControl.automation.actions.abertura.AlterarAbertura;
import DomusControl.device.ColunaSom;
import DomusControl.device.Cortina;
import DomusControl.device.Dispositivo;
import DomusControl.device.Lampada;
import DomusControl.device.PortaoGaragem;
import DomusControl.device.Rele;
import DomusControl.device.SensorChuva;
import DomusControl.device.SensorLuminosidade;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;
import DomusControl.services.DivisaoInfo;
import DomusControl.users.Papel;
import DomusControl.users.Utilizador;

public class SistemaController {
    private DomusControl model;

    private String emailUtilizadorAtual;
    private String nomeCasaAtual;
    private String idDispositivo;

    public SistemaController() throws FileNotFoundException, IOException, ClassNotFoundException {
        this.model = DomusControl.carregaEstado("estado.dat");
    }

    public SistemaController(DomusControl model) {
        this.model = model;
    }

    public Utilizador getUtilizadorAtual() throws DomusControlException {
        return model.getUtilizador(emailUtilizadorAtual);
    }

    public String getEmailUtilizadorAtual() {
        return this.emailUtilizadorAtual;
    }

    public void setEmailUtilizadorAtual(String utilizadorAtual) {
        this.emailUtilizadorAtual = utilizadorAtual;
    }

    public Casa getCasaAtual() throws DomusControlException {
        return model.getCasa(nomeCasaAtual);
    }

    public String getNomeCasaAtual() {
        return this.nomeCasaAtual;
    }

    public void setNomeCasaAtual(String nomeCasaAtual) {
        this.nomeCasaAtual = nomeCasaAtual;
    }

    public String getIDdispositivoAtual() {
        return this.idDispositivo;
    }

    public void setDispositivoAtual(String idDispositivoAtual) {
        this.idDispositivo = idDispositivoAtual;
    }

    // recebe sobre a forma de strings e dá o objeto já
    public void criarCasa(String nome) throws DomusControlException {
        model.addCasa(emailUtilizadorAtual,nome);
    }

    public void criarUtilizador(String nome,String email) throws DomusControlException {
        model.addUtilizador(nome,email);
    }

    public void criarDivisao(String nomeDivisao) throws DomusControlException {
        validarContexto();
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                             (casa,u) -> casa.addDivisao(u, nomeDivisao));
    } 

    public void criarCortina(String id,
                            String marca, 
                            String modelo, 
                            double consumoPorHora, 
                            double tempoAberturaSegundos, 
                            String divisao
    ) throws DomusControlException {
        validarContexto();

        double tempoAberturaHoras = tempoAberturaSegundos / 3600.0;

        Cortina cortina = new Cortina(id, marca, modelo, consumoPorHora, tempoAberturaHoras);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                            (casa,u) -> casa.addDispositivoADivisao(u, divisao, cortina));
    }

    public void criarPortaoGaragem(String id,
                            String marca, 
                            String modelo, 
                            double consumoPorHora, 
                            double tempoAberturaSegundos, 
                            String divisao
    ) throws DomusControlException {
        validarContexto();

        double tempoAberturaHoras = tempoAberturaSegundos / 3600.0;

        PortaoGaragem portao = new PortaoGaragem(id, marca, modelo, consumoPorHora, tempoAberturaHoras);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                            (casa,u) -> casa.addDispositivoADivisao(u, divisao, portao));
    }

    public void criarColunaSom(String id,
                            String marca, 
                            String modelo, 
                            double consumoPorHora, 
                            String divisao
    ) throws DomusControlException {
        validarContexto();

        ColunaSom coluna = new ColunaSom(id, marca, modelo, consumoPorHora);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                             (casa,u) -> casa.addDispositivoADivisao(u, divisao, coluna));
    }

    public void criarLampada(String id,
                            String marca, 
                            String modelo, 
                            double consumoPorHora, 
                            String divisao
    ) throws DomusControlException {
        validarContexto();

        Lampada l = new Lampada(id, marca, modelo, consumoPorHora);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                             (casa,u) -> casa.addDispositivoADivisao(u, divisao, l));
    }

    public void criarRele(String id,
                            String marca, 
                            String modelo, 
                            double consumoPorHora, 
                            String divisao
    ) throws DomusControlException {
        validarContexto();

        Rele r = new Rele(id, marca, modelo, consumoPorHora);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                             (casa,u) -> casa.addDispositivoADivisao(u, divisao, r));
    }

    // sensores acabam por nao estar associados a qualquer divisao
    public void criarSensorChuva(String id,
                                String marca, 
                                String modelo, 
                                double consumoPorHora
    ) throws DomusControlException {
        validarContexto();

        SensorChuva s = new SensorChuva(id, marca, modelo, consumoPorHora);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual,
                             (casa, u) -> casa.addDispositivo(u, s));
    }

    public void criarSensorLuminosidade(String id,
                                String marca, 
                                String modelo, 
                                double consumoPorHora
    ) throws DomusControlException {
        validarContexto();

        SensorLuminosidade s = new SensorLuminosidade(id, marca, modelo, consumoPorHora);
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual,
                             (casa, u) -> casa.addDispositivo(u, s));
    }

    public void adicionarAutomacao(Automacao a) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, casa -> {
            casa.addAutomacao(a);
        });
    }

    public void criarAutomacaoPorSensor(
            String idSensor,
            String comparacao,
            double valorReferencia,
            List<AcaoComInversa> acoes
    ) throws DomusControlException {

        validarContexto();

        model.executarNaCasa(nomeCasaAtual, emailUtilizadorAtual,
            (casa, user) -> {

                TipoComparacao tipo = TipoComparacao.valueOf(comparacao.toUpperCase());

                Condicao cond = new CondicaoComparativaSensor(
                        idSensor,
                        valorReferencia,
                        tipo
                );

                Automacao automacao = new AutomacaoEstado(cond, acoes, user);

                casa.addAutomacao(automacao);
            }
        );
    }

    public void criarAutomacaoPorHorario(
        LocalTime hora,
        List<Acao> acoes
    ) throws DomusControlException {

       validarContexto();

        model.executarNaCasa(nomeCasaAtual, emailUtilizadorAtual,
            (casa, user) -> {

                Condicao cond = new CondicaoHorarioExato(hora);
                Automacao automacao = new AutomacaoEvento(cond, acoes, user);

                casa.addAutomacao(automacao);
            }
        );
    }

    public void criarAutomacaoPorIntervalo(LocalTime inicio, LocalTime fim,List<AcaoComInversa> acoes) 
        throws DomusControlException {

        validarContexto();

        model.executarNaCasa(nomeCasaAtual, emailUtilizadorAtual,
            (casa, user) -> {

                Condicao cond = new CondicaoHorarioIntervalo(inicio, fim);
                Automacao automacao = new AutomacaoEstado(cond, acoes, user);

                casa.addAutomacao(automacao);
            }
        );
    }

    public void criarCenario(String nome, List<Acao> acoes) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, emailUtilizadorAtual,
            (casa, user) -> {

                Cenario c = new Cenario(nome, acoes, user);
                casa.addCenario(c);
            }
        );
    }

    // Funções auxiliares necessárias para a criação de uma automação
    public FiltroDispositivo criarFiltro(String tipo, String divisao) throws DomusControlException {
        validarContexto();

        return (casa,d) -> {

            boolean tipoOk = switch (tipo.toLowerCase()) {
                case "lampada" -> d instanceof Lampada;
                case "cortina" -> d instanceof Cortina;
                case "colunasom" -> d instanceof ColunaSom;
                case "rele" -> d instanceof Rele;
                case "portaogaragem" -> d instanceof PortaoGaragem;
                default -> false;
            };

            boolean divisaoOk = divisao == null || casa.dispositivoPertenceDivisao(divisao, d);

            return tipoOk && divisaoOk;
        };
    }

    public FactoryAcao criarFactory(String acao, Integer valor) {
        return switch (acao) {
            case "LIGAR" -> d -> new Ligar(d.getId());
            case "DESLIGAR" -> d -> new Desligar(d.getId());
            case "ABRIR" -> d -> new Abrir(d.getId());
            case "FECHAR" -> d -> new Fechar(d.getId());
            case "ABERTURA" -> d -> new AlterarAbertura(d.getId(), valor);
            case "VOLUME" -> d -> new AlterarVolume(d.getId(),valor);
            case "LUMINOSIDADE" -> d-> new AlterarLuminosidade(d.getId(), valor);
            case "COR" -> d -> new AlterarCor(d.getId(), valor);
            default -> throw new IllegalArgumentException("Ação inválida");
        };
    }

    // Cria o seu papel dentro da casa
    public boolean utilizadorTemAcessoCasaSelecionada() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
                                  emailUtilizadorAtual, 
                                  Casa::temAcesso);
    }

    public void garantirAcessoCasa(Papel papel) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                             (casa,u) -> {
                                if (!casa.temAcesso(u))
                                    casa.addUtilizador(u, papel);

                             });
    }

    public void ligarDispositivo() throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                            emailUtilizadorAtual, 
                            (casa, u) -> casa.atuarDispositivo(u, new Ligar(idDispositivo)));
    }

    public void desligarDispositivo() throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                        emailUtilizadorAtual, 
                        (casa, u) -> casa.atuarDispositivo(u, new Desligar(idDispositivo)));
    }

    public void abrirDispositivo() throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                        emailUtilizadorAtual, 
                        (casa, u) -> casa.atuarDispositivo(u, new Abrir(idDispositivo)));
    }
   
    public void fecharDispositivo() throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                        emailUtilizadorAtual, 
                        (casa, u) -> casa.atuarDispositivo(u, new Fechar(idDispositivo)));
    }

    public void alterarAberturaDispositivo(int valor) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                        emailUtilizadorAtual, 
                        (casa, u) -> casa.atuarDispositivo(u, new AlterarAbertura(idDispositivo, valor)));
    }

    public void alterarLuminosidadeLampada(int valor) throws DomusControlException {
        validarContexto();

         model.executarNaCasa(nomeCasaAtual, 
                            emailUtilizadorAtual, 
                            (casa, u) -> casa.atuarDispositivo(u, new AlterarLuminosidade(idDispositivo,valor)));
    }

    public void alterarCorLampada(int valor) throws DomusControlException {
        validarContexto();

         model.executarNaCasa(nomeCasaAtual, 
                            emailUtilizadorAtual, 
                            (casa, u) -> casa.atuarDispositivo(u, new AlterarCor(idDispositivo, valor)));
    }

    public void alterarValorMedido(double valor) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                            emailUtilizadorAtual, 
                            (casa, u) -> casa.atuarDispositivo(u, new AlterarValorMedido(idDispositivo, valor)));
    }

    public void alterarVolumeColuna(int valor) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual, 
                        emailUtilizadorAtual, 
                        (casa, u) -> casa.atuarDispositivo(u, new AlterarVolume(idDispositivo, valor)));
    }

    public Dispositivo getDispositivo(String id) throws DomusControlException {
        validarContexto();
        return model.consultarCasa(nomeCasaAtual, 
                                   casa -> casa.getDispositivo(id));
    }

    
    public void selecionarUtilizador(String email) throws DomusControlException {
        model.getUtilizador(email);
        this.emailUtilizadorAtual = email;
    }

    public void selecionarCasa(String nome) throws DomusControlException {
        model.getCasa(nome);
        this.nomeCasaAtual = nome;
    }

    public void selecionarDispositivo(String id) throws DomusControlException {
        validarContexto();

        model.consultarCasa(nomeCasaAtual, 
                casa -> {
                    casa.getDispositivo(id);
                    return null;
                }
        );

        this.idDispositivo = id;
    }

    public boolean temUtilizadorSelecionado() {
        return this.emailUtilizadorAtual != null;
    }

    public boolean temCasaSelecionada() {
        return this.nomeCasaAtual != null;
    }

    public void executarCenario(String nome) throws DomusControlException {
        validarContexto();
        model.executarNaCasa(nomeCasaAtual, 
                             emailUtilizadorAtual, 
                            (casa, u) -> casa.executarCenario(u, nome));
    }

    public Set<Automacao> listarAutomacoes() throws DomusControlException {
        validarContexto();

        return model.consultarCasa(nomeCasaAtual, 
                                   Casa::getAutomacoes
        );
    }

    public LocalDateTime getTempoCasaAtual() throws DomusControlException {
        validarContexto();

        return model.consultarCasa(nomeCasaAtual, 
                                    Casa::getTempoAtual
        );
    }

    public void listar(FiltroDispositivo filtro) throws DomusControlException {
        validarContexto();

        model.executarNaCasa(nomeCasaAtual,
            casa -> casa.getDispositivosFiltrados(filtro)
                        .forEach(System.out::println)
        );
    }

    public void avancaTempoLocal(Duration d) throws DomusControlException {
        model.executarNaCasa(nomeCasaAtual,
                        casa -> casa.avancarTempo(d)
        );
    }

    public Map<String,LocalDateTime> getTemposCasas() {
        return model.getCasas().entrySet()
                               .stream()
                               .collect(Collectors.toMap(
                                  e -> e.getKey(),
                                  e -> e.getValue().getTempoAtual()
                               ));
    }

    public Casa getCasaComMaiorConsumo() {
        return model.getCasaComMaiorConsumo();
    }

    public List<DivisaoInfo> getTopTresDivisoesComMaisDipositivos() 
        throws DomusControlException {
        return model.getTopTresDivisoesComMaisDipositivos();
    }

    public Utilizador utilizadorComMaisCasasComoAdmin() {
        return model.utilizadorComMaisCasasComoAdmin();
    }

    public Map<String, Double> getConsumoMedioPorDivisao() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
                                   Casa::getConsumoMedioPorDivisao

        );
    }

    public List<Dispositivo> getTresDispositivosMaisUsados() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
                                  Casa::getTresDispositivosMaisUsados

        );
    }

    public void analisarSugestoes() throws DomusControlException {
        model.executarNaCasa(nomeCasaAtual, 
                    casa -> casa.analisarSugestoes()
        );
    }

    public List<Automacao> getSugestoesAutomacoes() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
            casa -> casa.getAnalisador().getSugestoes()
        );
    }

    public void limparSugestoes() throws DomusControlException {
        model.executarNaCasa(nomeCasaAtual, casa -> casa.limparSugestoes());
    }

    public Map<String,Cenario> getCenarios() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, Casa::getCenarios);
    }

    public int getNumeroUtilizadores() {
        return this.model.getNumeroUtilizadores();
    }

    public int getNumeroCasas() {
        return this.model.getNumeroCasas();
    }

    public boolean existem(Function<Casa, Integer> extractor) {
        validarContexto();
        return model.getNumero(nomeCasaAtual, extractor) > 0;
    }

    public boolean existemDispositivos(Predicate<Dispositivo> filtro) throws DomusControlException {
        validarContexto();
        return model.consultarCasa(nomeCasaAtual, 
            casa -> casa.getDispositivos().values().stream().anyMatch(filtro));
    }

    public void guardarEstado(String ficheiro) throws FileNotFoundException, IOException {
       this.model.guardarEstado(ficheiro);
    }

    public void logout() {
        this.emailUtilizadorAtual = null;
        this.nomeCasaAtual = null;
    }

    public void sairCasa() {
        this.nomeCasaAtual = null;
    }

    public void sairDispositivo() {
        this.idDispositivo = null;
    }
    
    public Dispositivo getDispositivoAtual() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
                casa -> casa.getDispositivo(idDispositivo)
        );
    }

    public Map<String, Set<Dispositivo>> getDivisoes() throws DomusControlException {
        return model.consultarCasa(nomeCasaAtual, 
                                   Casa::getDivisoes
        );
    }

    private void validarContexto() {
        if (emailUtilizadorAtual == null)
            throw new IllegalStateException("Nenhum utilizador autenticado.");

        if (nomeCasaAtual == null)
            throw new IllegalStateException("Nenhuma casa selecionada.");
    }


}
