package DomusControl.automation.actions.onoff.lampada;

import DomusControl.home.Casa;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.Lampada;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;

public class AlterarCor implements AcaoSimples {
    private String idDispositivo;
    private int temperatura;

    public AlterarCor(String idDispositivo, int temperaturaCor) {
        this.idDispositivo = idDispositivo;
        this.temperatura = temperaturaCor;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public int getTemperatura() {
        return temperatura;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof Lampada lampada)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }

            lampada.setTemperaturaCor(temperatura);
            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AlterarCor a = (AlterarCor)o;
        return a.getIdDispositivo().equals(this.idDispositivo) &&
               a.getTemperatura() == this.temperatura;
    }

    public String toString() {
         return "Alterar cor do " + this.idDispositivo + "para " + this.temperatura;
    }
}