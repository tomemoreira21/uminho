package DomusControl.ui.interfaces_genericas;

import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface ThrowingConsumer<T> {
    void accept(T t) throws DomusControlException;
}