package DomusControl.device;

import DomusControl.exceptions.DomusControlException;

public abstract class DispositivoMedicao extends DispositivoOnOff {
    private double valor;
    private SensorObserver observer;

    public DispositivoMedicao(String id,String marca,String modelo,double consumoPorHora) {
        super(id,marca,modelo,consumoPorHora);
        this.valor = 0.0;
    }

    public DispositivoMedicao() {
        super();
        this.valor = 0.0;
    }

    public DispositivoMedicao(DispositivoMedicao s) {
        super(s);
        this.valor = s.getValor();
    }

    public double getValor() {
        return this.valor;
    }

    public void setValor(double valor) throws DomusControlException {
        this.valor = valor;

        // notifica as alterações no valor medido
        if (observer != null) {
            observer.valorAlterado(getId());
        }
    }

    public SensorObserver getObserver() {
        return observer;
    }

    public void setObserver(SensorObserver observer) {
        this.observer = observer;
    }

    public abstract DispositivoMedicao clone();

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        DispositivoMedicao d = (DispositivoMedicao) o;
        return super.equals(o) &&
               Double.compare(d.getValor(), this.valor) == 0;
    }

    @Override
    public String toString() {
        return super.toString() + ", valor = " + this.valor;
    }

    @Override
     public int hashCode() {
        return super.hashCode() * 31 + Double.hashCode(this.valor);
    }

}
