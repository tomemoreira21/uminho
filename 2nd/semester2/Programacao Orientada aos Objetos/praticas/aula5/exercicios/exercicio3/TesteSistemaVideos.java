import java.time.LocalDate;
import java.time.LocalDateTime;

public class TesteSistemaVideos {
    public static void main(String[] args) {
        SistemaVideos manager = new SistemaVideos();
        
        // Criar alguns vídeos de teste
        Video v1 = new Video("video1", new byte[]{}, LocalDateTime.of(2026,3,1,10,0), 1080, 300, new String[]{}, 10, 2);
        Video v2 = new Video("video2", new byte[]{}, LocalDateTime.of(2026,3,5,15,30), 720, 600, new String[]{}, 25, 1);
        Video v3 = new Video("video3", new byte[]{}, LocalDateTime.of(2026,3,10,12,0), 1080, 450, new String[]{}, 15, 0);

        // Adicionar vídeos ao manager
        manager.addVideo(v1);
        manager.addVideo(v2);
        manager.addVideo(v3);

        // Dar likes adicionais
        manager.addLike("video1"); // agora v1 tem 11 likes
        manager.addLike("video3"); // agora v3 tem 16 likes

        // Mostrar vídeo com mais likes geral
        String top = manager.topLikes();
        System.out.println("Vídeo com mais likes (geral): " + top);

        // Mostrar vídeo com mais likes num intervalo de datas
        LocalDate start = LocalDate.of(2026,3,1);
        LocalDate end   = LocalDate.of(2026,3,6);
        String topIntervalo = manager.topLikes(start, end);
        System.out.println("Vídeo com mais likes (intervalo 1-6 março): " + topIntervalo);

        // Mostrar vídeo mais longo
        Video maisLongo = manager.videoMaisLongo();
        System.out.println("Vídeo mais longo: " + maisLongo.getNome() + " com " + maisLongo.getDuracaoTotalSeg() + " segundos");

        // Remover um vídeo
        manager.removeVideo("video2");
        System.out.println("Vídeo 'video2' removido.");

        // Tentar obter um vídeo
        Video test = manager.getVideo("video1");
        System.out.println("Obtido vídeo: " + test.getNome() + " com " + test.getLikes() + " likes");

    }
}
