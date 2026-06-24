import java.time.LocalDateTime;

public class PedidoSuporte {
    private String user;
    private LocalDateTime dataPedido;
    private String assunto;
    private String descricao;
    private String tecnico;
    private LocalDateTime dataConclusao;
    private String info;

    public PedidoSuporte(String user, LocalDateTime dataPedido, String assunto, String descricao) {
        this.user = user;
        this.dataPedido = dataPedido;
        this.assunto = assunto;
        this.descricao = descricao;
        this.tecnico = null;
        this.dataConclusao = null;
        this.info = null;
    }

    public PedidoSuporte() {
        this.user = "1";
        this.dataPedido = LocalDateTime.now();
        this.assunto = null;
        this.descricao = null;
        this.tecnico = null;
        this.dataConclusao = null;
        this.info = null;   
    }

    public PedidoSuporte(PedidoSuporte umPedido) {
        this.user = umPedido.getUser();
        this.dataPedido = umPedido.getDataPedido();
        this.assunto = umPedido.getAssunto();   
        this.descricao = umPedido.getDescricao();
        this.tecnico = umPedido.getTecnico();
        this.dataConclusao = umPedido.getDataConclusao();
        this.info = umPedido.getInfo();
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public LocalDateTime getDataPedido() {
        return dataPedido;
    }
    
    public void setDataPedido(LocalDateTime dataPedido) {
        this.dataPedido = dataPedido;
    }

    public String getAssunto() {
        return assunto;
    }

    public void setAssunto(String assunto) {
        this.assunto = assunto;
    }

    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public String getTecnico() {
        return tecnico;
    }

    public void setTecnico(String tecnico) {
        this.tecnico = tecnico;
    }

    public LocalDateTime getDataConclusao() {
        return dataConclusao;
    }

    public void setDataConclusao(LocalDateTime dataConclusao) {
        this.dataConclusao = dataConclusao;
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }

    public PedidoSuporte clone() {
        return new PedidoSuporte(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        PedidoSuporte pd = (PedidoSuporte) o;
        return pd.getUser().equals(this.user) &&
               pd.getDataPedido().equals(this.dataPedido);
    }

    public String toString() {
        return "user='" + user + '\'' +
            ", dataPedido=" + dataPedido +
            ", assunto='" + assunto + '\'' +
            ", descricao='" + descricao + '\'' +
            ", tecnico='" + tecnico + '\'' +
            ", dataConclusao=" + dataConclusao +
            ", info='" + info + '\'';
    }
    
}
