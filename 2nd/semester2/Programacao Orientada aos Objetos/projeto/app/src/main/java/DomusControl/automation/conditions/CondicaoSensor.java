package DomusControl.automation.conditions;

import DomusControl.automation.core.Condicao;

public interface CondicaoSensor extends Condicao {
    public String getIdDispositivo(); // devolve o ID do sensor
}