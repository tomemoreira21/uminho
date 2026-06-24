package DomusControl.automation.actions.abertura;

import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.DispositivoAbertura;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class AlterarAbertura implements AcaoSimples {
    private String idDispositivo;
    private int abertura;

    public AlterarAbertura(String idDispositivo, int abertura) {
        this.idDispositivo = idDispositivo;
        this.abertura = abertura;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public int getAbertura() {
        return abertura;
    }
    
    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreDispositivo(idDispositivo,
            d -> {
                if (!(d instanceof DispositivoAbertura disp)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }

                disp.setAbertura(abertura);
            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AlterarAbertura a = (AlterarAbertura) o;
        return a.getIdDispositivo().equals(this.idDispositivo) &&
               a.getAbertura() == this.abertura;
    }
    
    public String toString() {
        return "Alterar abertura do " + this.idDispositivo + "para " + this.abertura;
    }
}
