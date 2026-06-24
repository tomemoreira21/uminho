public class TesteTurmaAlunos {
    public static void main(String[] args) {
        // Criar alguns alunos
        Aluno a1 = new Aluno("A1", 19,"Joao","LEI");
        Aluno a2 = new Aluno("A2", 18,"Maria","LEI");
        Aluno a3 = new Aluno("A3", 15,"Antonio","LEI");

        // Criar turma
        TurmaAlunos turma = new TurmaAlunos();
        turma.setNomeTurma("LEI");
        turma.setcUC("POO");

        // Inserir alunos
        turma.insereAluno(a1);
        turma.insereAluno(a2);
        turma.insereAluno(a3);

        // Mostrar turma
        System.out.println("=== TURMA ===");
        System.out.println(turma);

        // Testar número de alunos
        System.out.println("Total alunos: " + turma.qtsAlunos());

        // Testar códigos
        System.out.println("Codigos: " + turma.todosOsCodigos());

        // Testar getAluno
        System.out.println("Aluno A1: " + turma.getAluno("A1"));

        // Testar ordem alfabética
        System.out.println("=== Ordem Alfabética ===");
        System.out.println(turma.alunosOrdemAlfabetica());

        // Testar ordem número descendente
        System.out.println("=== Ordem Número Descrescente ===");
        System.out.println(turma.alunosOrdemDescrescenteNumero());

        // Testar remove
        turma.removeAluno("A2");
        System.out.println("Depois de remover A2:");
        System.out.println(turma);

        // Testar clone
        TurmaAlunos copia = turma.clone();
        System.out.println("=== Cópia ===");
        System.out.println(copia);

        // Testar equals
        System.out.println("Turma == Cópia? " + turma.equals(copia));

        // Testar compareTo
        TurmaAlunos outra = new TurmaAlunos();
        outra.setNomeTurma("MEI");
        outra.setcUC("EDA");

        outra.insereAluno(new Aluno("B1", 14,"Ana","LEI"));

        System.out.println("CompareTo (turma vs outra): " + turma.compareTo(outra));
    }
}
