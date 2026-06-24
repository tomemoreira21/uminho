package DomusControl.automation.interfaces_genericas;

import java.io.Serializable;

import DomusControl.device.Dispositivo;
import DomusControl.exceptions.DomusControlException;

@FunctionalInterface

// acaba por ser igual ao consumer nao dei extens Consumer<Dispositivo> porque não permite lançar excepções
public interface OperacaoDispositivo  extends  Serializable {
    void accept(Dispositivo d) throws DomusControlException;
}
