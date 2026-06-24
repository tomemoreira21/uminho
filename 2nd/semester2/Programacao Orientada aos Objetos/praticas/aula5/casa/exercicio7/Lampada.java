import java.util.Objects;

public class Lampada {
    private String id;
    private double consumoOn;
    private double consumoEco;
    private Estado estado;
    private long update; // está milissegundos
    private double custoTotal;   

    public enum Estado {
        ON,
        OFF,
        ECO  
    }

    public Lampada(String id,double cOn,double cEco) {
        this.id = id;
        this.consumoOn = cOn;
        this.consumoEco = cEco;
        this.estado = Estado.OFF;
        this.update = System.currentTimeMillis();
        this.custoTotal = 0;
    }

    public Lampada() {
        this.id = "";
        this.consumoOn = 2;
        this.consumoEco = 1;
        this.estado = Estado.OFF;
        this.update = System.currentTimeMillis();
        this.custoTotal = 0;
    }

    public Lampada(Lampada l) {
        this.id = l.getId();
        this.consumoOn = l.getConsumoOn();
        this.consumoEco = l.getConsumoEco();
        this.estado = l.getEstado();
        this.update = l.getUpdate();
        this.custoTotal = l.getCustoTotal();
    }

    public String getId() {
        return this.id;
    }

    public void setId(String id) {
        this.id = id;
    }
    
    public double getConsumoOn() {
        return this.consumoOn;
    }

    public long getUpdate() {
        return this.update;
    }

    public double getCustoTotal() {
        return this.custoTotal;
    }

    public void setCustoTotal(double custoTotal) {
        this.custoTotal = custoTotal;
    }

    public void setUpdate(long tempo) {
        this.update = tempo;
    }

    public void setConsumoOn(double consumoOn) {
        this.consumoOn = consumoOn;
    }

    public double getConsumoEco() {
        return this.consumoEco;
    }

    public void setConsumoEco(double consumoEco) {
        this.consumoEco = consumoEco;
    }

    public Estado getEstado() {
        return this.estado;
    }

    public void setEstado(Estado estado) {
        this.estado = estado;
    };

    public boolean onECOMode() {
        return this.estado == Estado.ECO;
    }

    public void lampON() {
        this.atualizaConsumo();
        this.estado = Estado.ON;
    }

    public void lampOFF() {
        this.atualizaConsumo();
        this.estado = Estado.OFF;
    }

    public void lampECO() {
        this.atualizaConsumo();
        this.estado = Estado.ECO;
    }

    public double totalConsumo() {
        return this.custoTotal;
    }

    private void atualizaConsumo() {
        this.custoTotal += this.periodoConsumo();
        this.update = System.currentTimeMillis();
    }

    public double periodoConsumo() {
        long diferenca = System.currentTimeMillis() - this.update;

        double valor = 0;
        
        if (this.estado == Estado.ON) {
            valor = diferenca * consumoOn;
        } else if (this.estado == Estado.ECO) {
            valor = diferenca * consumoEco;
        }

        return valor;
    }

    public Lampada clone() {
        return new Lampada(this);
    }

    public String toString() {
        return "ConsumoOn = " + this.consumoOn + ", ConsumoECO = " + this.consumoEco + ", Estado = " + this.estado.toString() + ", Custo Total = " + this.custoTotal;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Lampada l = (Lampada) o;
        return l.getId().equals(this.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }
}
