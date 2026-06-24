public class CarroCombustao extends Carro implements PontosPorKms {
    private double tamanhoDeposito;
    private double consumoLitros100Km;
    private double precoPorLitro;

    private double pontosPorKm = 1;

    public CarroCombustao(String id, String marca, String modelo, int ano, double vMedia, double autonomia,
            double numeroKms,double totaisKm, double tamanhoDeposito, double consumoLitros100Km, double precoPorLitro) {
        super(id, marca, modelo, ano, vMedia, autonomia, numeroKms, totaisKm);
        this.tamanhoDeposito = tamanhoDeposito;
        this.consumoLitros100Km = consumoLitros100Km;
        this.precoPorLitro = precoPorLitro;
    }

    public CarroCombustao() {
        super();
        this.tamanhoDeposito = 100;
        this.consumoLitros100Km = 2;
        this.precoPorLitro = 1;
    }

    public CarroCombustao(CarroCombustao c) {
        super(c);
        this.tamanhoDeposito = c.getTamanhoDeposito();
        this.consumoLitros100Km = c.getConsumoLitros();
        this.precoPorLitro = c.getPrecoPorLitro();
    }

    public double getTamanhoDeposito() {
        return tamanhoDeposito;
    }

    public void setTamanhoDeposito(double tamanhoDeposito) {
        this.tamanhoDeposito = tamanhoDeposito;
    }

    public double getConsumoLitros() {
        return consumoLitros100Km;
    }
    
    public void setConsumoLitros(double consumoLitros) {
        this.consumoLitros100Km = consumoLitros;
    }

    public double getPrecoPorLitro() {
        return precoPorLitro;
    }

    public double getPontosPorKm() {
        return pontosPorKm;
    }

    public void setPontosPorKm(double pontosPorKm) {
        this.pontosPorKm = pontosPorKm;
    }

    public void setPrecoPorLitro(double precoPorLitro) {
        this.precoPorLitro = precoPorLitro;
    }

    public double custoPorKm() {
        return (this.consumoLitros100Km/ 100.0) * this.precoPorLitro;
    }

    public void atestar() {
        super.atestar();
        double autonomia = (this.tamanhoDeposito / this.consumoLitros100Km) * 100;
        this.setAutonomia(autonomia);
    }

      public double totalPontos() {
        return super.getTotaisKm() * this.pontosPorKm;
    }

    public CarroCombustao clone() {
        return new CarroCombustao(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CarroCombustao c = (CarroCombustao) o;
        return super.equals(c) &&
                Double.compare(c.getTamanhoDeposito(), this.tamanhoDeposito) == 0 &&
                Double.compare(c.getConsumoLitros(), this.consumoLitros100Km) == 0 &&
                Double.compare(c.getPrecoPorLitro(), this.precoPorLitro) == 0;
    }   

    public String toString() {
        return super.toString() + ", tamanhoDeposito = " + this.tamanhoDeposito + 
        ", consumoLitros100Km = " + this.consumoLitros100Km + ", precoPorLitro = " + this.precoPorLitro;
    }

}
