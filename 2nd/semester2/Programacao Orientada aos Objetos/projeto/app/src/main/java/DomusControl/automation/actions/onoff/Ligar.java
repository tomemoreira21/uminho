package DomusControl.automation.actions.onoff;

import DomusControl.automation.actions.TipoAcao;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoAutomatizavel;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.home.Casa;
import DomusControl.device.DispositivoOnOff;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;

public class Ligar implements AcaoSimples, AcaoComInversa, AcaoAutomatizavel {
    private String idDispositivo;
    private TipoAcao tipoAcao;

    public Ligar(String id) {
        this.idDispositivo = id;
        this.tipoAcao = TipoAcao.LIGAR;
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
                if (!(d instanceof DispositivoOnOff disp)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }

            disp.ligar(casa.getTempoAtual());
            }
        );
    }

    @Override
    public Acao inversa() {
        return new Desligar(idDispositivo);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Ligar l = (Ligar)o;
        return l.getIdDispositivo().equals(this.idDispositivo) &&
               l.getTipoAcao() == this.tipoAcao;
    }

    public String toString() {
         return "Ligar dispositivo " + this.idDispositivo;
    }
}