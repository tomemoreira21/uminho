public class LampadaLed extends Lampada {
    private int potencia;
    private int lumens;

    public LampadaLed(String id,int potencia,int lumens) {
        super(id,1 /potencia,1.25/potencia);
        this.lumens = lumens;
    }

    public LampadaLed() {
        super();
        this.potencia = 10;
        this.lumens = 10;
    }

    public LampadaLed(LampadaLed led) {
        super(led);
        this.potencia = led.getPotencia();
        this.lumens = led.getLumens();
    }

    public int getPotencia() {
        return potencia;
    }

    public void setPotencia(int potencia) {
        this.potencia = potencia;
    }

    public int getLumens() {
        return lumens;
    }

    public void setLumens(int lumens) {
        this.lumens = lumens;
    }

    @Override
    public LampadaLed clone() {
        return new LampadaLed(this);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        LampadaLed l = (LampadaLed) o;
        return super.equals(o) && 
               l.getPotencia() == this.potencia &&
               l.getLumens() == this.lumens;
    }

    @Override 
    public String toString() {
        return super.toString() + ", Potencia = " + this.potencia + ", Intensidade = " + this.lumens;
    }

}
