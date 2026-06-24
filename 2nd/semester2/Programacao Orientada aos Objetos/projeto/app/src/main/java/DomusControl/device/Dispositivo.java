package DomusControl.device;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Objects;

public abstract class Dispositivo implements Serializable {
    private String id;
    private String marca;
    private String modelo;
    private double consumoPorHora;

    private double tempoAtivo; // tempo ativo em horas
    private int numAtivacoes; // quantas vezes foi ativo

    public Dispositivo(String id,String marca,String modelo,double consumoPorHora) {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.consumoPorHora = consumoPorHora;
        this.tempoAtivo = 0;
        this.numAtivacoes = 0;
    }

    public Dispositivo() {
        this.id = "";
        this.marca = "";
        this.modelo = "";
        this.consumoPorHora = 1;
        this.tempoAtivo = 0;
        this.numAtivacoes = 0;
    }

    public Dispositivo(Dispositivo d) {
        this.id = d.getId();
        this.marca = d.getMarca();
        this.modelo = d.getModelo();
        this.consumoPorHora = d.getConsumoPorHora();
        this.tempoAtivo= d.getTempoAtivo();
        this.numAtivacoes = d.getNumAtivacoes();
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getModelo() {
        return this.modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public double getConsumoPorHora() {
        return this.consumoPorHora;
    }

    public void setConsumoPorHora(double consumoPorHora) {
        this.consumoPorHora = consumoPorHora;
    }

    public double getTempoAtivo() {
        return this.tempoAtivo;
    }

    public void setTempoAtivo(double tempoAtivo) {
        this.tempoAtivo = tempoAtivo;
    }

    public int getNumAtivacoes() {
        return this.numAtivacoes;
    }

    public void setNumAtivacoes(int numAtivacoes) {
        this.numAtivacoes = numAtivacoes;
    }

    public void registarAtivacao() {
        this.numAtivacoes++;
    }

    public void adicionarConsumo(double horas) {
        this.tempoAtivo += horas;
    }

    public double consumoTotal(LocalDateTime tempoAtual) {
        return this.tempoAtivo * this.consumoPorHora;
    }

    // Clone abstrato → cada subclasse implementa
    public abstract Dispositivo clone();

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Dispositivo d = (Dispositivo) o;
        return d.getId().equals(this.id) &&
               d.getMarca().equals(this.marca) &&
               d.getModelo().equals(this.modelo) &&
               Double.compare(d.getConsumoPorHora(), this.consumoPorHora) == 0 &&
               Double.compare(d.getTempoAtivo(), this.tempoAtivo) == 0 &&
               d.getNumAtivacoes() == this.numAtivacoes;
    }

    public String toString() {
        return "id = " + this.id + ", marca = " + this.marca + ", modelo = " + this.modelo + 
        ", consumoPorHora = " + this.consumoPorHora + 
        ", tempoAtivo = " + this.tempoAtivo + ", numAtivacoes = " + this.numAtivacoes;
    }

    public int hashCode() {
        return Objects.hash(this.id,this.marca,this.modelo,this.consumoPorHora,this.tempoAtivo,this.numAtivacoes);
    }
}
