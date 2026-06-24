package DomusControl.device;

import java.time.LocalDateTime;

import DomusControl.exceptions.dispositivo.CorInvalidadeException;
import DomusControl.exceptions.dispositivo.IntensidadeInvalidaException;

public class Lampada extends DispositivoOnOff {
    private int intensidadeLuminosa; // 0 - 100
    private int temperaturaCor; // vai da escala dos 2700K até 4000K

    public Lampada(String id,String marca,String modelo,double consumoPorHora) {
        super(id,marca,modelo,consumoPorHora);
        this.intensidadeLuminosa = 0;
        this.temperaturaCor = 2700;
    }

    public Lampada() {
        super();
        this.intensidadeLuminosa = 0;
        this.temperaturaCor = 2700;
    }

    public Lampada(Lampada l) {
        super(l);
        this.intensidadeLuminosa = l.getIntensidadeLuminosa();
        this.temperaturaCor = l.getTemperaturaCor();
    }

    public int getIntensidadeLuminosa() {
        return this.intensidadeLuminosa;
    }

    public void setIntensidadeLuminosa(int novaIntensidade) throws IntensidadeInvalidaException {
        if (novaIntensidade < 0 || novaIntensidade > 100)
            throw new IntensidadeInvalidaException(""+novaIntensidade);

        this.intensidadeLuminosa = novaIntensidade;
    }

    public int getTemperaturaCor() {
        return temperaturaCor;
    }

    public void setTemperaturaCor(int novaTemperaturaCor) throws CorInvalidadeException {
        if (novaTemperaturaCor < 2700 || novaTemperaturaCor > 4000)
            throw new CorInvalidadeException(""+novaTemperaturaCor);

        this.temperaturaCor = novaTemperaturaCor;
    }

    public void ligar(LocalDateTime tempoAtual, int intensidade, int temperaturaCor) throws IntensidadeInvalidaException,CorInvalidadeException {
        super.ligar(tempoAtual);

        setIntensidadeLuminosa(intensidade);
        setTemperaturaCor(temperaturaCor);
    }

    @Override
    public void ligar(LocalDateTime tempoAtual) {
        super.ligar(tempoAtual);
        this.intensidadeLuminosa = 50;
        this.temperaturaCor = 2700;
    }

    @Override
    public void desligar(LocalDateTime tempoAtual) {
        super.desligar(tempoAtual);
        this.intensidadeLuminosa = 0;
    }

    @Override 
    public Lampada clone() {
        return new Lampada(this);
    }

    @Override 
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass())) 
            return false;

        Lampada l = (Lampada) o;
        return  super.equals(o) &&
               l.getIntensidadeLuminosa() == this.intensidadeLuminosa &&
               l.getTemperaturaCor() == this.temperaturaCor;
    }

    @Override 
    public String toString() {
        return super.toString() + 
              ", intensidade = " + this.intensidadeLuminosa +
              ", temperaturaCor = " + this.temperaturaCor;
    }

    @Override
    public int hashCode() {
        return super.hashCode() * 31 + Integer.hashCode(intensidadeLuminosa) * 17 + Integer.hashCode(temperaturaCor);
    }

}
