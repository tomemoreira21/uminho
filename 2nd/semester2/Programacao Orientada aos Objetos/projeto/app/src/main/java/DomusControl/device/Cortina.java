package DomusControl.device;

public class Cortina extends DispositivoAbertura {

    public Cortina(String id,String marca,String modelo,double consumoPorHora, double tempoAberturaHoras) {
        super(id,marca,modelo,consumoPorHora,tempoAberturaHoras); 
    }
    
    public Cortina() {
        super();
    }

    public Cortina(Cortina c) {
        super(c);
    }

    @Override
    public Cortina clone() {
        return new Cortina(this);
    }
}
