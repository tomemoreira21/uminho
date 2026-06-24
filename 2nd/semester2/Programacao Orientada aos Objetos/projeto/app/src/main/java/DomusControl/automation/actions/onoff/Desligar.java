package DomusControl.automation.actions.onoff;

import DomusControl.automation.actions.TipoAcao;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoAutomatizavel;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.DispositivoOnOff;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class Desligar implements AcaoSimples, AcaoComInversa, AcaoAutomatizavel {
    private String idDispositivo;
    private TipoAcao tipoAcao;

    public Desligar(String id) {
        this.idDispositivo = id;
        this.tipoAcao = TipoAcao.DESLIGAR;
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

            disp.desligar(casa.getTempoAtual());
            }
        );
    }

    @Override
    public Acao inversa() {
        return new Ligar(idDispositivo);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Desligar d = (Desligar)o;
        return d.getIdDispositivo().equals(this.idDispositivo) &&
               d.getTipoAcao() == this.tipoAcao;
    }   

    public String toString() {
        return "Desligar dispositivo " + this.idDispositivo;
    }
}
