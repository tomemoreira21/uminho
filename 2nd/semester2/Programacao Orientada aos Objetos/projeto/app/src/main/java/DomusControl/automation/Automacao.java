package DomusControl.automation;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import DomusControl.automation.conditions.CondicaoSensor;
import DomusControl.automation.conditions.CondicaoTemporal;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.Condicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;
import DomusControl.users.Utilizador;

// agregacao
public abstract class Automacao implements Serializable {
    private Condicao condicao;
    private List<Acao> acoes;
    private Utilizador user; // quem foi o responsável por criar a automacao

    public Automacao(Condicao condicao,List<? extends Acao> acoes, Utilizador user) {
        this.condicao = condicao;
        this.acoes = new ArrayList<>(acoes);
        this.user = user;
    }

    public Automacao() {
        this.condicao = null;
        this.acoes = new ArrayList<Acao>();
        this.user = new Utilizador();
    }

    public Automacao(Automacao a) {
        this.condicao = a.getCondicao();
        this.acoes = a.getAcoes();
        this.user = a.getUtilizador();
    }
    
    public Condicao getCondicao() {
        return this.condicao;
    }

    public void setCondicao(Condicao condicao) {
        this.condicao = condicao;
    }

    public List<Acao> getAcoes() {
        return this.acoes.stream().collect(Collectors.toList());
    }

    public void setAcoes(List<Acao> acoes) {
        this.acoes = new ArrayList<>(acoes);
    }

    public Utilizador getUtilizador() {
        return this.user;
    }

    public void setUtilizador(Utilizador u) {
        this.user = u;
    }

    // devolve se a automacao depende do tempo
    public boolean eTemporal() {
        return this.condicao instanceof CondicaoTemporal;
    }

    // responsável por verificar se um dispositivo de medição está associada à condicao
    public boolean estaAssociadoADispositivo(String idDispositivo) throws DomusControlException {
        return this.condicao instanceof CondicaoSensor cs &&
               cs.getIdDispositivo().equals(idDispositivo);
    }

    public abstract void avaliarAutomacao(Casa casa) throws DomusControlException;
    public abstract Automacao clone();
        
    public boolean equals(Object o) {
        if (o == this) 
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Automacao a = (Automacao) o;
        return a.getCondicao().equals(this.condicao) &&
               a.getAcoes().equals(this.acoes) &&
               a.getUtilizador().equals(this.user);
    }

    public String toString() {
        return "condicao = " + this.condicao + ", acoes = " + this.acoes + ", user = " + this.user;
    }

    public int hashCode() {
        return Objects.hash(this.condicao,this.acoes,this.user);
    }

}
