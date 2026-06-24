package DomusControl.automation.core;

import java.io.Serializable;

import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;

public interface Acao extends Serializable {
    public void executar(Casa casa) throws DomusControlException;
} 