package DomusControl.exceptions.dispositivo;

import DomusControl.exceptions.DomusControlException;

public class DispositivoJaExisteException extends DomusControlException {
    public DispositivoJaExisteException(String msg) {
        super(msg);
    }
}
