package DomusControl.users;

import java.io.Serializable;
import java.util.Objects;

import DomusControl.home.Casa;

// agregacao
public class CasaAcesso implements Serializable{
    private Utilizador utilizador;
    private Casa casa;
    private Papel papel;

    public CasaAcesso(Utilizador utilizador,Casa casa, Papel papel) {
        this.utilizador = utilizador;
        this.casa = casa;
        this.papel = papel;
    }

    public CasaAcesso() {
        this.utilizador = new Utilizador();
        this.casa = new Casa();
        this.papel = Papel.USER;
    }

    public CasaAcesso(CasaAcesso ca) {
        this.utilizador = ca.getUtilizador();
        this.casa = ca.getCasa();
        this.papel = ca.getPapel();
    }

    public Utilizador getUtilizador() {
        return this.utilizador;
    }

    public void setUser(Utilizador user) {
        this.utilizador = user;
    }

    public Casa getCasa() {
        return this.casa;
    }

    public void setCasa(Casa casa) {
        this.casa = casa;
    }

    public Papel getPapel() {
        return papel;
    }

    public void setPapel(Papel papel) {
        this.papel = papel;
    }

    public CasaAcesso clone() {
        return new CasaAcesso(this);
    }   

    public boolean isAdmin() {
        return this.papel == Papel.ADMIN;
    }

    public boolean isUser() {
        return this.papel == Papel.USER;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CasaAcesso ca = (CasaAcesso) o;
        return Objects.equals(this.utilizador, ca.utilizador) &&
                Objects.equals(this.casa, ca.casa) &&
                this.papel == ca.papel;
    }   

    public String toString() {
        return "utilizador = " + this.utilizador + ", casa = " + this.casa + 
        ", acesso = " + this.papel;
    }

    public int hashCode() {
        return Objects.hash(this.utilizador, this.casa.getNome(), this.papel);
    }
    
}
