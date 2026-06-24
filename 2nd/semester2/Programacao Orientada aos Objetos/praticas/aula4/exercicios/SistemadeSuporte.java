import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class SistemadeSuporte {
    private List<PedidoSuporte> pedidos;

    public SistemadeSuporte (List<PedidoSuporte> pedidos) {
        this.setPedidos(pedidos);
    }

    public SistemadeSuporte() {
        this.pedidos = new ArrayList<PedidoSuporte>();
    }

    public SistemadeSuporte (SistemadeSuporte umSis) {
        this.pedidos = umSis.getPedidos();
    }

    public List<PedidoSuporte> getPedidos() {
        return this.pedidos.stream().map(PedidoSuporte :: clone).collect(Collectors.toList());
    }

    public void setPedidos(List<PedidoSuporte> novosPedidos) {
        ArrayList<PedidoSuporte> pes = new ArrayList<>(novosPedidos.size());

        for (PedidoSuporte ps : novosPedidos) {
            pes.add(ps.clone());
        }

        this.pedidos = pes;
    }

    public void inserePedido (PedidoSuporte pedido) {
        this.pedidos.add(pedido.clone());
    }

    public PedidoSuporte procuraPedido (String user,LocalDateTime data) {
        boolean encontrado = false;
        Iterator<PedidoSuporte> it = this.pedidos.iterator();
        PedidoSuporte ps = null;

        while (it.hasNext() && !encontrado) {
            PedidoSuporte p = it.next();

            if (p.getUser().equals(user) && p.getDataPedido().equals(data)) {
                encontrado = true;
                ps = p.clone();
            }
        }

        return ps;
    }

    public void resolvePedido (PedidoSuporte pedido,String tecnico,String info) {
        boolean resolvido = false;
        Iterator<PedidoSuporte> it = this.pedidos.iterator();
        
        while (it.hasNext() && !resolvido) {
            PedidoSuporte p = it.next();

            if (p.equals(pedido)) {
                p.setTecnico(tecnico);
                p.setInfo(info);
                p.setDataConclusao(LocalDateTime.now());
                resolvido = true;
            }
        }
    }

    public List<PedidoSuporte> resolvidos() {
        return this.pedidos.stream().
                filter(ps -> ps.getDataConclusao() != null && ps.getTecnico() != null && ps.getInfo() != null)
                .map (PedidoSuporte :: clone)
                .collect(Collectors.toList());
    }

    // ter a String associada a um inteiro
    public String colaboradorTop() {
        Map<String, Integer>  colaboradorTop = new HashMap<>();
        int maxPedidos = 0;
        String userMax = null;

        for (PedidoSuporte ps : this.resolvidos()) {
            String tecnico = ps.getTecnico();
            int numVendasAtual = colaboradorTop.getOrDefault(tecnico,0) + 1; // default começa em 0

            colaboradorTop.put (tecnico,numVendasAtual);

            if (numVendasAtual > maxPedidos) {
                maxPedidos = numVendasAtual;
                userMax = tecnico;
            }
        }

        return userMax;
    }

    public List<PedidoSuporte> resolvidos(LocalDateTime inicio, LocalDateTime fim) {
        return this.resolvidos().stream()
                .filter(ps -> ps.getDataConclusao().isBefore(fim) && ps.getDataConclusao().isAfter(inicio))
                .map (PedidoSuporte :: clone) 
                .collect(Collectors.toList());
    }

    public double tempoMedioResolucao() {
        List<PedidoSuporte> pedidosResolvidos = this.resolvidos();

        double tempo_total = pedidosResolvidos.stream()
                            .mapToDouble (ps -> Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes())
                            .sum();

        return tempo_total/pedidosResolvidos.size();
    }

    public double tempoMedioResolucao(LocalDateTime inicio, LocalDateTime fim) {
        double tempo_total = 0;
        int num_pedidos = 0;
        
        for (PedidoSuporte ps : this.resolvidos()) {
            if (ps.getDataConclusao().isAfter(inicio) && ps.getDataConclusao().isBefore(fim)){
                tempo_total += Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes();
                num_pedidos++;
            }
        }

        return tempo_total/num_pedidos;
    }

    public PedidoSuporte pedidoMaisLongo() {
        double maxTime = 0;
        PedidoSuporte max = null;

        for (PedidoSuporte ps : this.resolvidos()) { // percorre apenas os resolvidos 
            double timeSolution = Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes();
            if (timeSolution > maxTime) {
                maxTime = timeSolution;
                max = ps.clone();
            }
        }

        return max;
    }

    public PedidoSuporte pedidoMaisLongo(LocalDateTime inicio, LocalDateTime fim) {
        double maxTime = 0;
        PedidoSuporte max = null;

        for (PedidoSuporte ps : this.resolvidos()) {
            if (ps.getDataConclusao().isAfter(inicio) && ps.getDataConclusao().isBefore(fim)){
                double timeSolution = Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes();
                if (timeSolution > maxTime) {
                    maxTime = timeSolution;
                    max = ps.clone();
                }
            }
        }

        return max;
    }

    public PedidoSuporte pedidoMaisCurto() {
        double minTime = Double.MAX_VALUE;
        PedidoSuporte min = null;

        for (PedidoSuporte ps : this.resolvidos()) { // percorre apenas os resolvidos 
            double timeSolution = Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes();
            if (timeSolution < minTime) {
                minTime = timeSolution;
                min = ps.clone();
            }
        }

        return min;
    }

    public PedidoSuporte pedidoMaisCurto(LocalDateTime inicio, LocalDateTime fim) {
        double minTime = Double.MAX_VALUE;
        PedidoSuporte min = null;

        for (PedidoSuporte ps : this.resolvidos()) {
            if (ps.getDataConclusao().isAfter(inicio) && ps.getDataConclusao().isBefore(fim)){
                double timeSolution = Duration.between(ps.getDataPedido(), ps.getDataConclusao()).toMinutes();
                if (timeSolution < minTime) {
                    minTime = timeSolution;
                    min = ps.clone();
                }
            }
        }

        return min;
    }

    public SistemadeSuporte clone() {
        return new SistemadeSuporte(this);
    }

    public boolean equals (Object o) {
        if (o == this) 
            return true;

        if ((o == null) || (o.getClass() != this.getClass())) 
            return false;

        SistemadeSuporte ss = (SistemadeSuporte) o;
        return ss.getPedidos().equals(this.pedidos);
    }

    public String toString () {
        String out = "";

        for (PedidoSuporte ps : this.pedidos) {
            out += (ps.toString() + "\n");
        }

        return out;
    }


}
