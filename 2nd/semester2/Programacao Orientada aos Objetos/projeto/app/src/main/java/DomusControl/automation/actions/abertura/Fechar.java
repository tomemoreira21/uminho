package DomusControl.automation.actions.abertura;

import DomusControl.automation.actions.TipoAcao;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoAutomatizavel;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.DispositivoAbertura;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class Fechar implements AcaoSimples, AcaoComInversa, AcaoAutomatizavel {
    private String idDispositivo;
    public TipoAcao tipoAcao;

    public Fechar(String idDispositivo) {
        this.idDispositivo = idDispositivo;
        this.tipoAcao = TipoAcao.FECHAR;
    }

    public TipoAcao getTipoAcao () {
        return this.tipoAcao;
    }

    public String getIdDispositivo() {
        return this.idDispositivo;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof DispositivoAbertura disp)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }

                disp.fechar();
            }
        );
    }

    @Override
    public Acao inversa() {
        return new Abrir(idDispositivo);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Fechar f = (Fechar) o;
        return f.getIdDispositivo().equals(this.idDispositivo) &&
               f.getTipoAcao() == this.tipoAcao;
    }

    public String toString() {
        return "Fechar dispositivo " + this.idDispositivo;
    }
}

