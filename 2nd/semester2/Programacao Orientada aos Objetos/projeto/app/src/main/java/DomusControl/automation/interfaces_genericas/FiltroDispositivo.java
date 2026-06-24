package DomusControl.automation.interfaces_genericas;

import java.io.Serializable;

import DomusControl.device.Dispositivo;
import DomusControl.home.Casa;

@FunctionalInterface
public interface FiltroDispositivo extends Serializable {
    boolean test(Casa casa, Dispositivo d);
}