package DomusControl.automation.interfaces_genericas;

import java.io.Serializable;
import java.util.function.Function;

import DomusControl.automation.core.Acao;
import DomusControl.device.Dispositivo;

@FunctionalInterface
public interface FactoryAcao extends Function<Dispositivo,Acao>, Serializable {}
