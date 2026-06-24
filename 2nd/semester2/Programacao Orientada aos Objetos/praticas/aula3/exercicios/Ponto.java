public class Ponto {
    private double coordX;
    private double coordY;

    public Ponto (double x,double y) {
        this.coordX = x;
        this.coordY = y;
    }

    public Ponto (Ponto umPonto) {
        this.coordX = umPonto.getCoordX();
        this.coordY = umPonto.getCoordY();
    }
    
    public Ponto() {
        this.coordX = 0;
        this.coordY = 0;
    }

    public double getCoordX() {
        return coordX;
    }

    public void setCoordX(double coordX) {
        this.coordX = coordX;
    }

    public double getCoordY() {
        return coordY;
    }

    public void setCoordY(double coordY) {
        this.coordY = coordY;
    }

    public Ponto clone() {
        return new Ponto(this);
    }

    public String toString() {
        return "(" + this.coordX + "," + this.coordY + ")"; 
    }
}
