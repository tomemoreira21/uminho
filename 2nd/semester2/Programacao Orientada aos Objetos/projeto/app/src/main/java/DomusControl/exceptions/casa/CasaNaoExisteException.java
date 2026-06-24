package DomusControl.exceptions.casa;

import DomusControl.exceptions.DomusControlException;

public class CasaNaoExisteException extends DomusControlException {
    public CasaNaoExisteException(String msg) {
        super(msg);
    }
}
