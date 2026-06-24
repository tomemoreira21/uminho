import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FBPost {
    private int id;
    private String nome;
    private LocalDateTime time;
    private String conteudo;
    private int likes;
    private List<String> comentarios;

    public FBPost (int id,String nome, LocalDateTime tempo,String c,int likes,List<String> comentarios) {
        this.id = id;
        this.nome = nome;
        this.time = tempo;
        this.conteudo = c;
        this.likes = likes;
        this.setComentarios(comentarios);
    }

    public FBPost() {
        this.id = 0;
        this.nome = null;
        this.time = LocalDateTime.now();
        this.conteudo = null;
        this.likes = 0;
        this.comentarios = new ArrayList<>();
    }

    public FBPost(FBPost umPost) {
        this.id = umPost.getId();
        this.nome = umPost.getNome();
        this.time = umPost.getTime();
        this.conteudo = umPost.getConteudo();
        this.likes = umPost.getLikes();
        this.comentarios = umPost.getComentarios();
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public LocalDateTime getTime() {
        return time;
    }

    public void setTime(LocalDateTime time) {
        this.time = time;
    }

    public String getConteudo() {
        return conteudo;
    }

    public void setConteudo(String conteudo) {
        this.conteudo = conteudo;
    }

    public int getLikes() {
        return likes;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public List<String> getComentarios() {
        ArrayList<String> novosComentarios = new ArrayList<>(this.comentarios.size());

        for (String comentario : this.comentarios) {
            novosComentarios.add(comentario);
        }

        return novosComentarios;
    }

    public void setComentarios(List<String> comentariosN) {
       ArrayList<String> novosComentarios = new ArrayList<>(comentariosN.size());

        for (String comentario : comentariosN) {
            novosComentarios.add(comentario);
        }

        this.comentarios = novosComentarios;
    }

    public void addComentario (String comentario) {
        this.comentarios.add(comentario);
    }

    public FBPost clone() {
        return new FBPost(this);
    }

    public String toString() {
        String out = "";

        out += ("id = " + this.id + ", nome = " + this.nome + ", time = " + this.time.toString() + ", conteudo = " + this.conteudo
        + ", likes = " + this.likes + "\nComentarios");

        int i = 1;
        for (String comentarios: this.comentarios) {
            out += ("\n" + i + " - " + comentarios);
            i++;
        }

        return out;
    }

    public boolean equals(Object o) {
        if (o == this) 
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        FBPost fb = (FBPost) o;
        return fb.getId() == this.id &&
               fb.getNome().equals(this.nome) &&
               fb.getTime().equals(this.time) &&
               fb.getConteudo().equals(this.conteudo) &&
               fb.getLikes() == this.likes &&
               fb.getComentarios().equals(this.comentarios);
    }


}
