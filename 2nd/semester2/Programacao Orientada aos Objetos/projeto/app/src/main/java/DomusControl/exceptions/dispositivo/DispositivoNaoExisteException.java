package DomusControl.exceptions.dispositivo;

import DomusControl.exceptions.DomusControlException;

public class DispositivoNaoExisteException extends DomusControlException {
    public DispositivoNaoExisteException(String msg) {
        super(msg);
    }
}