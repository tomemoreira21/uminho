import java.util.Arrays;

public class TesteProgramaMusica {
    public static void main(String[] args) {

        // Criar poema e música
        String[] poema = {
            "Rosas são vermelhas,",
            "Violetas são azuis,",
            "O céu é bonito,",
            "E tu também és."
        };

        String[] linhasMusica = {
            "C D E F G",
            "G F E D C"
        };

        // Criar objeto Musica
        Musica m = new Musica("Minha Canção", "Cantor X", "Autor Y", "Editora Z",
                              poema, linhasMusica, 180, 1000);

        // Testar qtsLinhasPoema()
        System.out.println("Número de linhas do poema: " + m.qtsLinhasPoema());

        // Testar numeroCarateres()
        System.out.println("Número total de caracteres do poema: " + m.numeroCaracteres());

        // Testar addLetra()
        m.addLetra(2, "Nova linha adicionada");
        System.out.println("Poema após adicionar linha:");
        for (String linha : m.getLetra()) {
            System.out.println(linha + " (" + linha.length() + ")");
        }

        // Testar linhaMaisLonga()
        System.out.println("Linha mais longa do poema: " + m.linhaMaisLonga());

        // Testar letrasMaisUtilizadas()
        String[] topLetras = m.letrasMaisUtilizadas();
        System.out.println("Três letras mais usadas: " + Arrays.toString(topLetras));
    }
}