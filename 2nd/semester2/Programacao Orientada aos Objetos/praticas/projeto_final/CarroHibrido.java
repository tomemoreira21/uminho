
public class CarroHibrido extends CarroCombustao implements iCarroEletrico {
    private double dimensaoBateria;
    private double consumoKWh100Km;
    private double precoKWh;

    private double pontosPorKm = 2.0;

    public CarroHibrido(String id, String marca, String modelo, int ano,
                        double vMedia, double autonomia, double numeroKms, double totaisKm,
                        double tamanhoDeposito, double consumoLitros100Km, double precoPorLitro,
                        double dimensaoBateria, double consumoKWh100Km, double precoKWh) {

        super(id, marca, modelo, ano, vMedia, autonomia, numeroKms, totaisKm,
              tamanhoDeposito, consumoLitros100Km, precoPorLitro);

        this.dimensaoBateria = dimensaoBateria;
        this.consumoKWh100Km = consumoKWh100Km;
        this.precoKWh = precoKWh;
    }

    public CarroHibrido() {
        super();
        this.dimensaoBateria = 1.0;
        this.consumoKWh100Km = 1.0;
        this.precoKWh = 1.0;
    }

    public CarroHibrido(CarroHibrido umCarro) {
        super(umCarro);
        this.dimensaoBateria = umCarro.getDimensaoBateria();
        this.consumoKWh100Km = umCarro.getConsumoKWh100Km();
        this.precoKWh = umCarro.getPrecoKWh();
    }

    public double getDimensaoBateria() {
        return dimensaoBateria;
    }

    public void setDimensaoBateria(double dimensaoBateria) {
        this.dimensaoBateria = dimensaoBateria;
    }

    public double getConsumoKWh100Km() {
        return consumoKWh100Km;
    }

    public void setConsumoKWh100Km(double consumoKWh100Km) {
        this.consumoKWh100Km = consumoKWh100Km;
    }

    public double getPrecoKWh() {
        return precoKWh;
    }

    public void setPrecoKWh(double precoKWh) {
        this.precoKWh = precoKWh;
    }

    public double getPontosPorKm() {
        return pontosPorKm;
    }

    public void setPontosPorKm(double pontosPorKm) {
        this.pontosPorKm = pontosPorKm;
    }

    public double custoPorKm() {
        double custoEletrico = (this.consumoKWh100Km / 100.0) * this.precoKWh;
        double custoCombustao = super.custoPorKm();

        return custoEletrico + custoCombustao;
    }

    public void atestar() {
        super.atestar(); // combustível

        double autonomiaEletrica = (this.dimensaoBateria / this.consumoKWh100Km) * 100;
        this.setAutonomia(this.getAutonomia() + autonomiaEletrica);
    }
    
    public double getNivelBateria() {
        if (this.consumoKWh100Km == 0) return 0.0;

        double autonomiaMax = (this.dimensaoBateria / this.consumoKWh100Km) * 100.0;
        return (this.getAutonomia() / autonomiaMax) * 100.0;
    }

    public double totalPontos() {
        return super.getTotaisKm() * this.pontosPorKm;
    }

    public CarroHibrido clone() {
        return new CarroHibrido(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CarroHibrido c = (CarroHibrido) o;
        return super.equals(c) &&
               Double.compare(c.getDimensaoBateria(), this.dimensaoBateria) == 0 &&
               Double.compare(c.getConsumoKWh100Km(), this.consumoKWh100Km) == 0 &&
               Double.compare(c.getPrecoKWh(), this.precoKWh) == 0;
    }

    public String toString() {
        return super.toString() + ", dimensaoBateria = " + this.dimensaoBateria + ", consumoKWh100km = " + this.consumoKWh100Km
        + ", precoKWh = " + this.precoKWh;
    }
}

