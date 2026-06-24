import java.util.Arrays;

public class Telemovel {
    private String marca;
    private String modelo;
    private int disX;
    private int disY;
    private int armazenamentoTexto; // capacidade máxima para mensagens
    private int armazenamentoFotoApp; // capacidade máxima para fotos e apss
    private int armazenamentoFoto; // capacidade máxima para as fotos 
    private int armazenamentoApp; // capacidade máxima para as apps
    private int espacoOcupadoTexto;
    private int espacoOcupadoFoto;
    private int espacoOcupadoApp;
    private int nFotosSave;
    private int nAppInstaladas;
    private String[] nomeApp;
    private String[] texto;

    public Telemovel(String marca, String modelo, int disX, int disY, int armazenamentoTexto, int armazenamentoFotoApp,
            int armazenamentoFoto, int armazenamentoApp, int espacoOcupadoTexto, int espacoOcupadoFoto,
            int espacoOcupadoApp, int nFotosSave, int nAppInstaladas, String[] nomeApp, String[] texto) {
        this.marca = marca;
        this.modelo = modelo;
        this.disX = disX;
        this.disY = disY;
        this.armazenamentoTexto = armazenamentoTexto;
        this.armazenamentoFotoApp = armazenamentoFotoApp;
        this.armazenamentoFoto = armazenamentoFoto;
        this.armazenamentoApp = armazenamentoApp;
        this.espacoOcupadoTexto = espacoOcupadoTexto;
        this.espacoOcupadoFoto = espacoOcupadoFoto;
        this.espacoOcupadoApp = espacoOcupadoApp;
        this.nFotosSave = nFotosSave;
        this.nAppInstaladas = nAppInstaladas;
        this.nomeApp = nomeApp;
        this.texto = texto;
    }

    public Telemovel(Telemovel t) {
        this.marca = t.getMarca();
        this.modelo = t.getModelo();
        this.disX = t.getDisX();
        this.disY = t.getDisY();
        this.armazenamentoTexto = t.getArmazenamentoTexto();
        this.armazenamentoFotoApp = t.getArmazenamentoFotoApp();
        this.armazenamentoFoto = t.getArmazenamentoFoto();
        this.armazenamentoApp = t.getArmazenamentoApp();
        this.espacoOcupadoTexto = t.getEspacoOcupadoTexto();
        this.espacoOcupadoFoto = t.getEspacoOcupadoFoto();
        this.espacoOcupadoApp = t.getEspacoOcupadoApp();
        this.nFotosSave = t.getnFotosSave();
        this.nAppInstaladas = t.getnAppInstaladas();
        this.nomeApp = Arrays.copyOf(t.getNomeApp(),t.getNomeApp().length);
        this.texto = Arrays.copyOf(t.getTexto(), t.getTexto().length);
    }

     public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getModelo() {
        return modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public int getDisX() {
        return disX;
    }

    public void setDisX(int disX) {
        this.disX = disX;
    }

    public int getDisY() {
        return disY;
    }

    public void setDisY(int disY) {
        this.disY = disY;
    }

    public int getArmazenamentoTexto() {
        return armazenamentoTexto;
    }

    public void setArmazenamentoTexto(int armazenamentoTexto) {
        this.armazenamentoTexto = armazenamentoTexto;
    }

    public int getArmazenamentoFotoApp() {
        return armazenamentoFotoApp;
    }

    public void setArmazenamentoFotoApp(int armazenamentoFotoApp) {
        this.armazenamentoFotoApp = armazenamentoFotoApp;
    }

    public int getArmazenamentoFoto() {
        return armazenamentoFoto;
    }

    public void setArmazenamentoFoto(int armazenamentoFoto) {
        this.armazenamentoFoto = armazenamentoFoto;
    }

    public int getArmazenamentoApp() {
        return armazenamentoApp;
    }

    public void setArmazenamentoApp(int armazenamentoApp) {
        this.armazenamentoApp = armazenamentoApp;
    }

    public int getEspacoOcupadoTexto() {
        return espacoOcupadoTexto;
    }

    public void setEspacoOcupadoTexto(int espacoOcupadoTexto) {
        this.espacoOcupadoTexto = espacoOcupadoTexto;
    }

    public int getEspacoOcupadoFoto() {
        return espacoOcupadoFoto;
    }

    public void setEspacoOcupadoFoto(int espacoOcupadoFoto) {
        this.espacoOcupadoFoto = espacoOcupadoFoto;
    }

    public int getEspacoOcupadoApp() {
        return espacoOcupadoApp;
    }

    public void setEspacoOcupadoApp(int espacoOcupadoApp) {
        this.espacoOcupadoApp = espacoOcupadoApp;
    }

    public int getnFotosSave() {
        return nFotosSave;
    }

    public void setnFotosSave(int nFotosSave) {
        this.nFotosSave = nFotosSave;
    }

    public int getnAppInstaladas() {
        return nAppInstaladas;
    }

    public void setnAppInstaladas(int nAppInstaladas) {
        this.nAppInstaladas = nAppInstaladas;
    }

    public String[] getNomeApp() {
        return nomeApp;
    }

    public void setNomeApp(String[] nomeApp) {
        this.nomeApp = nomeApp;
    }

    public String[] getTexto() {
        return texto;
    }

    public void setTexto(String[] texto) {
        this.texto = texto;
    }

    // considerei que o armazenamento máximo é armazenamentoFotoApp
    public boolean existeEspaco (int numeroBytes) {
        return (this.espacoOcupadoFoto + 
               this.espacoOcupadoApp + numeroBytes <= this.armazenamentoFotoApp);
    }
    
    public void instalaApp(String nome,int tamanho) {
        if (!existeEspaco(tamanho) || (this.espacoOcupadoApp + tamanho > this.armazenamentoApp)) return;

        int newSize = this.nAppInstaladas + 1;
        String[] novosNomes = Arrays.copyOf(this.nomeApp, newSize);
        novosNomes[newSize - 1] = nome;

        this.nAppInstaladas++;
        this.espacoOcupadoApp += tamanho;
        this.nomeApp = novosNomes;
    }

    public void recebeMsg(String msg) {
        int size = msg.getBytes().length;

        if (this.espacoOcupadoTexto + size > this.armazenamentoTexto) return;

        int newSize = this.texto.length + 1;
        String[] novasMsg = Arrays.copyOf(this.texto, newSize);
        novasMsg[newSize - 1] = msg;

        this.espacoOcupadoTexto += size;
        this.texto = novasMsg;
    }

    public double tamMedioApps() {
        if (this.nAppInstaladas == 0) return 0;
        return (double)this.espacoOcupadoApp/this.nAppInstaladas;
    }

    public String maiorMsg() {
        String maior = "";
        int max = Integer.MIN_VALUE;

        for (int i = 0; i < this.texto.length; i++) {
            int size = this.texto[i].getBytes().length;

            if (size > max) {
                max = size;
                maior = this.texto[i];
            }
        }

        return maior;
    }

    public void removeApp (String nome,int tamanho) {
        int newSize = this.nAppInstaladas - 1;
        String[] novasApps = new String[newSize];

        int j = 0;
        for (int i = 0; i < this.nomeApp.length; i++) {
            if (!this.nomeApp[i].equals(nome)) {
                novasApps[j++] = this.nomeApp[i];
            }
        }

        this.nAppInstaladas--;
        this.espacoOcupadoApp -= tamanho;
        this.nomeApp = novasApps;
    }
}
