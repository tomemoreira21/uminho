public class LinhaDeEncomenda {
    private Produto produto;
    private int quantidade;
    private int descontoComercial;

    // variáveis de classe
    private static int regimeImp = 23;

    public LinhaDeEncomenda(Produto prod,int quantidade,int descontoComercial) {
        this.produto = new Produto(prod);
        this.quantidade = quantidade;
        this.descontoComercial = descontoComercial;
    }

    public LinhaDeEncomenda(LinhaDeEncomenda l) {
        this.produto = l.getProduto();
        this.quantidade = l.getQuantidade();
        this.descontoComercial = l.getDescontoComercial();
    }

    public LinhaDeEncomenda() {
        this.produto = new Produto();
        this.quantidade = 1;
        this.descontoComercial = 10;
    }

    public Produto getProduto() {
        return this.produto.clone();
    } 
    
    public void setProduto(Produto umProduto) {
        this.produto = new Produto(umProduto);
    }

    public int getQuantidade() {
        return this.quantidade;
    }

    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }

    public static int getRegimeImp() {
        return regimeImp;
    }

    public static void setRegimeImp(int regimeI) {
        regimeImp = regimeI;
    }

    public int getDescontoComercial() {
        return this.descontoComercial;
    }

    public void setDescontoComercial(int descontoComercial) {
        this.descontoComercial = descontoComercial;
    }

    public double calculaValorLinhaEnc() {
        double precoTotal = this.produto.getPreco() * this.quantidade;
        precoTotal = precoTotal * (1 - (this.descontoComercial/100.0));
        return precoTotal * (1 + (LinhaDeEncomenda.getRegimeImp()/100.0));
    }

    public double calculaValorDesconto() {
        return ((double)this.descontoComercial/100.0) * (this.produto.getPreco() * this.quantidade);
    }

    public LinhaDeEncomenda clone() {
        return new LinhaDeEncomenda(this);
    }

    public String toString() {
        return "quantidade = " + this.quantidade +  ", descontoComercial = " + this.descontoComercial
        + ", " + this.produto.toString();
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        LinhaDeEncomenda e = (LinhaDeEncomenda) o;
        return (e.getProduto().equals(this.produto) && 
                e.getQuantidade() == this.quantidade &&
                e.getDescontoComercial() == this.descontoComercial
        );
    }
    
}
