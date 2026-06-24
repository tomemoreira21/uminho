package DomusControl.automation.core;

import DomusControl.automation.actions.TipoAcao;

public interface AcaoAutomatizavel extends Acao {
    public TipoAcao getTipoAcao();
    public String getIdDispositivo();
} 