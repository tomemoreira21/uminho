package DomusControl.exceptions.casa;

import DomusControl.exceptions.DomusControlException;

public class UtilizadorNaoExisteException extends DomusControlException {
    public UtilizadorNaoExisteException(String msg) {
        super(msg);
    }
}
