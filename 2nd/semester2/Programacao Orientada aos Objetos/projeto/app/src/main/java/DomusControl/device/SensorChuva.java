package DomusControl.device;

public class SensorChuva extends DispositivoMedicao {

    public SensorChuva(String id,String marca,String modelo,double consumoPorHora) {
        super(id,marca,modelo,consumoPorHora);
    }

    public SensorChuva() {
        super();
    }

    public SensorChuva(SensorChuva s) {
        super(s);
    }

    @Override
    public SensorChuva clone() {
        return new SensorChuva(this);
    }
}
