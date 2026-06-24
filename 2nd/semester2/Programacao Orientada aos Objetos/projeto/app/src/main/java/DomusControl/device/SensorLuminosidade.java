package DomusControl.device;

public class SensorLuminosidade extends DispositivoMedicao {

     public SensorLuminosidade(String id,String marca,String modelo,double consumoPorHora) {
        super(id,marca,modelo,consumoPorHora);
    }

    public SensorLuminosidade() {
        super();
    }

    public SensorLuminosidade(SensorLuminosidade s) {
        super(s);
    }

    @Override
    public SensorLuminosidade clone() {
        return new SensorLuminosidade(this);
    }
}
