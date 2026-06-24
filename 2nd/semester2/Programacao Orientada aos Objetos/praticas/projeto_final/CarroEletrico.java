public class CarroEletrico extends Carro implements Comparable<CarroEletrico>,PontosPorKms {
    private double dimensaoBateria;
    private double consumoKWh100Km;
    private double precoKWh;

    private double pontosPorKm = 2.5;

    public CarroEletrico(String id, String marca, String modelo, int ano, double vMedia, double autonomia,
            double numeroKms, double totaisKm, double dimensaoBateria, double consumoKWh100Km, double precoKWh) {
        super(id, marca, modelo, ano, vMedia, autonomia, numeroKms, totaisKm);
        this.dimensaoBateria = dimensaoBateria;
        this.consumoKWh100Km = consumoKWh100Km;
        this.precoKWh = precoKWh;
    }

    public CarroEletrico() {
        super();
        this.dimensaoBateria = 100;
        this.consumoKWh100Km = 2;
        this.precoKWh = 1;
    }

    public CarroEletrico(CarroEletrico c) {
        super(c);
        this.dimensaoBateria = c.getDimensaoBateria();
        this.consumoKWh100Km = c.getConsumoKWh();
        this.precoKWh = c.getPrecoKW(); 
    }

    public double getDimensaoBateria() {
        return dimensaoBateria;
    }

    public void setDimensaoBateria(double dimensaoBateria) {
        this.dimensaoBateria = dimensaoBateria;
    }

    public double getConsumoKWh() {
        return consumoKWh100Km;
    }

    public void setConsumoKWh(double consumoKWh) {
        this.consumoKWh100Km = consumoKWh;
    }

    public double getPrecoKW() {
        return precoKWh;
    }
    
    public void setPrecoKW(double precoKW) {
        this.precoKWh = precoKW;
    }

    public double getPontosPorKm() {
        return pontosPorKm;
    }

    public void setPontosPorKm(double pontosPorKm) {
        this.pontosPorKm = pontosPorKm;
    }

    public double custoPorKm() {
        return (this.consumoKWh100Km / 100.0) * this.precoKWh;
    }

    public void atestar() {
        super.atestar();
        double autonomia = (this.dimensaoBateria / this.consumoKWh100Km) * 100;
        this.setAutonomia(autonomia);
    }

    public double getNivelBateria() {
        if (this.consumoKWh100Km == 0) return 0.0;

        double autonomiaMax = (this.dimensaoBateria / this.consumoKWh100Km) * 100.0;
        return (this.getAutonomia() / autonomiaMax) * 100.0;
    }

    public double totalPontos() {
        return super.getTotaisKm() * this.pontosPorKm;
    }

    @Override
    public int compareTo(CarroEletrico outro) {
        int res = Double.compare(this.getTotaisKm(), outro.getTotaisKm());

        if (res == 0) {
            res = Double.compare(outro.getDimensaoBateria(), this.getDimensaoBateria());
        }

        return res;
    }


    public CarroEletrico clone() {
        return new CarroEletrico(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CarroEletrico c = (CarroEletrico) o;
        return super.equals(c) &&
               Double.compare(c.getDimensaoBateria(), this.dimensaoBateria) == 0 &&
               Double.compare(c.getConsumoKWh(), this.consumoKWh100Km) == 0 &&
               Double.compare(c.getPrecoKW(), this.precoKWh) == 0;
    }
    
    public String toString() {
        return super.toString() + ", dimensao = " + this.dimensaoBateria + 
        ", consumoKWh100km = " + this.consumoKWh100Km + ", precoKwh = " + this.precoKWh;
    }
    

}
