package DomusControl.exceptions.casa;

import DomusControl.exceptions.DomusControlException;

public class DivisaoInexistenteException extends DomusControlException {
    public DivisaoInexistenteException(String msg) {
        super(msg);
    }
}