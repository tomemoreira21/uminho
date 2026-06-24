package DomusControl.automation.conditions;

import DomusControl.device.DispositivoMedicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.DispositivoNaoESensorException;
import DomusControl.home.Casa;

public class CondicaoComparativaSensor implements CondicaoSensor {
    private String idDispositivo;
    private double valorLimite;
    private TipoComparacao tipo;

    public CondicaoComparativaSensor(String idDispositivo, double valorLimite, TipoComparacao tipo) {
        this.idDispositivo = idDispositivo;
        this.valorLimite = valorLimite;
        this.tipo = tipo;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public double getValorLimite() {
        return valorLimite;
    }

    public TipoComparacao getTipo() {
        return tipo;
    }

    @Override
    public boolean verificar(Casa casa) throws DomusControlException {
        return casa.consultarDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof DispositivoMedicao disp)) {
                    throw new DispositivoNaoESensorException(idDispositivo);
                }

                if (tipo == TipoComparacao.MENOR) {
                    return disp.getValor() < valorLimite;
                } else {
                    return disp.getValor() > valorLimite;
                }
            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CondicaoComparativaSensor c = (CondicaoComparativaSensor)o;
        return c.getIdDispositivo().equals(this.idDispositivo) &&
               Double.compare(c.getValorLimite(), this.valorLimite) == 0 &&
               c.getTipo() == this.tipo;
    }


    public String toString() {
        return "Sensor " + idDispositivo + " " + 
        (tipo == TipoComparacao.MAIOR ? ">" : "<")
        + " " + valorLimite;
    }
}
