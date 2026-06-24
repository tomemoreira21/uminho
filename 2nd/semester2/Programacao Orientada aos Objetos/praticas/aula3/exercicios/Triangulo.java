public class Triangulo {
    private Ponto p1;
    private Ponto p2;
    private Ponto p3;

    public Triangulo (Ponto ponto1,Ponto ponto2,Ponto ponto3) {
        this.p1 = new Ponto(ponto1);
        this.p2 = new Ponto(ponto2);
        this.p3 = new Ponto(ponto3);
    }

    public Triangulo() {
        this.p1 = new Ponto();  
        this.p2 = new Ponto();
        this.p3 = new Ponto();
    }

    public Triangulo(Triangulo t) {
        this.p1 = t.getPontoP1();
        this.p2 = t.getPontoP2();
        this.p3 = t.getPontoP3();
    }

    public Ponto getPontoP1() {
        return p1.clone();
    }

    public void setPontoP1(Ponto p1) {
        this.p1 = p1;
    }

    public Ponto getPontoP2() {
        return p2.clone();
    }

    public void setPontoP2(Ponto p2) {
        this.p2 = p2;
    }

    public Ponto getPontoP3() {
        return p3.clone();
    }

    public void setPontoP3(Ponto p3) {
        this.p3 = p3;
    }

    public double calculaAreaTriangulo() {
        return 0.5 * Math.abs(
                    (this.getPontoP1().getCoordX() * (this.getPontoP2().getCoordY() - this.getPontoP3().getCoordY()) + 
                     this.getPontoP2().getCoordX() * (this.getPontoP3().getCoordY() - this.getPontoP1().getCoordY()) + 
                     this.getPontoP3().getCoordX() * (this.getPontoP1().getCoordY() - this.getPontoP2().getCoordY()))
        );
    }

    public double calculaPerimetroTriangulo() {
        return (Math.sqrt(Math.pow(this.getPontoP1().getCoordX() - this.getPontoP2().getCoordX(),2) + Math.pow(this.getPontoP1().getCoordY() - this.getPontoP2().getCoordY(),2))) + 
            (Math.sqrt(Math.pow(this.getPontoP2().getCoordX() - this.getPontoP3().getCoordX(),2) + Math.pow(this.getPontoP2().getCoordY() - this.getPontoP3().getCoordY(),2))) +
            (Math.sqrt(Math.pow(this.getPontoP1().getCoordX() - this.getPontoP3().getCoordX(),2) + Math.pow(this.getPontoP1().getCoordY() - this.getPontoP3().getCoordY(),2)));
    }

    public double calculaAltura() {
        double menorY = Math.min(Math.min(this.getPontoP1().getCoordY(),this.getPontoP2().getCoordY()),this.getPontoP3().getCoordY());
        double maiorY = Math.max(Math.max(this.getPontoP1().getCoordY(),this.getPontoP2().getCoordY()),this.getPontoP3().getCoordY());

        return maiorY - menorY;
    }

    public Triangulo clone() {
        return new Triangulo(this);
    }

    public String toString() {
        return "p1 = " + this.p1.toString() + ", p2 = " + this.p2.toString() + ", p3 = " + this.p3.toString();
    }

}
