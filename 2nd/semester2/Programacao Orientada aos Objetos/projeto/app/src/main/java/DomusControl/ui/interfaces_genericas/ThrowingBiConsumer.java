package DomusControl.ui.interfaces_genericas;

import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface ThrowingBiConsumer<T, U> {
    void accept(T t, U u) throws DomusControlException;
}
