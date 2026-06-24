package DomusControl.automation.interfaces_genericas;

import java.io.Serializable;

import DomusControl.device.Dispositivo;
import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface ConsultaDispositivo<T> extends Serializable {
    T apply(Dispositivo d) throws DomusControlException;
}