import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class GestaoEncomendas {
    private Map<Integer,Encomenda> encomendas;
 
    public GestaoEncomendas (Map<Integer,Encomenda> e) {
        this.setEncomendas(e);
    }

    public GestaoEncomendas() {
        this.encomendas = new HashMap<Integer,Encomenda>();
    }

    public GestaoEncomendas(GestaoEncomendas ge) {
        this.encomendas = ge.getEncomendas();
    }

    public Map<Integer,Encomenda> getEncomendas() {
        Map<Integer,Encomenda> encs = new HashMap<>();

        for (Map.Entry<Integer,Encomenda> e : this.encomendas.entrySet()) {
            encs.put(e.getKey(),e.getValue().clone());
        }
        
        return encs;
    }

    public void setEncomendas(Map<Integer,Encomenda> enc) {
        Map<Integer,Encomenda> encs = new HashMap<>();

        for (Map.Entry<Integer,Encomenda> e : enc.entrySet()) {
            encs.put(e.getKey(),e.getValue().clone());
        }

        this.encomendas = encs;
    }

    public Set<Integer> todosCodigosEnc() {
        return encomendas.keySet();
    }

    public void addEncomenda(Encomenda enc) {
        this.encomendas.put(enc.getNumero(),enc.clone());
    }

    public Encomenda getEncomenda(Integer codEnc) {
        return this.encomendas.get(codEnc).clone();
    }

    public void removeEncomenda(Integer codEnc) {
        this.encomendas.remove(codEnc);
    }

    public Integer encomendaComMaisProdutos() {
        return this.encomendas.keySet()
                              .stream()
                              .max(Comparator.comparingInt(e -> this.encomendas.get(e).numeroTotalProdutos()))
                              .orElse(null);
    }


    public Set<Integer> encomendasComProduto(String codProd) {
        return this.encomendas.values().stream()
                              .filter(e -> e.existeProdutoEncomenda(codProd))
                              .map(Encomenda :: getNumero)
                              .collect(Collectors.toSet());
    }

    public Set<Integer> encomendasAposData(LocalDate d) {
        Set<Integer> encs = this.encomendas.keySet();

        encs.stream().filter(enc -> getEncomenda(enc).getDataEncomenda().isAfter(d)).collect(Collectors.toSet());

        return encs;
    }

    public Encomenda encomendaMaiorValor() {
        Encomenda e = null;
        double valorMax = 0;

        for (Map.Entry<Integer,Encomenda> encs : encomendas.entrySet()) {
            Encomenda enc = encs.getValue();
            double valorTotal = enc.calculaValorTotal();

            if (valorTotal > valorMax) {
                valorMax = valorTotal;
                e = enc.clone();
            }
            
        }

        return e;
    }

    public Encomenda encomendaMaiorValor_v1() {
        Encomenda res = this.encomendas.values()
                              .stream()
                              .max(Comparator.comparingDouble(Encomenda :: calculaValorTotal))
                              .orElse(null);

        return (res != null) ? res.clone() : null;
    }


    // Função Geral com um comparador
    public Set<Encomenda> encomendasOrdenadas (Comparator<Encomenda> c) {
        return this.encomendas.values()
                        .stream()
                        .map (Encomenda :: clone)
                        .sorted(c)
                        .collect(Collectors.toSet());
    }

    public Set<Encomenda> encomendasOrdernadasPorQEncomendas_v1() {
        return this.encomendas.values()
                              .stream()
                              .map (Encomenda :: clone)
                              .sorted((e1,e2) -> e1.numeroTotalProdutos() - e2.numeroTotalProdutos())
                              .collect(Collectors.toSet());
    }

    public Set<Encomenda> encomendasOrdenadasPorQtProdutos_v2() {
        return encomendasOrdenadas(new ComparadorPorQt());
    }

    public Set<Encomenda> encomendasValorDescrecente_v2() {
        return encomendasOrdenadas(new ComparadorPorValorDescrescente());
    }

    public Map<String,List<Integer>> encomendasDeProduto() {
        Map<String,List<Integer>> encs = new HashMap<String,List<Integer>>();

        for (Map.Entry <Integer,Encomenda> e : this.encomendas.entrySet()) {
            Encomenda enc = e.getValue();
            for (LinhaDeEncomenda linha : enc.getLinha()) {
                String idProduto = linha.getProduto().getIdProduto();

                if (!encs.containsKey(idProduto)) {
                    encs.put(idProduto, new ArrayList<Integer>());
                }

                encs.get(idProduto).add(e.getKey());
            }
        }

        return encs;
    } 


}
