import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class SistemaGestaoEncomendas {
    private List<Encomenda> listaEncomendas;

    public SistemaGestaoEncomendas(List<Encomenda> listEnc) {
        this.setListaEncomendas(listEnc);
    }

    public SistemaGestaoEncomendas() {
        this.listaEncomendas = new ArrayList<Encomenda>();
    }

    public SistemaGestaoEncomendas(SistemaGestaoEncomendas sge) {
        this.listaEncomendas = sge.getListaEncomendas();
    }

    public List<Encomenda> getListaEncomendas() {
        ArrayList<Encomenda> listEnc = new ArrayList<Encomenda>();

        for (Encomenda e : this.listaEncomendas) {
            listEnc.add(e.clone());
        }

        return listEnc;
    }


    public void setListaEncomendas(List<Encomenda> umaList) {
        ArrayList<Encomenda> novaList = new ArrayList<Encomenda>(umaList.size());

        for (Encomenda e : umaList) {
            novaList.add(e.clone());
        }

        this.listaEncomendas = novaList;
    }

    public void insereEncomenda(String nomeCliente,int nif,String morada,LocalDate dataEncomenda, List<LinhaDeEncomenda> linhaEncomendas) {
        Encomenda e = new Encomenda(new Cliente(nomeCliente, nif, morada), dataEncomenda, linhaEncomendas);
        this.listaEncomendas.add(e);
    }

    public void insereEncomenda (Encomenda enc) {
        this.listaEncomendas.add(enc.clone());
    }   

    public Encomenda pesquisaNrEncomenda(int nEnc) {
        boolean encontrado = false;
        Iterator<Encomenda> it = this.listaEncomendas.iterator();
        Encomenda enc = null;

        while (it.hasNext() && !encontrado) {
            Encomenda e = it.next();    

            if (e.getNumero() == nEnc) {
                encontrado = true;
                enc = e.clone();
            }
        }

        return enc;
    }

    public void removeEncomenda(int nEnc) {
        this.listaEncomendas.removeIf(e -> e.getNumero() == nEnc);
    }

    public Encomenda calculaEncMaiorValor() {
        Encomenda max = null;
        double valorMax = 0;

        for (Encomenda e : this.listaEncomendas) {
            double valorAtual = e.calculaValorTotal();

            if (valorAtual > valorMax) {
                max = e.clone();
                valorMax = valorAtual; 
            }
        }

        return max;
    }

    public int numeroTotalProdutos() {
        int numTotal = 0;

        for (Encomenda e : this.listaEncomendas) {
            numTotal += e.numeroTotalProdutos();
        }

        return numTotal;
    }

    public SistemaGestaoEncomendas clone() {
        return new SistemaGestaoEncomendas(this);
    }

    public String toString() {
        String out = "";

        for (Encomenda e : this.listaEncomendas) {
            out += (e.toString() + "\n");
        }

        return out;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        SistemaGestaoEncomendas sge = (SistemaGestaoEncomendas) o;
        return sge.getListaEncomendas().equals(this.listaEncomendas);
    }

     
}