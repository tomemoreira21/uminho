import java.util.Objects;

public class Lugar {
    private String matricula;
    private String nome;
    private int minutos;
    private boolean permanente;

    public Lugar(String matricula, String nome, int minutos, boolean permanente) {
        this.matricula = matricula;
        this.nome = nome;
        this.minutos = minutos;
        this.permanente = permanente;
    }

    public Lugar() {
        this.matricula = "";
        this.nome = "";
        this.minutos = 0;
        this.permanente = false;
    }

    public Lugar(Lugar l) {
        this.matricula = l.getMatricula();
        this.nome = l.getNome();
        this.minutos = l.getMinutos();
        this.permanente = l.isPermanente();
    }

    public String getMatricula() {
        return matricula;
    }

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getMinutos() {
        return minutos;
    }

    public void setMinutos(int minutos) {
        this.minutos = minutos;
    }

    public boolean isPermanente() {
        return permanente;
    }

    public void setPermanente(boolean permanente) {
        this.permanente = permanente;
    }    

    public Lugar clone() {
        return new Lugar(this);
    }

    public String toString() {
        return "matricula = " + this.matricula + ", nome = " + this.nome + 
                ", minutos = " + this.minutos + ", permanente = " + this.permanente;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Lugar l = (Lugar) o;
        return l.getMatricula().equals(this.matricula) && 
               l.getNome().equals(this.nome) &&
               l.getMinutos() == this.minutos && 
               l.isPermanente() == this.permanente;
    }

    public int hashcode() {
        return Objects.hash(this.matricula,this.nome,this.minutos,this.permanente);
    }


}