package DomusControl.device;

public class Rele extends DispositivoOnOff {
    
    public Rele(String id,String marca,String modelo,double consumoPorHora) {
        super(id, marca, modelo, consumoPorHora);
    }

    public Rele() {
        super();
    }

    public Rele(Rele r) {
        super(r);
    }

    @Override
    public Rele clone() {
        return new Rele(this);
    }

}
