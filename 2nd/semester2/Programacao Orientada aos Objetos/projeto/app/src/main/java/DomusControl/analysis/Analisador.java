package DomusControl.analysis;

import java.io.Serializable;
import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

import DomusControl.automation.Automacao;
import DomusControl.automation.AutomacaoEvento;
import DomusControl.automation.actions.TipoAcao;
import DomusControl.automation.actions.abertura.Abrir;
import DomusControl.automation.actions.abertura.Fechar;
import DomusControl.automation.actions.onoff.Desligar;
import DomusControl.automation.actions.onoff.Ligar;
import DomusControl.automation.conditions.CondicaoHorarioExato;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.Condicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;

//composição
public class Analisador implements Serializable {
    private Map<Padrao, Integer> buffer;
    private Map<Padrao, Set<LocalDate>> diasPorPadrao;
    private List<Automacao> sugestoes;

    private static int quantidadeNec = 7;    // mínimo de ocorrências para gerar sugestão

    public Analisador() {
        this.buffer = new HashMap<>();
        this.sugestoes = new ArrayList<>();
        this.diasPorPadrao = new HashMap<>();
    }

    public Analisador(Analisador a) {
        this.buffer = a.getBuffer();
        this.sugestoes = a.getSugestoes();
        this.diasPorPadrao = a.getDiasPorPadrao();
    }

    public void registarPadrao(Padrao chave, LocalDateTime t) {
        LocalDate dia = t.toLocalDate();

        if (this.diasPorPadrao.containsKey(chave)) {  //contains usa o equals do padrao. assim não permitimos a contagem de açoes repetidas num curto intervalo de tempo
            if (!this.diasPorPadrao.get(chave).contains(dia)) {
                buffer.put(chave, buffer.getOrDefault(chave,0) + 1);
                this.diasPorPadrao.get(chave).add(dia);
            }
        }
        
        else {
            Set<LocalDate> dias = new HashSet<>();
            dias.add(dia);
            this.diasPorPadrao.put(chave, dias);
            this.buffer.put(chave, 1);
        }
        
    }

    public void analisar(Casa casa) throws DomusControlException {
        sugestoes.clear();

        Set<List<Padrao>> grupos = this.agruparPadroes();

        for (List<Padrao> grupo: grupos) {
            Automacao sugestao = construirSugestao(grupo, casa);
            if (sugestao != null) {
                this.sugestoes.add(sugestao);
            }
        }
}

    // Constrói uma Automacao a partir de um padrão
    private Automacao construirSugestao(List<Padrao> grupo, Casa casa) throws DomusControlException {
        List<Acao> acoes = new ArrayList<>();

        for (Padrao padrao: grupo) {
            String idDispositivo = padrao.getIdDispositivo();
            TipoAcao tipoAcao = padrao.getTipoDeAcao();
            Acao acao;

            switch (tipoAcao) {
                case TipoAcao.LIGAR:
                    acao = new Ligar(idDispositivo); 

                    acoes.add(acao);
                    break;

                case TipoAcao.DESLIGAR:
                    acao = new Desligar(idDispositivo);

                    acoes.add(acao);
                    break;

                case TipoAcao.ABRIR:
                    acao = new Abrir(idDispositivo);

                    acoes.add(acao);
                    break;
                
                case TipoAcao.FECHAR:
                    acao = new Fechar(idDispositivo);

                    acoes.add(acao);
                    break;
            
                default:
                    break;
            }
        }

        if (grupo.isEmpty()) return null;

        Condicao condicao = new CondicaoHorarioExato(grupo.get(0).getHoraAprox()); 
        return new AutomacaoEvento(condicao,acoes,casa.getUtilizadorPorEmail(grupo.get(0).getEmailUtilizador()));
    }

    private Set<List<Padrao>> agruparPadroes() {
        Set<List<Padrao>> grupos = new HashSet<>();

        List<Padrao> processados = new ArrayList<>(); //esta lista serve para evitar analisar o mesmo grupo de padrões várias vezes
        for (Padrao padrao : buffer.keySet()) {
            if (processados.contains(padrao) || this.buffer.getOrDefault(padrao,0) < Analisador.getQuantidadeNec()) continue;

            List<Padrao> grupo = new ArrayList<>();   // para cada padrão vamos cirar uma lista de padrões semelhantes
            for (Padrao outro : buffer.keySet()) {
                if (processados.contains(outro)) continue;

                if (dentroDoIntervalo(padrao.getHoraAprox(), outro.getHoraAprox()) 
                    && padrao.getEmailUtilizador().equals(outro.getEmailUtilizador())
                    && this.buffer.getOrDefault(outro,0) >= Analisador.getQuantidadeNec()) { //um padrao vai se comparar com ele proprio em algum momento
                    processados.add(outro);
                    grupo.add(outro);
                }
            }

            if (!grupo.isEmpty()) { //esta condição deverá dar sempre true,mas ponho por causa dos testes
                grupos.add(grupo);
            }
        }

        return grupos;
    }

    public void limparSugestoes() {
        this.sugestoes.clear();
        this.buffer.clear();
        this.diasPorPadrao.clear();
    }

    public List<Automacao> getSugestoes() {
        return this.sugestoes.stream().map(Automacao :: clone).collect(Collectors.toList());
    }

    public Map<Padrao, Integer> getBuffer() {
        Map<Padrao, Integer> res = new HashMap<>();

        for(Map.Entry<Padrao, Integer> entry: this.buffer.entrySet()) {
            res.put(entry.getKey().clone(), entry.getValue());
        }

        return res;
    }

    public Map<Padrao, Set<LocalDate>> getDiasPorPadrao() {
        Map<Padrao, Set<LocalDate>> res = new HashMap<>();

        for(Map.Entry<Padrao, Set<LocalDate>> entry: this.diasPorPadrao.entrySet()) {
            Set<LocalDate> aux = new HashSet<>(entry.getValue());
            res.put(entry.getKey().clone(), aux);
        }

        return res;
    }

    public static int getQuantidadeNec() { 
        return Analisador.quantidadeNec; 
    }
    public static void setQuantidadeNec(int q) { 
        Analisador.quantidadeNec = q; 
    }

    private boolean dentroDoIntervalo(LocalTime t1, LocalTime t2) {
        return Math.abs(Duration.between(t1, t2).toMinutes()) <= 10;
    }

    public boolean temSugestoes() {
        return !this.sugestoes.isEmpty();
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || this.getClass() != o.getClass()) return false;

        Analisador a = (Analisador) o;
        return this.buffer.equals(a.getBuffer()) && this.sugestoes.equals(a.getSugestoes());
    }

    public Analisador clone() {
        return new Analisador(this);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Analisador {\n");

        sb.append("  Buffer:\n");
        for (Map.Entry<Padrao, Integer> entry : buffer.entrySet()) {
            sb.append("    ")
            .append(entry.getKey())
            .append(" -> ")
            .append(entry.getValue())
            .append("\n");
        }

        sb.append("  Sugestoes:\n");
        for (Automacao a : sugestoes) {
            sb.append("    ")
            .append(a)
            .append("\n");
        }

        sb.append("}");

        return sb.toString();
    }
}
