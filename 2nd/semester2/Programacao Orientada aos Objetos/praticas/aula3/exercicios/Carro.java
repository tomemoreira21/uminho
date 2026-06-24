public class Carro {
    private String marca;
    private String modelo;
    private int ano;
    private double consumoPorKm;
    private double distanciaTotalKm;
    private double mediaConsumoInicio;
    private double distanciaUltimaKm;
    private double energiaTotalConsumida;
    private double mediaConsumoUltima;
    private double consumoRecuperado; // Travar durante 1 km permite recuperar X kWh
    private Estado estado;

    public enum Estado {ON,OFF};

    public Carro(String marca, String modelo, int ano, double consumoPorKm, double distanciaTotalKm,
            double mediaConsumoInicio, double distanciaUltimaKm, double energiaTotalConsumida, double mediaConsumoUltima, double consumoRecuperado, Estado e) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.consumoPorKm = consumoPorKm;
        this.distanciaTotalKm = distanciaTotalKm;
        this.mediaConsumoInicio = mediaConsumoInicio;
        this.distanciaUltimaKm = distanciaUltimaKm;
        this.energiaTotalConsumida = energiaTotalConsumida;
        this.mediaConsumoUltima = mediaConsumoUltima;
        this.consumoRecuperado = consumoRecuperado;
        this.estado = e;
    }

    public Carro() {
        this.marca = "";
        this.modelo = "";
        this.ano = 2026;
        this.consumoPorKm = 10;
        this.distanciaTotalKm = 10;
        this.mediaConsumoInicio = 10;
        this.energiaTotalConsumida = 10;
        this.distanciaUltimaKm = 0;
        this.mediaConsumoUltima = 0;
        this.consumoRecuperado = 1;
        this.estado = Estado.OFF;
    }

    public Carro(Carro c) {
        this.marca = c.getMarca();
        this.modelo = c.getModelo();
        this.ano = c.getAno();
        this.consumoPorKm = c.getConsumoPorKm();
        this.distanciaTotalKm = c.getDistanciaTotalKm();
        this.mediaConsumoInicio = c.getMediaConsumoInicio();
        this.distanciaUltimaKm = c.getDistanciaUltimaKm();
        this.mediaConsumoUltima = c.getMediaConsumoUltima();
        this.energiaTotalConsumida = c.getEnergiaTotalConsumida();
        this.consumoRecuperado = c.getConsumoRecuperado();
        this.estado = c.getEstado();
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public Estado getEstado() {
        return estado;
    }

    public void setEstado(Estado estado) {
        this.estado = estado;
    }

    public String getModelo() {
        return modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public double getEnergiaTotalConsumida() {
        return energiaTotalConsumida;
    }

    public void setEnergiaTotalConsumida(double energiaTotalConsumida) {
        this.energiaTotalConsumida = energiaTotalConsumida;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }
    
    public double getConsumoPorKm() {
        return consumoPorKm;
    }

    public void setConsumoPorKm(double consumoPorKm) {
        this.consumoPorKm = consumoPorKm;
    }

    public double getDistanciaTotalKm() {
        return distanciaTotalKm;
    }

    public void setDistanciaTotalKm(double distanciaTotalKm) {
        this.distanciaTotalKm = distanciaTotalKm;
    }

    public double getMediaConsumoInicio() {
        return mediaConsumoInicio;
    }

    public void setMediaConsumoInicio(double mediaConsumoInicio) {
        this.mediaConsumoInicio = mediaConsumoInicio;
    }

    public double getDistanciaUltimaKm() {
        return distanciaUltimaKm;
    }

    public void setDistanciaUltimaKm(double distanciaUltimaKm) {
        this.distanciaUltimaKm = distanciaUltimaKm;
    }

    public double getMediaConsumoUltima() {
        return mediaConsumoUltima;
    }

    public void setMediaConsumoUltima(double mediaConsumoUltima) {
        this.mediaConsumoUltima = mediaConsumoUltima;
    }

    public double getConsumoRecuperado() {
        return consumoRecuperado;
    }

    public void setConsumoRecuperado(double consumoRecuperado) {
        this.consumoRecuperado = consumoRecuperado;
    }

    public void ligaCarro() {
        this.estado = Estado.ON;
    }

    public void desligaCarro() {
        this.estado = Estado.OFF;
    }

    public void resetUltimaViagem() {
        this.distanciaUltimaKm = 0;
        this.mediaConsumoUltima = 0;
    }

    public void avancaCarro(double metros,double velocidade) {
        double distKm = metros/1000;
        double consumoPorKmReal = this.consumoPorKm * (velocidade / 100);
        double consumoPercurso = consumoPorKmReal * distKm;    

        this.distanciaTotalKm += distKm;
        this.energiaTotalConsumida += consumoPercurso;
        this.distanciaUltimaKm = distKm;

        this.mediaConsumoUltima = consumoPercurso / distKm;
        this.mediaConsumoInicio = this.energiaTotalConsumida / this.distanciaTotalKm;
    }

    public void travaCarro(double metros) {
        double distKm = metros/1000;
        double energiaPoupada = distKm * this.consumoRecuperado;    

        this.energiaTotalConsumida -= energiaPoupada;
        this.mediaConsumoInicio = this.energiaTotalConsumida / this.distanciaTotalKm;
    }

}
