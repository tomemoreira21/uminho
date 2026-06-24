import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class TesteFBFeed {
    public static void main (String[] args) {
        // POST 1
        List<String> comentarios1 = new ArrayList<>();
        comentarios1.add("Muito bom!");
        comentarios1.add("Parabéns!");
        FBPost post1 = new FBPost(1, "João", LocalDateTime.now(), "Meu primeiro post!", 10, comentarios1);

        // POST 2
        List<String> comentarios2 = new ArrayList<>();
        comentarios2.add("Adorei!");
        FBPost post2 = new FBPost(2, "Ana", LocalDateTime.now(), "Dia incrível hoje!", 5, comentarios2);

        // POST 3
        List<String> comentarios3 = new ArrayList<>();
        comentarios3.add("Top!");
        comentarios3.add("Muito fixe!");
        comentarios3.add("Grande post!");
        FBPost post3 = new FBPost(3, "Carlos", LocalDateTime.now(), "Férias na praia", 20, comentarios3);

        // POST 4
        List<String> comentarios4 = new ArrayList<>();
        comentarios4.add("Boa foto!");
        comentarios4.add("Onde é isso?");
        comentarios4.add("Quero ir aí!");
        comentarios4.add("Espetacular!");
        FBPost post4 = new FBPost(4, "Maria", LocalDateTime.now(), "Viagem a Itália", 15, comentarios4);

        // POST 5
        List<String> comentarios5 = new ArrayList<>();
        FBPost post5 = new FBPost(5, "Pedro", LocalDateTime.now(), "A estudar POO...", 3, comentarios5);

        // POST 6
        List<String> comentarios6 = new ArrayList<>();
        comentarios6.add("Força!");
        comentarios6.add("Vai correr bem!");
        comentarios6.add("Boa sorte!");
        comentarios6.add("Estamos contigo!");
        comentarios6.add("Depois conta como foi!");
        FBPost post6 = new FBPost(6, "Rita", LocalDateTime.now(), "Exame amanhã...", 8, comentarios6);

        // POST 7
        List<String> comentarios7 = new ArrayList<>();
        comentarios7.add("Muito interessante");
        comentarios7.add("Gostei de ler");
        comentarios7.add("Partilha mais!");
        comentarios7.add("Boa reflexão");
        comentarios7.add("Concordo contigo");
        comentarios7.add("Excelente");
        FBPost post7 = new FBPost(7, "Rita", LocalDateTime.now(), "Reflexão do dia", 12, comentarios7);

        List<FBPost> listPosts = new ArrayList<FBPost>();
        listPosts.add(post1);
        listPosts.add(post2);
        listPosts.add(post3);
        listPosts.add(post4);
        listPosts.add(post5);
        listPosts.add(post6);
        listPosts.add(post7);

        FBFeed posts = new FBFeed(listPosts);   

        System.out.format ("Nrº de posts do user Rita: %d\n",posts.nrPosts("Rita"));
        System.out.format (posts.postsOf("Rita").toString() + "\n\n");
        System.out.format (posts.getPost(6).toString() + "\n\n");

        posts.comment(post2, "Espetáculo");
        posts.comment(2, "Incrivel");
        posts.like(7);
        posts.like(post7);
        
        System.out.println (posts.toString());
        List<Integer> listId = posts.top5Comments();
        System.out.println(listId.toString());


    }   
}
