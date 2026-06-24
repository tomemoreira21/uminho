package DomusControl.automation;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import DomusControl.automation.core.Acao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;
import DomusControl.users.Utilizador;

// agregacao 
public class Cenario implements Serializable{
    private String nome;
    private List<Acao> acoes;
    private Utilizador user;

    public Cenario(String nome,List<Acao> acoes, Utilizador user) {
        this.nome = nome;
        this.acoes = new ArrayList<Acao>(acoes);
        this.user = user;
    }

    public Cenario() {
        this.nome = ""; 
        this.acoes = new ArrayList<Acao>();
        this.user = new Utilizador();
    }

    public Cenario(Cenario c) {
        this.nome = c.getNome();    
        this.acoes = c.getAcoes();
        this.user = c.getUser();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public List<Acao> getAcoes() {
        return this.acoes.stream().collect(Collectors.toList());
    }

    public void setAcoes(List<Acao> acoes) {
        this.acoes = new ArrayList<>(acoes);
    }

    public Utilizador getUser() {
        return user;
    }

    public void setUser(Utilizador user) {
        this.user = user;
    }

    public void ativar(Casa casa) throws DomusControlException {
        for (Acao a : acoes) {
            a.executar(casa);
        }
    }

    public Cenario clone() {
        return new Cenario(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Cenario c = (Cenario) o;
        return c.getNome().equals(this.nome) &&
              c.getAcoes().equals(this.acoes) && 
              c.getUser().equals(this.user);
    }

    public String toString() {
        return "nome = " + this.nome + ", acoes = " + this.acoes + ", user = " + this.user;        
    }

    public int hashCode() {
        return Objects.hash(this.nome,this.acoes,this.user);
    }
}
