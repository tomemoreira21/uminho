public class Futebol {
    private String nomeVisitado;
    private String nomeVisitante;
    private Estado estado;
    private int golosVisitado;
    private int golosVisitante;

    public enum Estado {
        PorIniciar,Decorrer,Terminado
    }

    public Futebol (String nome1,String nome2,Estado e,int golos1,int golos2) {
        this.nomeVisitado = nome1;
        this.nomeVisitante = nome2;
        this.estado = e;
        this.golosVisitado = golos1;
        this.golosVisitante = golos2;
    }

    public Futebol() {
        this.nomeVisitado = "";
        this.nomeVisitante = "";
        this.estado = Estado.PorIniciar;
        this.golosVisitado = 0;
        this.golosVisitante = 0;
    }

    public Futebol(Futebol f) {
        this.nomeVisitado = f.getNomeVisitado();
        this.nomeVisitante = f.getNomeVisitante();
        this.estado = f.getEstado();
        this.golosVisitado = f.getGolosVisitado();
        this.golosVisitante = f.getGolosVisitante();
    }

    public String getNomeVisitado() {
        return nomeVisitado;
    }

    public void setNomeVisitado(String nomeVisitado) {
        this.nomeVisitado = nomeVisitado;
    }

    public String getNomeVisitante() {
        return nomeVisitante;
    }

    public void setNomeVisitante(String nomeVisitante) {
        this.nomeVisitante = nomeVisitante;
    }

    public Estado getEstado() {
        return estado;
    }

    public void setEstado(Estado estado) {
        this.estado = estado;
    }

    public int getGolosVisitado() {
        return golosVisitado;
    }

    public void setGolosVisitado(int golosVisitado) {
        this.golosVisitado = golosVisitado;
    }

    public int getGolosVisitante() {
        return golosVisitante;
    }

    public void setGolosVisitante(int golosVisitante) {
        this.golosVisitante = golosVisitante;
    }

    public void startGame() {
        this.estado = Estado.Decorrer;   
    }

    public void endGame() {
        this.estado = Estado.Terminado;
    }

    public void goloVisitado() {
        if (this.estado == Estado.Decorrer) 
            (this.golosVisitado)++;
    }

    public void goloVisitante() {
        if (this.estado == Estado.Decorrer)
            (this.golosVisitante)++;
    }

    public String resultadoActual() {
        return this.nomeVisitado + " " + this.golosVisitado + " x " + this.golosVisitante + " " + this.nomeVisitante;
    }
}