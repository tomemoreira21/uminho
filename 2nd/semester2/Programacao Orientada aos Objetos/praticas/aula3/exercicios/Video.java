import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Arrays;

public class Video {
    private String nome;
    private byte[] conteudo; // byte é um tipo primitivo em Java que ocupa 8 bits (1 byte). -128 até 127
    private LocalDateTime dataLoad;
    private int resolucao;
    private int duracaoTotalSeg; // minutos = duracao / 60, segundos = duracao % 60
    private String[] comentarios;
    private int likes;
    private int dislikes;

    public Video(String nome, byte[] conteudo, LocalDateTime dataLoad, int resolucao, int duracaoTotalSeg,
            String[] comentarios, int likes, int dislikes) {
        this.nome = nome;
        this.conteudo = conteudo;
        this.dataLoad = dataLoad;
        this.resolucao = resolucao;
        this.duracaoTotalSeg = duracaoTotalSeg;
        this.comentarios = comentarios;
        this.likes = likes;
        this.dislikes = dislikes;
    }

    public Video() {
        this.nome = "";
        this.conteudo = new byte[0];
        this.dataLoad = LocalDateTime.now();
        this.resolucao = 720;
        this.duracaoTotalSeg = 600;
        this.comentarios = new String[0];
        this.likes = 0;
        this.dislikes = 0;
    }

    public Video(Video v) {
        this.nome = v.getNome();
        this.conteudo = Arrays.copyOf(v.getConteudo(),v.getConteudo().length);
        this.dataLoad = v.getDataLoad();
        this.resolucao = v.getResolucao();
        this.duracaoTotalSeg = v.getDuracaoTotalSeg();
        this.comentarios = Arrays.copyOf(v.getComentarios(), v.getComentarios().length);
        this.likes = v.getLikes();
        this.dislikes = v.getDislikes();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public byte[] getConteudo() {
        return conteudo;
    }

    public void setConteudo(byte[] conteudo) {
        this.conteudo = conteudo;
    }

    public LocalDateTime getDataLoad() {
        return dataLoad;
    }

    public void setDataLoad(LocalDateTime dataLoad) {
        this.dataLoad = dataLoad;
    }

    public int getResolucao() {
        return resolucao;
    }

    public void setResolucao(int resolucao) {
        this.resolucao = resolucao;
    }

    public int getDuracaoTotalSeg() {
        return duracaoTotalSeg;
    }

    public void setDuracaoTotalSeg(int duracaoTotalSeg) {
        this.duracaoTotalSeg = duracaoTotalSeg;
    }

    public String[] getComentarios() {
        return comentarios;
    }

    public void setComentarios(String[] comentarios) {
        this.comentarios = comentarios;
    }

    public int getLikes() {
        return likes;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public int getDislikes() {
        return dislikes;
    }

    public void setDislikes(int dislikes) {
        this.dislikes = dislikes;
    }

    public void insereComentario (String comentario) {
        int newSize = this.comentarios.length + 1;
        String[] todosComentarios = Arrays.copyOf(this.comentarios, newSize);
        
        todosComentarios[newSize - 1] = comentario;
        this.comentarios = todosComentarios;
    }

    public long qstDiasDepois() {
        long dias_diff = ChronoUnit.DAYS.between(this.dataLoad, LocalDateTime.now());
        return dias_diff;
    }

    public void thumbsUp() {
        (this.likes)++;
    }

    public String processa() {
        String res = "";
        
        for (int i = 0; i < this.conteudo.length; i++) {
            res += " " + this.conteudo[i];
        }

        return res;
    }

}
