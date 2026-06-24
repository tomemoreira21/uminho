package DomusControl.automation.core;

import java.io.Serializable;

import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;

public interface Condicao extends Serializable {
    public boolean verificar(Casa casa) throws DomusControlException;
} 
