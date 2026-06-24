import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class Parque {
    private Map<String,Lugar> lugares;

    public Parque(Map<String,Lugar> lugares) {
        this.setLugares(lugares);
    }

    public Parque(){
        this.lugares = new HashMap<String,Lugar>();
    }

    public Parque(Parque p) {
        this.lugares = p.getLugares();
    }

    public Map<String,Lugar> getLugares() {
        Map<String,Lugar> ls = new HashMap<String,Lugar>();

        for (Map.Entry<String,Lugar> lugar : this.lugares.entrySet()) {
            ls.put(lugar.getKey(),lugar.getValue().clone());
        }

        return ls;
    }

    public void setLugares(Map<String,Lugar> lugares) {
        Map<String,Lugar> ls = new HashMap<String,Lugar>();

        for (Map.Entry<String,Lugar> lugar : lugares.entrySet()) {
            ls.put(lugar.getKey(),lugar.getValue().clone());
        }

        this.lugares = ls;
    }

    public Set<String> todasMatriculas() {
        return this.lugares.keySet();
    }

    public void registaOcupacao(Lugar l) {
        this.lugares.put(l.getMatricula(), l.clone());
    }

    public void removeLugar (String matricula) {
        this.lugares.remove(matricula);
    }

    public void alteraTempo (String matricula,int novoTempo) {
        if (!this.lugares.containsKey(matricula)) {
            this.lugares.put(matricula,new Lugar(matricula, null, novoTempo, false));
        } else {
            this.lugares.get(matricula).setMinutos(novoTempo);
        }
    }

    public int quantidadeTotalMinutos_v1() {
        int total = 0;

        for (Map.Entry<String,Lugar> lugar : this.lugares.entrySet()) {
            total += lugar.getValue().getMinutos();
        }

        return total;
    }

    public int quantidadeTotalMinutos_v2() {
        return this.lugares.values().stream().mapToInt(Lugar :: getMinutos).sum();
    }   

    public int quantidadeTotalMinutos_v3() {
        return this.lugares.values().stream()
                    .reduce(0,(ac,l) -> ac + l.getMinutos(),
                              (ac1,ac2) -> ac1 + ac2);    
    }

    public boolean existeLugar (String matricula) {
        return this.lugares.containsKey(matricula);
    }

    public List<String> matriculasTempo_v1(int x) {
        List<String> listaM = new ArrayList<String>();

        for (Map.Entry<String,Lugar> ls : this.lugares.entrySet()) {
            Lugar lugar = ls.getValue();
            if (lugar.getMinutos() > x && lugar.isPermanente()) 
                listaM.add(ls.getKey());
        }

        return listaM;
    }

    public List<String> matriculasTempo_v2(int x) {
        return this.lugares.keySet().stream()
                           .filter(m -> this.lugares.get(m).getMinutos() > x && this.lugares.get(m).isPermanente())
                           .collect(Collectors.toList());
    }

    public Collection<Lugar> copyLugares() {
        return this.lugares.values().stream().map (Lugar :: clone).collect(Collectors.toList());
    }

    public Lugar devolveLugar (String matricula) {
        return this.lugares.get(matricula).clone();
    }

}
