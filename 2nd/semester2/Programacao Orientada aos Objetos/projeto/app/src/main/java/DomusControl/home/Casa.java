package DomusControl.home;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

import DomusControl.analysis.Analisador;
import DomusControl.analysis.Padrao;
import DomusControl.automation.Automacao;
import DomusControl.automation.Cenario;
import DomusControl.automation.actions.TipoAcao;
import DomusControl.automation.core.AcaoAutomatizavel;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.automation.interfaces_genericas.ConsultaDispositivo;
import DomusControl.automation.interfaces_genericas.FiltroDispositivo;
import DomusControl.automation.interfaces_genericas.OperacaoDispositivo;
import DomusControl.device.Dispositivo;
import DomusControl.device.DispositivoMedicao;
import DomusControl.device.SensorObserver;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.casa.AcessoNegadoException;
import DomusControl.exceptions.casa.AcessoRepetidoException;
import DomusControl.exceptions.casa.CenarioInexistenteException;
import DomusControl.exceptions.casa.DivisaoInexistenteException;
import DomusControl.exceptions.casa.DivisaoJaExisteException;
import DomusControl.exceptions.casa.UtilizadorNaoExisteException;
import DomusControl.exceptions.dispositivo.DispositivoJaExisteException;
import DomusControl.exceptions.dispositivo.DispositivoNaoExisteException;
import DomusControl.services.ComparatorTempoAtivacoes;
import DomusControl.users.CasaAcesso;
import DomusControl.users.Papel;
import DomusControl.users.Utilizador;

// sensor já contém Serializable
public class Casa implements SensorObserver {
    private String nome;
    private Set<CasaAcesso> acessos; // serve para adicionar os users associando-lhes o seu papel
    private Map<String, Set<Dispositivo>> divisoes; // nome da divisao, mapeia para a classe divisao (nome -> Set<Ids>)
    private Map<String,Dispositivo> dispositivos; // dispositivos todos da casa, com (id -> dispositivo)
    private Set<Automacao> automacoes; // conjunto de automações/escalonamentos definidos pelo user para a casa
    private Map<String,Cenario> cenarios; // cenários definidos pelos utilizadores referentes à casa (nome -> cenário)
    private Analisador analisador; //composição

    private LocalDateTime tempoAtual;

    public Casa(String nome) {
        this.nome = nome;
        this.acessos = new HashSet<CasaAcesso>();
        this.divisoes = new HashMap<String, Set<Dispositivo>>();
        this.dispositivos = new HashMap<String,Dispositivo>();
        this.automacoes = new HashSet<Automacao>();
        this.cenarios = new HashMap<String, Cenario>();
        this.analisador = new Analisador();
        this.tempoAtual = LocalDateTime.now();
    }

    public Casa() {
        this.nome = "";
        this.acessos = new HashSet<CasaAcesso>();
        this.divisoes = new HashMap<String, Set<Dispositivo>>();
        this.dispositivos = new HashMap<String,Dispositivo>();
        this.automacoes = new HashSet<Automacao>();
        this.cenarios = new HashMap<String, Cenario>();
        this.analisador = new Analisador();
        this.tempoAtual = LocalDateTime.now();
    }

    public Casa(Casa c) {
        this.nome = c.getNome();
        this.acessos = c.getAcessos();
        this.divisoes = c.getDivisoes();
        this.dispositivos = c.getDispositivos();
        this.automacoes = c.getAutomacoes();
        this.cenarios = c.getCenarios();
        this.analisador = c.getAnalisador();
        this.tempoAtual = c.getTempoAtual();
    }
   
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Set<CasaAcesso> getAcessos() {
        return this.acessos.stream().map(CasaAcesso :: clone).collect(Collectors.toSet());
    }

    public void setAcessos(Set<CasaAcesso> acessos) {
        Set<CasaAcesso> novos_acessos = new HashSet<>();

        for (CasaAcesso ca : acessos) 
            novos_acessos.add(ca.clone());

        this.acessos = novos_acessos;
    }

    public Utilizador getUtilizadorPorEmail(String email) throws DomusControlException { 
        Utilizador res = this.acessos.stream()
                        .map(CasaAcesso::getUtilizador)
                        .filter(u -> u.getEmail().equals(email))
                        .findFirst()
                        .orElse(null);

        if (res == null) 
            throw new UtilizadorNaoExisteException(email);

        return res.clone(); 
    }

    public Map<String,Set<Dispositivo>> getDivisoes() {
        Map<String,Set<Dispositivo>> novas_div = new HashMap<>();

        for (Map.Entry<String,Set<Dispositivo>> div : this.divisoes.entrySet()) {
            novas_div.put(div.getKey(),
                          div.getValue().stream().map(Dispositivo :: clone).collect(Collectors.toSet()));
        }

        return novas_div;
    }

    public void setDivisoes(Map<String,Set<Dispositivo>> divs) {
        Map<String,Set<Dispositivo>> novas_div = new HashMap<>();

        for (Map.Entry<String,Set<Dispositivo>> div : divs.entrySet()) {
            novas_div.put(div.getKey(),
                          div.getValue().stream().map(Dispositivo :: clone).collect(Collectors.toSet()));
        }

        this.divisoes = novas_div;
    }

    public Map<String,Dispositivo> getDispositivos() {
        Map<String,Dispositivo> novas_disp = new HashMap<>();

        for (Map.Entry<String,Dispositivo> disp : this.dispositivos.entrySet()) {
            novas_disp.put(disp.getKey(),disp.getValue().clone());
        }

        return novas_disp;
    }

    public void setDispositivos (Map<String,Dispositivo> dispositivos) {
        Map<String,Dispositivo> novas_disp = new HashMap<>();

        for (Map.Entry<String,Dispositivo> disp : dispositivos.entrySet()) {
            novas_disp.put(disp.getKey(),disp.getValue().clone());
        }

        this.dispositivos = novas_disp;
    }

    public Set<Automacao> getAutomacoes() {
        return this.automacoes.stream().map(Automacao :: clone).collect(Collectors.toSet());
    }

    public void setAutomacoes(Set<Automacao> automacoes) {
        Set<Automacao> novas_automacoes = new HashSet<>();

        for (Automacao a : automacoes) 
            novas_automacoes.add(a.clone());

        this.automacoes = novas_automacoes;
    }

    public Map<String,Cenario> getCenarios() {
        Map<String,Cenario> res = new HashMap<>();

        for (Map.Entry<String,Cenario> e : this.cenarios.entrySet()) {
            res.put(e.getKey(), e.getValue().clone());
        }

        return res;
    }

    public void setCenarios(Map<String,Cenario> cenarios) {
        Map<String,Cenario> novos_cenarios = new HashMap<>();

        for (Map.Entry<String,Cenario> e : cenarios.entrySet()) {
            novos_cenarios.put(e.getKey(), e.getValue().clone());
        }

        this.cenarios = novos_cenarios;
    }

    public Analisador getAnalisador() {
        return this.analisador.clone();
    }

    public LocalDateTime getTempoAtual() {
        return tempoAtual;
    }

    public void setTempoAtual(LocalDateTime tempoAtual) {
        this.tempoAtual = tempoAtual;
    }

    public void avancarTempo(Duration d) throws DomusControlException {
        this.tempoAtual = this.tempoAtual.plus(d);
        executarAutomacoesTemporais(); // verifica se deve executar as automações temporais
    }

    // Método que verifica se um utilizador é admin, importante para as permissoes
    public boolean isAdmin(Utilizador u) {
        return this.acessos.stream()
                           .anyMatch(ca -> ca.getUtilizador().equals(u) && ca.isAdmin());
    }

    // testa somente se o user temAcesso à casa independentemente do papel
    public boolean temAcesso (Utilizador u) {
        return this.acessos.stream().anyMatch(a -> a.getUtilizador().equals(u));
    }

    // dá clear das sugestões geradas pelo analisador
    public void limparSugestoes() {
        this.analisador.limparSugestoes();
    }

    // verifica se um dispositivo pertence a uma divisao
    public boolean dispositivoPertenceDivisao(String nomeDivisao,Dispositivo d) {
        Set<Dispositivo> disp = this.divisoes.get(nomeDivisao);

        if (disp == null) return false;

        return disp.stream()
                   .anyMatch(x -> x.getId().equals(d.getId()));
    }

    // devolve o número de dispositivos por divisao
    public int getNumDispositivosDiv(String nomeDivisao) throws DomusControlException {
        if (!this.divisoes.containsKey(nomeDivisao))
            throw new DivisaoInexistenteException(nomeDivisao);

        return this.divisoes.get(nomeDivisao).size();
    }

    // deolve o dispositivo com clone
    public Dispositivo getDispositivo(String idDispositivo) throws DomusControlException {
        if (!this.dispositivos.containsKey(idDispositivo))
            throw new DispositivoNaoExisteException(idDispositivo);

        return this.dispositivos.get(idDispositivo).clone();
    }

    // devolve os dispositivos que obdecem ao filtro passado
    public List<Dispositivo> getDispositivosFiltrados(FiltroDispositivo filtro) {
        return this.dispositivos.values()
            .stream()
            .filter(d -> filtro.test(this,d))
            .map(Dispositivo :: clone)
            .collect(Collectors.toList());
    }

    // Devolve os dispositivos associados a uma divisão
    public Set<Dispositivo> getDispositivosDivisao(String divisao) throws DomusControlException {
         if (!this.divisoes.containsKey(divisao)) {
            throw new DivisaoInexistenteException(divisao);
         }

         return this.divisoes.get(divisao).stream()
                                          .map(Dispositivo :: clone) 
                                          .collect(Collectors.toSet());
    }

    // responsável por executar uma ação sobre um dispositivo
    public void executarSobreDispositivo(String id, OperacaoDispositivo op) throws DomusControlException {
        Dispositivo d = this.dispositivos.get(id);

        if (d == null) {
            throw new DispositivoNaoExisteException(id);
        }

        op.accept(d);
    }

    // responsável por executar uma acao a vários dispositivos que obdecem ao filtro
    public void executarSobreVariosDispositivos(FiltroDispositivo filtro, OperacaoDispositivo op) throws DomusControlException {
        for (Dispositivo d : this.dispositivos.values()) {
            if (filtro.test(this, d)) {
                op.accept(d);
            }
        }
    }

    // responsável por consultar informação de um dispositivo sem expor o apontador interno
    public <T> T consultarDispositivo(String id, ConsultaDispositivo<T> consulta) throws DomusControlException {
        Dispositivo d = this.dispositivos.get(id);

        if (d == null) {
            throw new DispositivoNaoExisteException(id);
        }

        return consulta.apply(d);
    }
        
    // Método que permite após criar o user dar-lhe o papel relativamente a esta casa
    public void addUtilizador(Utilizador u,Papel papel) throws DomusControlException {
        if (temAcesso((u))) {
            throw new AcessoRepetidoException(u.getEmail());
        }

        CasaAcesso ca = new CasaAcesso(u, this, papel);

        this.acessos.add(ca);
        u.addAcesso(ca); // mantém a consistência, adicionando também ao users
    }

    // Método que permite a criação de uma divisao
    public void addDivisao(Utilizador u, String nomeDivisao) throws DomusControlException {
        if (!isAdmin(u)) 
            throw new AcessoNegadoException(u.getEmail());

        if (this.divisoes.containsKey(nomeDivisao)) 
            throw new DivisaoJaExisteException(nomeDivisao);

        this.divisoes.put(nomeDivisao, new HashSet<Dispositivo>());   
    }

    // Método que adiciona um dispositivo não associando a nenhuma divisao (utilizado para sensores)
    public void addDispositivo(Utilizador u, Dispositivo d) throws DomusControlException {
        if (!isAdmin(u)) {
            throw new AcessoNegadoException(u.getEmail());
        }

        if (this.dispositivos.containsKey(d.getId()))
            throw new DispositivoJaExisteException(d.getId());

        Dispositivo clone = d.clone();

        // se for um dispositivo de medição então lança o observador para ele
        if (clone instanceof DispositivoMedicao sensor) {
            sensor.setObserver(this);
        }

        this.dispositivos.put(clone.getId(),clone);
    }

    // Associar um dispositivo a uma divisao
    public void addDispositivoADivisao(Utilizador u, String nomeDivisao, Dispositivo dispositivo) throws DomusControlException {
        if (!isAdmin(u)) 
            throw new AcessoNegadoException(u.getEmail());

        Set<Dispositivo> disp = divisoes.get(nomeDivisao);

        if (disp == null)
            throw new DivisaoInexistenteException(nomeDivisao);

        Dispositivo clone = dispositivo.clone(); // clone UMA vez (assim ambos têm o mesmo apontador)

        disp.add(clone);
        this.dispositivos.put(clone.getId(),clone); // casa
    }

    public double getConsumoTotalCasa() {
        return this.dispositivos.values()
                                .stream()
                                .mapToDouble(d -> d.consumoTotal(this.tempoAtual))
                                .sum();            
    }

    //Métodos para "querys" sobre uma casa
    public Map<String,Double> getConsumoMedioPorDivisao() {
        return this.getDivisoes().entrySet().stream()    
                                 .collect(Collectors.toMap(
                                        Map.Entry :: getKey,
                                        e -> {
                                            Set<Dispositivo> dispositivos = e.getValue();

                                            if (dispositivos.isEmpty()) return 0.0;
                                            
                                            double total = dispositivos.stream().
                                                                        mapToDouble(d -> d.consumoTotal(this.getTempoAtual())).sum();

                                            return total / dispositivos.size();
                                        }
                                 ));
    }

    //dá os dispositivos mais usados em termos de tempo e em caso de empate dá o que tiver o maior número de ativações. Em caso de empate ordena por id
    //Penso que List neste caso é melhor mas também poderíamos retornar um TreeSet
    // acho que este método devia ser dois um para tempo e outro para numero de ativicoes
    public List <Dispositivo> getTresDispositivosMaisUsados() {
        ComparatorTempoAtivacoes comp = new ComparatorTempoAtivacoes();

        return this.getDispositivos().values()
                                     .stream()
                                     .sorted(comp)
                                     .limit(3)
                                     .map(Dispositivo :: clone)
                                     .collect(Collectors.toList());
    }

    public void atuarDispositivo(Utilizador u, AcaoSimples acao) throws DomusControlException {
        if (!temAcesso(u))  // tanto os users como os admins podem interagir com dispositivo
            throw new AcessoNegadoException(u.getEmail());

        // Executa a ação sobre o dispositivo real
        acao.executar(this);
        
        // regista no analisar a ação
        if (acao instanceof AcaoAutomatizavel) {
            AcaoAutomatizavel acaoAutomatizavel = (AcaoAutomatizavel) acao;
            TipoAcao tipo = acaoAutomatizavel.getTipoAcao();
            Dispositivo dispositivo = this.dispositivos.get(acaoAutomatizavel.getIdDispositivo());

            Padrao padrao = new Padrao(this.tempoAtual, tipo, dispositivo.getId(), u.getEmail());
            this.analisador.registarPadrao(padrao,this.tempoAtual);
        }
    }

    public void addAutomacao(Automacao a) throws DomusControlException {
        if (!temAcesso(a.getUtilizador())) 
            throw new AcessoNegadoException(a.getUtilizador().getEmail()); 

        Automacao clone = a.clone();

        this.automacoes.add(clone);

        // verifica se já tem condições para executar no momento que é adicionada
        clone.avaliarAutomacao(this);
    }

    public void addCenario(Cenario c) throws DomusControlException {
        if (!temAcesso(c.getUser())) 
            throw new AcessoNegadoException(c.getUser().getEmail()); 

        this.cenarios.put(c.getNome(),c.clone());
    }

    // Executar automações temporais
    public void executarAutomacoesTemporais() throws DomusControlException {
        for (Automacao a : this.automacoes) {
            if (a.eTemporal()) {
                a.avaliarAutomacao(this);
            }
        }
    }

    // Executar a automação afetada pela variação do valor medido pelo sensor
    private void executarAutomacoesAssociadas(String idDispositivo) throws DomusControlException {
        for (Automacao a : this.automacoes) {
            if (a.estaAssociadoADispositivo(idDispositivo)) {
                a.avaliarAutomacao(this);
            }
        }
    }

   // possibilita executar cenários desde que tenha acesso à casa
   public void executarCenario(Utilizador u, String nome) throws DomusControlException {
        Cenario c = this.cenarios.get(nome);

        if (c == null) {
            throw new CenarioInexistenteException(nome);
        }

        if (!temAcesso(u)) {
            throw new AcessoNegadoException(nome);
        }

        c.ativar(this);
   }

   // responsável por ficar os padrões e contruir sugestões 
   public void analisarSugestoes() throws DomusControlException {
        this.analisador.analisar(this);
    }

    // realiza o necessário para refletir a alteração do valor do sensor 
    public void valorAlterado(String idDispositivo) throws DomusControlException {
        executarAutomacoesAssociadas(idDispositivo);
    }

    public Casa clone() {
        return new Casa(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Casa c = (Casa) o;
        return Objects.equals(this.nome, c.nome) &&
               Objects.equals(divisoes, c.divisoes) &&
               Objects.equals(dispositivos, c.dispositivos) &&
               Objects.equals(automacoes, c.automacoes) &&
               Objects.equals(cenarios, c.cenarios) &&
               Objects.equals(tempoAtual, c.tempoAtual);
    }

    public String toString() {
        return "nome = " + this.nome + ", divisoes =" + this.divisoes + ", automacoes = " + this.automacoes
        + ", cenarios = " + this.cenarios + ", analisador = " + this.analisador;
    }

    public int hashCode() {
        return Objects.hash(this.nome, this.divisoes, this.dispositivos, this.automacoes, this.cenarios, this.tempoAtual);
    }
}
