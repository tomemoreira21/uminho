import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class Encomenda {
    private Cliente c;
    private int numero;
    private LocalDate dataEncomenda;
    private List<LinhaDeEncomenda> linha;

    private static int proximo_num = 1;

    public Encomenda(Cliente cliente,LocalDate data,List<LinhaDeEncomenda> list) {
        this.c = new Cliente(cliente);
        this.numero = getProximo_num();
        this.dataEncomenda = data;
        this.setLinha(list);
        incProximo_num();;
    }

    public Encomenda() {
        this.c = null;
        this.numero = getProximo_num();
        this.dataEncomenda = LocalDate.now();
        this.linha = new ArrayList<LinhaDeEncomenda>();
        incProximo_num();
    }

    public Encomenda(Encomenda l) {
        this.c = l.getCliente();
        this.numero = l.getNumero();
        this.dataEncomenda = l.getDataEncomenda();
        this.linha = l.getLinha();
    }

    public Cliente getCliente() {
        return new Cliente(this.c);
    }

    public void setCliente(Cliente c) {
        this.c = new Cliente(c);
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public LocalDate getDataEncomenda() {
        return dataEncomenda;
    }

    public void setDataEncomenda(LocalDate dataEncomenda) {
        this.dataEncomenda = dataEncomenda;
    }

    public List<LinhaDeEncomenda> getLinha() {
        ArrayList<LinhaDeEncomenda>  linhaNova = new ArrayList<>(this.linha.size());

        for (LinhaDeEncomenda l : this.linha) {
            linhaNova.add(l.clone());
        }

        return linhaNova;
    }

    public void setLinha(List<LinhaDeEncomenda> umaLinha) {
        ArrayList<LinhaDeEncomenda> linhaNova = new ArrayList<>(umaLinha.size());

        for (LinhaDeEncomenda l : umaLinha) {
            linhaNova.add(l.clone());
        }

        this.linha = linhaNova;
    }

    public static int getProximo_num() {
        return proximo_num;
    }

    public static void incProximo_num() {
        proximo_num++;
    }

    public static void setProximo_num(int proximo_num) {
        Encomenda.proximo_num = proximo_num;
    }

    public double calculaValorTotal() {
        double soma = 0;

        Iterator<LinhaDeEncomenda> it = this.linha.iterator();

        while (it.hasNext()) {
            soma += it.next().calculaValorLinhaEnc();
        }

        return soma;
    }

    public double calculaValorDesconto() {
        double soma = 0;

        Iterator<LinhaDeEncomenda> it = this.linha.iterator();

        while (it.hasNext()) {
            soma += it.next().calculaValorDesconto();
        }

        return soma;
    }

    public int numeroTotalProdutos() {
        int count = 0;

        Iterator<LinhaDeEncomenda> it = this.linha.iterator();

        while (it.hasNext()) {
            count += it.next().getQuantidade();
        }

        return count;
    }

    public boolean existeProdutoEncomenda(String refProduto) {
        return this.linha.stream().anyMatch(l -> l.getProduto().getIdProduto().equals(refProduto));
    }

    public void adicionaLinha (LinhaDeEncomenda linha) {
        this.linha.add(linha.clone());
    }

    public void removeProduto (String codProduto) {
        this.linha.removeIf(l -> l.getProduto().getIdProduto().equals(codProduto));
    }

    public Encomenda clone() {
        return new Encomenda(this);
    }

    public String toString() {
        String out = this.c.toString();
        out = out + "\nNumero Encomenda = " + this.numero + "\n";

        for (LinhaDeEncomenda l : this.linha) {
            out += (l.toString() + "\n");
        }
    
        return out;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Encomenda e = (Encomenda) o;
        return (e.getCliente().equals(this.c) &&
                e.getNumero() == this.numero &&
                e.getDataEncomenda().equals(this.dataEncomenda) &&
                e.getLinha().equals(this.linha)
        );
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.getCliente(),this.getNumero(),this.getDataEncomenda(),this.getLinha());
    }

}
