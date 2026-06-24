package DomusControl.device;

public class PortaoGaragem extends DispositivoAbertura {

    public PortaoGaragem(String id,String marca,String modelo,double consumoPorHora, double tempoAberturaHoras) {
        super(id,marca,modelo,consumoPorHora,tempoAberturaHoras); 
    }
    
    public PortaoGaragem() {
        super();
    }

    public PortaoGaragem(PortaoGaragem p) {
        super(p);
    }

    @Override
    public PortaoGaragem clone() {
        return new PortaoGaragem(this);
    }
}
