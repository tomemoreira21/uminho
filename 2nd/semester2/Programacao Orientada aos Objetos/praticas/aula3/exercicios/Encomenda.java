import java.time.LocalDateTime;
import java.util.Arrays;

public class Encomenda {
    private Cliente cliente;
    private int numero;
    private LocalDateTime dataEncomenda;
    private LinhaDeEncomenda[] linha;
    private int ocupado;
    private int tamanho;

    // variável de classe
    private static int proximo_num = 1;
    
    public Encomenda (Cliente c,LocalDateTime d) {
        this.cliente = new Cliente(c);
        this.numero = Encomenda.getProximoNum();
        this.dataEncomenda = d;
        this.tamanho = 2;
        this.linha = new LinhaDeEncomenda[this.tamanho];
        this.ocupado = 0;
        proximo_num++;
    }

    public Encomenda() {
        this.cliente = new Cliente();
        this.numero = Encomenda.getProximoNum();
        this.dataEncomenda = LocalDateTime.now();
        this.tamanho = 64;
        this.ocupado = 0;
        this.linha = new LinhaDeEncomenda[this.tamanho];
        proximo_num++;
    }

    public Encomenda(Encomenda e) {
        this.cliente = e.getCliente();
        this.numero = e.getNumero();
        this.dataEncomenda = e.getDataEncomenda();
        this.linha = e.getLinha();
        this.tamanho = e.getTamanho();
        this.ocupado = e.getOcupado();
    }

    public Cliente getCliente() {
        return this.cliente.clone();
    }

    public void setCliente(Cliente cliente) {
        this.cliente = new Cliente(cliente);
    }

    public int getTamanho() {
        return tamanho;
    }

    public void setTamanho(int tamanho) {
        this.tamanho = tamanho;
    }

    public int getOcupado() {
        return ocupado;
    }

    public void setOcupado(int ocupado) {
        this.ocupado = ocupado;
    }

    public int getNumero() {
        return this.numero;
    }

    public void setNumero(int num) {
        this.numero = num;
    }

    public static int getProximoNum() {
        return proximo_num;
    }

    public static void setProximoNum(int proxNum) {
        proximo_num = proxNum;
    }

    public LocalDateTime getDataEncomenda() {
        return dataEncomenda;
    }

    public void setDataEncomenda(LocalDateTime dataEncomenda) {
        this.dataEncomenda = dataEncomenda;
    }

    public LinhaDeEncomenda[] getLinha() {
        LinhaDeEncomenda[] linhaNova = new LinhaDeEncomenda[this.tamanho];

        for (int i = 0; i < this.ocupado; i++) {
            linhaNova[i] = this.linha[i].clone();
        }

        return linhaNova;
    }

    public void setLinha(LinhaDeEncomenda[] linha) {
        int newSize = (linha.length > this.tamanho) ? linha.length * 2 : this.tamanho;
        this.tamanho = newSize;
        this.ocupado = linha.length;

        LinhaDeEncomenda[] linhaNova = new LinhaDeEncomenda[this.tamanho];

        for (int i = 0; i < this.ocupado; i++) {
            linhaNova[i] = linha[i].clone();
        }

        this.linha = linhaNova;
    }

    public double calculaValorTotal() {
        double soma = 0;

        for (int i = 0; i < this.ocupado; i++) {
            soma += this.linha[i].calculaValorLinhaEnc();
        }

        return soma;
    }

    public double calculaValorDesconto() {
        double soma = 0;

        for (int i = 0; i < this.ocupado; i++) {
            soma += this.linha[i].calculaValorDesconto();
        }

        return soma;
    }   

    public int numeroTotalProdutos() {
        int soma = 0;

        for (int i = 0; i < this.ocupado; i++) {
            soma += this.linha[i].getQuantidade();
        }
        
        return soma;
    }

    public boolean existeProdutoEncomenda(String refProduto) {
        for (int i = 0; i < this.ocupado; i++) {
            Produto p = this.linha[i].getProduto();
            if (p.getIdProduto().equals(refProduto)) return true;
        }

        return false;
    }

    public void adicionaLinha (LinhaDeEncomenda linha) {
        if (this.ocupado == this.tamanho) {
            this.tamanho *= 2;
            this.linha = Arrays.copyOf(this.linha, this.tamanho); // dá realloc do array
        }

        this.linha[this.ocupado] = new LinhaDeEncomenda(linha);
        this.ocupado++;
    }

    public void removeProduto(String codProd) {
        int index = -1;

        for (int i = 0; i < this.ocupado; i++) {
            Produto p = this.linha[i].getProduto();
            if (p.getIdProduto().equals(codProd)) {
                index = i;
                break;
            }
        }

        if (index == -1) return; // não existe o produto
        else {
            for (int j = index + 1; j < this.ocupado; j++) {
                this.linha[j-1] = this.linha[j];
            };

            this.linha[this.ocupado - 1] = null;
            this.ocupado--;
        }

    }

    public Encomenda clone() {
        return new Encomenda(this);
    }

    public String toString() {
        String out = this.cliente.toString();
        out = out + "\n";

        for (int i = 0; i < this.ocupado; i++) {
            out += this.linha[i].toString() + "\n";
        }

        out += ("Ocupado = " + this.ocupado + "\n"); 
        out += ("Size = " + this.tamanho + "\n");

        return out;
    }

    public boolean equals (Object o) {
        if (this == o)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Encomenda e = (Encomenda) o;
        return (e.getCliente().equals(this.cliente) &&
                e.getNumero() == this.numero &&
                e.getDataEncomenda().equals(this.dataEncomenda) &&
                Arrays.equals(e.getLinha(), this.linha)
        );
    }



}
