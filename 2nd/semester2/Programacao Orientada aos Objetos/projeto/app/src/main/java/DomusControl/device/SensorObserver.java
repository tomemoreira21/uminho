package DomusControl.device;

import java.io.Serializable;

import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface SensorObserver extends Serializable {
    void valorAlterado(String idDispositivo) throws DomusControlException;
}
