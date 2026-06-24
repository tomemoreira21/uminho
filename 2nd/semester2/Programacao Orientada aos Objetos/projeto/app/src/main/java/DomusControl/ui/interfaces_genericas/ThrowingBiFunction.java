package DomusControl.ui.interfaces_genericas;

import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface ThrowingBiFunction<T, U, R> {
    R apply(T t, U u) throws DomusControlException;
}