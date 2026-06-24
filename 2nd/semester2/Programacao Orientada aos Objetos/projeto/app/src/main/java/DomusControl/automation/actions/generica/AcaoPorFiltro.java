package DomusControl.automation.actions.generica;

import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.AcaoComposta;
import DomusControl.automation.interfaces_genericas.FactoryAcao;
import DomusControl.automation.interfaces_genericas.FiltroDispositivo;
import DomusControl.device.Dispositivo;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.AcaoNaoReversivelException;
import DomusControl.home.Casa;

public class AcaoPorFiltro implements AcaoComposta, AcaoComInversa {
    private FiltroDispositivo filtro;
    private FactoryAcao factory;

    public AcaoPorFiltro(FiltroDispositivo filtro, FactoryAcao factory) {
        this.filtro = filtro;
        this.factory = factory;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreVariosDispositivos(filtro, 
            d -> {
                Acao acao = factory.apply(d);
                acao.executar(casa);
            }
        );
    }

    @Override
    public Acao inversa() {
        return new AcaoPorFiltro(
            filtro,
            this::gerarAcaoInversa
        );
    }

    private Acao gerarAcaoInversa(Dispositivo d) {
        Acao acao = factory.apply(d);

        if (!(acao instanceof AcaoComInversa ai)) {
            throw new AcaoNaoReversivelException(d.getId());
        }

        return ai.inversa();
    }

    public String toString() {
        return "Aplicar ação a vários dispositivos";
    }
}