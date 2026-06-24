import java.util.*;
import java.util.stream.Collectors;

public class TurmaAlunos implements Comparable<TurmaAlunos> {
    private Map<String,Aluno> turma;
    private String nomeTurma;
    private String cUC;

    public TurmaAlunos (Map<String,Aluno> t,String nome,String codigo) {
        this.setTurma(t);
        this.nomeTurma = nome;
        this.cUC = codigo;
    }

    public TurmaAlunos() {
        this.turma = new HashMap<String,Aluno>();
        this.nomeTurma = "";
        this.cUC = "";
    }

    public TurmaAlunos(TurmaAlunos tA) {
        this.turma = tA.getTurma();
        this.nomeTurma = tA.getNomeTurma();
        this.cUC = tA.getcUC();
    }

    public Map<String,Aluno> getTurma() {
        Map<String,Aluno> ts = new HashMap<String,Aluno>();

        for (Map.Entry<String,Aluno> t : this.turma.entrySet()) {
            ts.put(t.getKey(),t.getValue().clone());
        }

        return ts;
    }

    public void setTurma (Map<String,Aluno> turma) {
        Map<String,Aluno> ts = new HashMap<String,Aluno>();

        for (Map.Entry<String,Aluno> t : turma.entrySet()) {
            ts.put(t.getKey(),t.getValue().clone());
        }

        this.turma = ts;
    }


    public String getNomeTurma() {
        return nomeTurma;
    }


    public void setNomeTurma(String nomeTurma) {
        this.nomeTurma = nomeTurma;
    }


    public String getcUC() {
        return cUC;
    }


    public void setcUC(String cUC) {
        this.cUC = cUC;
    }

    public TurmaAlunos clone() {
        return new TurmaAlunos(this);
    }
    
    public String toString() {
        String out = "";
        out += ("Nome: " + this.nomeTurma + ", Código UC: " + this.cUC + "\n");

        for (Map.Entry<String,Aluno> t : this.turma.entrySet()) {
            out += (t.getKey().toString() + " -> " + t.getValue().toString() + "\n");
        }

        return out;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        TurmaAlunos tA = (TurmaAlunos) o;
        return tA.getNomeTurma().equals(this.nomeTurma) &&
               tA.getcUC().equals(this.cUC) &&
               tA.getTurma().equals(this.turma);
    }

    @Override
    public int compareTo(TurmaAlunos tA) {
        return this.turma.size() - tA.getTurma().size();
    }

    public void insereAluno(Aluno a) {
        this.turma.put(a.getNumero(),a.clone());
    }

    public Aluno getAluno(String codAluno) {
        return this.turma.get(codAluno).clone();
    }

    public void removeAluno(String codAluno) {
        this.turma.remove(codAluno);
    }

    public Set<String> todosOsCodigos() {
        return this.turma.keySet();
    }

    public int qtsAlunos() {
        return this.turma.size();
    }

    public Collection<Aluno> alunosOrdemAlfabetica() {
        TreeSet<Aluno> alunosOrdenados = new TreeSet<Aluno>((a1,a2) -> a1.getNome().compareTo(a2.getNome())); // ordenado de forma alfabetica

        Collection<Aluno> alunos = this.turma.values().stream()
                                                      .map (Aluno :: clone)
                                                      .collect(Collectors.toList());

        alunosOrdenados.addAll(alunos);

        return alunosOrdenados;
    }

    public Collection<Aluno> alunosOrdemAlfabetica_v2() {
        return this.turma.values()
                         .stream()
                         .sorted(new ComparadorOrdemAlfabetica())
                         .collect(Collectors.toCollection(TreeSet :: new));
    }

    public Set<Aluno> alunosOrdemDescrescenteNumero() {
        TreeSet<Aluno> alunosNumDesc = new TreeSet<Aluno>(new ComparadorNumDescrescente());

        Collection<Aluno> alunos = this.turma.values().stream()
                                                      .map (Aluno :: clone)
                                                      .collect(Collectors.toList());

        alunosNumDesc.addAll(alunos);

        return alunosNumDesc;
    }

    
    public Set<Aluno> alunosOrdemDescescenteNumero_v2() {
        return this.turma.values()
                         .stream()
                         .sorted(new ComparadorNumDescrescente())
                         .collect(Collectors.toSet());

    }

}   
