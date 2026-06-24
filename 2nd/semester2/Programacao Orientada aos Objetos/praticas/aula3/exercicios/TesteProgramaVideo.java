import java.time.LocalDateTime;

public class TesteProgramaVideo {
    public static void main(String[] args) {
        // Criar um array de bytes simulando o conteúdo do vídeo
        byte[] conteudoTeste = {10, 20, 30, 40, 50};

        // Criar um vídeo
        Video meuVideo = new Video(
                "Meu Video Teste",
                conteudoTeste,
                LocalDateTime.now().minusDays(2), // data de upload há 2 dias
                1080,
                185, // 3min 5s
                new String[]{"Primeiro comentário"},
                5,
                1
        );

        // Inserir um novo comentário
        meuVideo.insereComentario("Segundo comentário");

        // Dar um like
        meuVideo.thumbsUp();

        // Mostrar informações
        System.out.println("Nome do vídeo: " + meuVideo.getNome());
        System.out.println("Resolução: " + meuVideo.getResolucao() + "p");
        System.out.println("Duração: " + (meuVideo.getDuracaoTotalSeg() / 60) + "m " + (meuVideo.getDuracaoTotalSeg() % 60) + "s");
        System.out.println("Likes: " + meuVideo.getLikes());
        System.out.println("Dislikes: " + meuVideo.getDislikes());
        System.out.println("Comentários: ");
        for (String c : meuVideo.getComentarios()) {
            System.out.println(" - " + c);
        }

        // Dias desde o upload
        System.out.println("Dias desde upload: " + meuVideo.qstDiasDepois());

        // Processar conteúdo do vídeo e mostrar
        System.out.println("Conteúdo processado:" + meuVideo.processa());
    }
}
