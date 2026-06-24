package DomusControl.exceptions.casa;

import DomusControl.exceptions.DomusControlException;

public class DivisaoJaExisteException extends DomusControlException {
    public DivisaoJaExisteException(String msg) {
        super(msg);
    }
}