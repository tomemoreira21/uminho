package DomusControl.automation.actions.onoff.sensor;

import DomusControl.automation.core.AcaoSimples;
import DomusControl.device.DispositivoMedicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.home.Casa;

public class AlterarValorMedido implements AcaoSimples {
    private String idDispositivo;
    private double valor;

    public AlterarValorMedido(String idDisposiitivo, double valor) {
        this.idDispositivo = idDisposiitivo;
        this.valor = valor;
    }

    public String getIdDispositivo() {
        return idDispositivo;
    }

    public double getValor() {
        return valor;
    }

    @Override
    public void executar(Casa casa) throws DomusControlException {
        casa.executarSobreDispositivo(idDispositivo, 
            d -> {
                if (!(d instanceof DispositivoMedicao disp)) {
                    throw new TipoDispositivoInvalidoException(idDispositivo);
                }
                
                disp.setValor(valor);
            }
        );
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AlterarValorMedido a = (AlterarValorMedido)o;
        return a.getIdDispositivo().equals(this.idDispositivo) &&
               Double.compare(a.getValor(), this.valor) == 0;
    }

    public String toString() {
         return "Alterar valor medido do " + this.idDispositivo + "para " + this.valor;
    }
}
