package DomusControl.device;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.Objects;

public abstract class DispositivoOnOff extends Dispositivo {
    private boolean ligado;
    private LocalDateTime ultimoLigado;

    public DispositivoOnOff(String id,String marca,String modelo,double consumoPorHora) {
        super(id, marca, modelo, consumoPorHora);
        this.ligado = false;
        this.ultimoLigado = null;
    }

    public DispositivoOnOff() {
        super();
        this.ligado = false;
        this.ultimoLigado = null;
    }

    public DispositivoOnOff(DispositivoOnOff d) {
        super(d);
        this.ligado = d.isLigado();
        this.ultimoLigado = d.getUltimoLigado();
    }

    public boolean isLigado() {
        return ligado;
    }

    public void setLigado(boolean ligado) {
        this.ligado = ligado;
    }

    public LocalDateTime getUltimoLigado() {
        return ultimoLigado;
    }

    public void setUltimoLigado(LocalDateTime ultimoLigado) {
        this.ultimoLigado = ultimoLigado;
    }

    // utiliza, a variável tempo local
    public void ligar(LocalDateTime tempoAtual) {
        if (!ligado) {
            ligado = true;
            registarAtivacao();
            ultimoLigado = tempoAtual;
        }
    }

    public void desligar(LocalDateTime tempoAtual) {
        if (ligado) {
            ligado = false;
            registarAtivacao();
            Duration duracao = Duration.between(ultimoLigado, tempoAtual);
            adicionarConsumo(duracao.toSeconds() / 3600.0);
        }
    }

    // faz o ajuste de se estiver ligado
    @Override
    public double consumoTotal(LocalDateTime tempoAtual) {
        double tempoTotal = this.getTempoAtivo();

        if (ligado && this.ultimoLigado != null) {
            Duration duracao = Duration.between(ultimoLigado, tempoAtual);
            tempoTotal += duracao.toSeconds() / 3600.0;
        }

        return tempoTotal * this.getConsumoPorHora();
    }

    public abstract DispositivoOnOff clone();

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        DispositivoOnOff d = (DispositivoOnOff) o;
        return super.equals(d) &&
               d.isLigado() == this.ligado &&
               ((d.getUltimoLigado() == null && this.ultimoLigado == null) ||
               (d.getUltimoLigado() != null && d.getUltimoLigado().equals(this.ultimoLigado)));
    }

    @Override
    public String toString() {
        return super.toString() + ", ligado = " + this.ligado;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(),this.ligado,this.ultimoLigado);
    }
}

