package DomusControl.users;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public class Utilizador implements Serializable {
    private String nome;
    private String email;
    private Set<CasaAcesso> acessos;

    public Utilizador(String nome,String email) {
        this.nome = nome;
        this.email = email;
        this.acessos = new HashSet<CasaAcesso>();
    }

    public Utilizador() {
        this.nome = "";
        this.email = "";
        this.acessos = new HashSet<CasaAcesso>();
    }

    public Utilizador(Utilizador u) {
        this.nome = u.getNome();
        this.email = u.getEmail();
        this.acessos = u.getAcessos();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
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

    public void addAcesso(CasaAcesso ca) {
        this.acessos.add(ca.clone());
    }

    public Utilizador clone() {
        return new Utilizador(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Utilizador u = (Utilizador) o;
        return u.getNome().equals(this.nome) &&
               u.getEmail().equals(this.email) &&
               u.getAcessos().equals(this.acessos);
    }

    public String toString() {
        return "nome = " + this.nome + ", email = " + this.email;
    }

    public int hashCode() {
        return Objects.hash(this.nome + this.email + this.acessos);
    }
}