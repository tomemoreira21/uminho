public class Lampada {
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

    public Lampada(double cOn,double cEco) {
        this.consumoOn = cOn;
        this.consumoEco = cEco;
        this.estado = Estado.OFF;
        this.update = System.currentTimeMillis();
        this.custoTotal = 0;
    }

    public Lampada() {
        this.consumoOn = 2;
        this.consumoEco = 1;
        this.estado = Estado.OFF;
        this.update = System.currentTimeMillis();
        this.custoTotal = 0;
    }

    public Lampada(Lampada l) {
        this.consumoOn = l.getConsumoOn();
        this.consumoEco = l.getConsumoEco();
        this.estado = l.getEstado();
        this.update = l.getUpdate();
        this.custoTotal = l.getCustoTotal();
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

}
