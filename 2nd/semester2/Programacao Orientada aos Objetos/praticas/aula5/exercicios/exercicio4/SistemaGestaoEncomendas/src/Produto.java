public class Produto {
    private String idProduto;
    private String descricao;
    private double preco;

    public Produto(String idProduto, String descricao, double preco) {
        this.idProduto = idProduto;
        this.descricao = descricao;
        this.preco = preco;
    }

    public Produto(Produto umProduto) {
        this.idProduto = umProduto.getIdProduto();
        this.descricao = umProduto.getDescricao();
        this.preco = umProduto.getPreco();
    }

    public Produto() {
        this.idProduto = "";
        this.descricao = "";
        this.preco = 0;
    }

    public String getIdProduto() {
        return idProduto;
    }

    public void setIdProduto(String idProduto) {
        this.idProduto = idProduto;
    }
    
    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public Produto clone() {
        return new Produto(this);
    }

    public String toString() {
        return "id = " + this.idProduto + ", " + "descricao = " + this.descricao +
         ", preco = " + this.preco;
    }

    public boolean equals (Object o) {
        if (this == o)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Produto p = (Produto) o;
        return (p.getIdProduto().equals(this.idProduto) &&
                p.getDescricao().equals(this.descricao) &&
                p.getPreco() == this.preco
        );
    }

}
