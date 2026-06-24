public class Sensor {
    private double valor;

    public Sensor() {
        this.valor = 0;
    }

    public Sensor(double valor) {
        if (valor >= 0) 
            this.valor = valor;
        else 
            this.valor = 0;
    }

    public Sensor(Sensor s) {
        this.valor = s.getPressao();
    }

    public boolean setPressao(double valor) {
        if (valor >= 0) {
            this.valor = valor;
            return true;
        }

        return false;
    }

    public double getPressao() {
        return this.valor;
    }
}   
