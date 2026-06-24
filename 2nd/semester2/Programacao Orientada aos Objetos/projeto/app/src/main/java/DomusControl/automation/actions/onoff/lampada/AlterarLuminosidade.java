package DomusControl.automation.actions.onoff.lampada;

import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.Lampada;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class AlterarLuminosidade implements AcaoSimples {
    private String idDispositivo;
    private int intensidade;

    public AlterarLuminosidade(String idDispositivo, int intensidade) {
        this.idDispositivo = idDispositivo;
        this.intensidade = intensidade;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public int getIntensidade() {
        return intensidade;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof Lampada lampada)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }

            lampada.setIntensidadeLuminosa(intensidade);
            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AlterarLuminosidade a = (AlterarLuminosidade)o;
        return a.getIdDispositivo().equals(this.idDispositivo) &&
               a.getIntensidade() == this.intensidade;
    }

    public String toString() {
        return "Alterar intensidade luminosa do " + this.idDispositivo + "para " + this.intensidade;
    }
}
