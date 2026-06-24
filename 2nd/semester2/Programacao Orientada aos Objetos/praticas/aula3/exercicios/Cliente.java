public class Cliente {
    private String nome;
    private long numeroFiscal;
    private String morada;

    public Cliente(String n,long nF,String m) {
        this.nome = n;
        this.numeroFiscal = nF;
        this.morada = m;
    }

    public Cliente (Cliente umCliente) {
        this.nome = umCliente.getNome();
        this.numeroFiscal = umCliente.getNumeroFiscal();
        this.morada = umCliente.getMorada();
    }

    public Cliente() {
        this.nome = ""; 
        this.numeroFiscal = 198668317;
        this.morada = "";
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public long getNumeroFiscal() {
        return numeroFiscal;
    }

    public void setNumeroFiscal(long numeroFiscal) {
        this.numeroFiscal = numeroFiscal;
    }

    public String getMorada() {
        return morada;
    }

    public void setMorada(String morada) {
        this.morada = morada;
    }

    public Cliente clone() {
        return new Cliente(this);
    }

    public String toString() {
        return "nome = " + this.nome + ", numeroFiscal = " + this.numeroFiscal + ", morada = " + this.morada;
    }

    public boolean equals (Object o) {
        if (this == o)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Cliente c = (Cliente) o;
        return (c.getNome().equals(this.nome) &&
                c.getNumeroFiscal() == this.numeroFiscal &&
                c.getMorada().equals(this.morada)
        );
    }
    
}
