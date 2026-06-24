import java.util.Comparator;

public class ComparadorNumDescrescente implements Comparator<Aluno> {
    @Override
    public int compare(Aluno a1,Aluno a2) {
        return a2.getNumero().compareTo(a1.getNumero());
    }

}
