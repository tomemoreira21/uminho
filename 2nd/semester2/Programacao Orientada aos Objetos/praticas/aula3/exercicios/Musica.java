import java.util.Arrays;

public class Musica {
    private String nome;
    private String interprete;
    private String autor;
    private String nome_editora;
    private String[] letra;
    private String[] musica;
    private int segundos;
    private long nVezes;

    public Musica(String nome, String interprete, String autor, String nome_editora, String[] letra, String[] musica,
            int segundos, long nVezes) {
        this.nome = nome;
        this.interprete = interprete;
        this.autor = autor;
        this.nome_editora = nome_editora;
        this.letra = letra;
        this.musica = musica;
        this.segundos = segundos;
        this.nVezes = nVezes;
    }

    public Musica() {
        this.nome = "";
        this.interprete = "";
        this.autor = "";
        this.nome_editora = "";
        this.letra = new String[0];
        this.musica = new String[0];
        this.segundos = 0;
        this.nVezes = 0;
    }

    public Musica(Musica m) {
        this.nome = m.getNome();
        this.interprete = m.getInterprete();
        this.autor = m.getAutor();
        this.nome_editora = m.getNome_editora();
        this.letra = Arrays.copyOf(m.getLetra(), m.getLetra().length);
        this.musica = Arrays.copyOf(m.getMusica(), m.getMusica().length);
        this.segundos = m.getSegundos();
        this.nVezes = m.getnVezes();
    }


    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getInterprete() {
        return this.interprete;
    }

    public void setInterprete(String interprete) {
        this.interprete = interprete;
    }

    public String getAutor() {
        return this.autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getNome_editora() {
        return this.nome_editora;
    }

    public void setNome_editora(String nome_editora) {
        this.nome_editora = nome_editora;
    }

    public String[] getLetra() {
        return this.letra;
    }

    public void setLetra(String[] letra) {
        this.letra = letra;
    }

    public String[] getMusica() {
        return this.musica;
    }

    public void setMusica(String[] musica) {
        this.musica = musica;
    }

    public int getSegundos() {
        return this.segundos;
    }

    public void setSegundos(int segundos) {
        this.segundos = segundos;
    }

    public long getnVezes() {
        return this.nVezes;
    }

    public void setnVezes(long nVezes) {
        this.nVezes = nVezes;
    }

    public int qtsLinhasPoema() {
        return this.letra.length;
    }

    public int numeroCaracteres() {
        int soma = 0;

        for (int i = 0; i < this.letra.length; i++) {
            soma += this.letra[i].length();
        }

        return soma;
    }

    public void addLetra (int posicao,String novaLinha) {
        if (posicao < 0 || posicao > this.letra.length) return;

        String[] novaLetra = new String[this.letra.length + 1];
        int j = 0;

        for (int i = 0; i < novaLetra.length; i++) {
            if (i == posicao) {
                novaLetra[i] = novaLinha;
            } else {
                novaLetra[i] = this.letra[j++];
            }
        }

        this.letra = novaLetra;
    }

    public String linhaMaisLonga() {
        String maisLonga = "";
        int max = Integer.MIN_VALUE;

        for (int i = 0; i < this.letra.length; i++) {
            int numCaracteres = this.letra[i].length();

            if (numCaracteres > max) {
                max = numCaracteres;
                maisLonga = this.letra[i];
            }
        }

        return maisLonga;
    }
    
    private int devolveIndexMax(int[] repLetras) {
        int max = 0;
        int index = -1;
        
        for (int i = 0; i < repLetras.length; i++) {
            if (repLetras[i] > max) {
                max = repLetras[i];
                index = i;
            }
        }

        return index;
    }

    public String[] letrasMaisUtilizadas() {
        int[] repLetras = new int[26]; // associar a cada indice o numero de repeticoes da letra;
        String[] charMaisRepetidos = new String[3];
        Arrays.fill(repLetras, 0);

        for (int i = 0; i < this.letra.length; i++) {
            String linhaMinuscula = this.letra[i].toLowerCase();

            for (int j = 0; j < linhaMinuscula.length(); j++) {
                char letra = linhaMinuscula.charAt(j);
                if (letra < 'a' || letra > 'z') continue;

                int index = letra - 'a';
                repLetras[index]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            int indexMax = this.devolveIndexMax(repLetras);
            repLetras[indexMax] = 0;
            charMaisRepetidos[i] = Character.toString((char) ('a' + indexMax));
        }

        return charMaisRepetidos;
    }



}
