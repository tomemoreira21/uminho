import java.util.Objects;

public class Aluno {
    private String numero;
    private int nota;
    private String nome;
    private String curso;

    public Aluno(String numero, int nota, String nome, String curso) {
        this.numero = numero;
        this.nota = nota;
        this.nome = nome;
        this.curso = curso;
    }

    public Aluno() {
        this.numero = "";
        this.nota = 0;
        this.nome = "";
        this.curso = "";
    }

    public Aluno(Aluno a) {
        this.numero = a.getNumero();
        this.nota = a.getNota();
        this.nome = a.getNome();
        this.curso = a.getCurso();
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    public int getNota() {
        return nota;
    }

    public void setNota(int nota) {
        this.nota = nota;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCurso() {
        return curso;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    public Aluno clone() {
        return new Aluno(this);
    }

    public String toString() {
        return "Nª: " + this.numero + ", Nota: " + this.nota + ", Nome: " + this.nome + 
                ", Curso: " + this.curso; 
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass())) 
            return false;

        Aluno a = (Aluno) o;
        return a.getNumero().equals(this.numero) &&
               a.getNota() == this.nota &&
               a.getNome().equals(this.nome) &&
               a.getCurso().equals(this.curso);
    }

    public int hashcode() {
        return Objects.hash(this.numero,this.nota,this.nome,this.curso);
    }
}
