import java.io.Serializable;

public abstract class Carro implements DadosCarro,Serializable {
    private String id;
    private String marca;
    private String modelo;
    private int ano;
    private double vMedia;
    private double autonomia;
    private double numeroKms; // contador parcial de kms
    private double totaisKm;

    public Carro(String id, String marca, String modelo, int ano, double vMedia, double autonomia, double numeroKms, double totaisKm) {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.vMedia = vMedia;
        this.autonomia = autonomia;
        this.numeroKms = numeroKms;
        this.totaisKm = totaisKm;
    }

    public Carro() {
        this.id = "";
        this.marca = "";
        this.modelo = "";
        this.ano = 2020;
        this.vMedia = 100;
        this.autonomia = 200;
        this.numeroKms = 0;
        this.totaisKm = 0;
    }

    public Carro (Carro c) {
        this.id = c.getId();
        this.marca = c.getMarca();
        this.modelo = c.getModelo();
        this.ano = c.getAno();
        this.vMedia = c.getvMedia();
        this.autonomia = c.getAutonomia();
        this.numeroKms = c.getNumeroKms();
        this.totaisKm = c.getTotaisKm();
    }

    public double getTotaisKm() {
        return totaisKm;
    }

    public void setTotaisKm(double totaisKm) {
        this.totaisKm = totaisKm;
    }

    public double getNumeroKms() {
        return numeroKms;
    }

    public void setNumeroKms(double numeroKms) {
        this.numeroKms = numeroKms;
    }

    public double getAutonomia() {
        return autonomia;
    }

    public void setAutonomia(double autonomia) {
        this.autonomia = autonomia;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getModelo() {
        return modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public double getvMedia() {
        return vMedia;
    }

    public void setvMedia(double vMedia) {
        this.vMedia = vMedia;
    }   

    public void atestar() {
        this.numeroKms = 0;
    }

    public double custoPorKmReal() {
        return 1.15 * this.custoPorKm();
    }

    public void registarViagem(int kms) {
        if (kms >= 0 && kms <= autonomia) {
            this.autonomia -= kms;
            this.numeroKms += kms;
            this.totaisKm += kms;
        }
    }

    public abstract double custoPorKm();
    public abstract Carro clone();
    
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Carro c = (Carro) o;
        return c.getId().equals(this.id) &&
               c.getMarca().equals(this.marca) &&
               c.getModelo().equals(this.modelo) &&
               c.getAno() == this.ano &&
               Double.compare(c.getAutonomia(), this.autonomia) == 0 &&
               Double.compare(c.getvMedia(), this.vMedia) == 0 &&
               Double.compare(c.getNumeroKms(), this.numeroKms) == 0 &&
               Double.compare(c.getTotaisKm(), this.totaisKm) == 0;
    }

    public String toString() {
        return "id = " + this.id + ", marca = " + this.marca + ", modelo = " + this.modelo + 
               ", ano = " + this.ano + ", vMedia = " + this.vMedia + ", autonomia = " + this.autonomia + 
               ", totaisKm = " + this.totaisKm;
    }

}
