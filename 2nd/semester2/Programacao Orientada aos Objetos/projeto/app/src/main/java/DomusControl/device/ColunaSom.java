package DomusControl.device;

import java.time.LocalDateTime;

import DomusControl.exceptions.dispositivo.VolumeInvalidoException;

public class ColunaSom extends DispositivoOnOff {
    private int volume; // 0 - 100

    public ColunaSom(String id,String marca,String modelo,double consumoPorHora) {
        super(id,marca,modelo,consumoPorHora);
        this.volume = 0;
    }

    public ColunaSom() {
        super();
        this.volume = 0;
    }

    public ColunaSom(ColunaSom c) {
        super(c);
        this.volume = c.getVolume();
    }

    public int getVolume() {
        return this.volume;
    }

    public void setVolume(int novoVolume) throws VolumeInvalidoException {
        if (novoVolume < 0 || novoVolume > 100) {
            throw new VolumeInvalidoException(""+novoVolume);
        }

        this.volume = novoVolume;
    }

    public void ligar(LocalDateTime tempoAtual, int volume) throws VolumeInvalidoException {
        super.ligar(tempoAtual);
        setVolume(volume);
    }

    @Override
    public void ligar(LocalDateTime tempoAtual) {
        super.ligar(tempoAtual);
        this.volume = 50;
    }

    @Override
    public void desligar(LocalDateTime tempoAtual) {
        super.desligar(tempoAtual);
        this.volume = 0;
    }

    @Override
    public ColunaSom clone() {
        return new ColunaSom(this);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        ColunaSom c = (ColunaSom) o;
        return super.equals(o) &&
               c.getVolume() == this.volume;
    }

    @Override
    public String toString() {
        return super.toString() + ", volume = " + this.volume;
    }

    @Override
    public int hashCode() {
        return super.hashCode() * 31 + Integer.hashCode(this.volume);
    }


}
