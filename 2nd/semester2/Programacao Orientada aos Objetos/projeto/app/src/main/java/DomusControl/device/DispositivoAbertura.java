package DomusControl.device;

import DomusControl.exceptions.dispositivo.AberturaInvalidaException;

public abstract class DispositivoAbertura extends Dispositivo {
    private int abertura; // 0 - 100% grau de abertura
    private double tempoTotal; // tempo que demora abrir/fechar totalmente 

    public DispositivoAbertura(String id,String marca,String modelo,double consumoPorHora, double tempoTotal) {
        super(id,marca,modelo,consumoPorHora);
        this.abertura = 0;
        this.tempoTotal = tempoTotal;
    }
    
    public DispositivoAbertura() {
        super();
        this.abertura = 0;
        this.tempoTotal = 0.01;
    }

    public DispositivoAbertura(DispositivoAbertura c) {
        super(c);
        this.abertura = c.getAbertura();
        this.tempoTotal = c.getTempoTotal();
    }

    public int getAbertura() {
        return abertura;
    }

    public void setAbertura(int novaAbertura) throws AberturaInvalidaException {
        if (novaAbertura < 0 || novaAbertura > 100)
            throw new AberturaInvalidaException(""+novaAbertura);

        if (novaAbertura != this.abertura) {
            int diferenca = Math.abs(novaAbertura - this.abertura);
            double tempo = (diferenca / 100.0) * this.tempoTotal;

            registarAtivacao();
            adicionarConsumo(tempo);
            this.abertura = novaAbertura;
        }
    }

    public double getTempoTotal() {
        return tempoTotal;
    }

    public void setTempoTotal(double tempoTotal) {
        this.tempoTotal = tempoTotal;
    }

    public void abrir() {
        if (this.abertura < 100) {
            registarAtivacao();
            adicionarConsumo(this.tempoTotal);
            this.abertura = 100;
        }
    }

    public void fechar() {
        if (this.abertura > 0) {
            registarAtivacao();
            adicionarConsumo(this.tempoTotal);
            this.abertura = 0;
        }
    }

    public boolean isFechada() {
        return this.abertura == 0;
    }

    public boolean isAberta() {
        return this.abertura > 0;
    }

    // Clone abstrato → cada subclasse implementa
    public abstract DispositivoAbertura clone();

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        DispositivoAbertura c = (DispositivoAbertura) o;
        return super.equals(o) &&
             c.getAbertura() == this.abertura;
    }

    @Override
    public String toString() {
        return super.toString() + ", abertura(%) = " + this.abertura;
    }

    @Override
     public int hashCode() {
        return super.hashCode() * 31 + Integer.hashCode(this.abertura);
    }

}
