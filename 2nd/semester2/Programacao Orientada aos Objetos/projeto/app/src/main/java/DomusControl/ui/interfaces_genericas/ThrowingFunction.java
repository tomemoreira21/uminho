package DomusControl.ui.interfaces_genericas;

import DomusControl.exceptions.DomusControlException;

@FunctionalInterface
public interface ThrowingFunction<T, R> {
    R apply(T t) throws DomusControlException;
}