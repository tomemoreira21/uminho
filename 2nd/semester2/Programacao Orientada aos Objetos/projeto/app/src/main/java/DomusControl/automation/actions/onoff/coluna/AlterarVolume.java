package DomusControl.automation.actions.onoff.coluna;

import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.ColunaSom;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class AlterarVolume implements AcaoSimples {
    private String idDispositivo;
    private int volume;

    public AlterarVolume(String idDispositivo,int volume) {
        this.idDispositivo = idDispositivo;
        this.volume = volume;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public int getVolume() {
        return volume;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException { 
        casa.executarSobreDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof ColunaSom coluna)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }
                
            coluna.setVolume(volume);

            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AlterarVolume a = (AlterarVolume)o;
        return a.getIdDispositivo().equals(this.idDispositivo) &&
               a.getVolume() == this.volume;
    }

    public String toString() {
         return "Alterar volume do " + this.idDispositivo + "para " + this.volume;
    }
}