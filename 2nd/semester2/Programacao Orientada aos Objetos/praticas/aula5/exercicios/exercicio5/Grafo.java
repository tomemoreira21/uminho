import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;
import java.util.Map;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

public class Grafo {
    private Map<Integer,Set<Integer>> adj;

    public Grafo(Map<Integer,Set<Integer>> lA) {
        this.setListAdj(lA);
    }

    public Grafo() {
        this.adj = new HashMap<Integer,Set<Integer>>();
    }

    public Grafo(Grafo g) {
        this.adj = g.getListAdj();
    }

    public Map<Integer,Set<Integer>> getListAdj() {
        return this.adj.entrySet()
                       .stream()
                       .collect(Collectors.toMap(
                                e -> e.getKey(), 
                                e -> e.getValue().stream().collect(Collectors.toSet())));
    }

    public void setListAdj (Map <Integer,Set<Integer>> listAdj) {
        Map<Integer,Set<Integer>> lA = new HashMap<>();

        for (Map.Entry<Integer,Set<Integer>> entry : listAdj.entrySet()) {
            lA.put(entry.getKey(), entry.getValue().stream().collect(Collectors.toSet()));
        }

        this.adj = lA;
    }

    public void addArco(Integer vOrig,Integer vDest) {
        Set<Integer> listAdjvOrig = this.adj.get(vOrig);

        if (listAdjvOrig == null) {
            listAdjvOrig = new TreeSet<>();
            this.adj.put(vOrig,listAdjvOrig);
        }

        listAdjvOrig.add(vDest);
    }

    public boolean isSink(Integer v) {
        Set<Integer> adjacentes = this.adj.get(v);
        return adjacentes == null;
    }

    public boolean isSource(Integer v) {
        int count = 0;

        for (Set<Integer> vertex : this.adj.values()) {
            if (vertex.contains(v)) count++;
        }

        return count == 0;
    }

    public int size() {
        int numVertices = this.adj.keySet().size();
        int numArestas = this.adj.values()
                                 .stream()
                                 .mapToInt(Set<Integer> :: size) 
                                 .sum();
        
        return numVertices + numArestas;
    }

    // Algoritmo DFS recursivo
    public boolean haCaminho(Integer vOrig,Integer vDest) {
        return haCaminhoAux (vOrig,vDest,new HashSet<>());
    }

    private boolean haCaminhoAux(Integer vOrig,Integer vDest,Set<Integer> visitados) {
        if (vOrig.equals(vDest))
            return true;

        visitados.add(vOrig);

        Set<Integer> adjacentes = this.adj.get(vOrig);
        if (adjacentes == null) return false;

        for (Integer vizinho : adjacentes) {
            if (!visitados.contains(vizinho)) {
                if (haCaminhoAux(vizinho, vDest,visitados))
                    return true;
            }
        }

        return false;
    }

    private boolean getCaminhoAux (Integer vOrig,Integer vDest,Set<Integer> visitados,List<String> caminho) {
        visitados.add(vOrig);
        caminho.add(vOrig.toString());

        if (vOrig.equals(vDest)) {  
            return true;
        }

        Set<Integer> adjacentes = this.adj.get(vOrig);
        if (adjacentes != null) {
            for (Integer vizinho : adjacentes) {
                if (!visitados.contains(vizinho)) {
                    if (getCaminhoAux(vizinho, vDest, visitados, caminho))
                        return true;
                }
            }
        }


        // backtracking (remove se não resultou)
        caminho.remove(caminho.size() - 1);
        return false;
    }

    public List<String> getCaminho(Integer vOrig,Integer vDest) {
        List<String> caminho = new ArrayList<>();
        boolean existeCaminho = getCaminhoAux(vOrig, vDest, new HashSet<>(),caminho);
        if (existeCaminho) 
            return caminho;

        return null;
    }

    public Set<Map.Entry<Integer, Integer>> fanOut (Integer v) {
        Set<Map.Entry<Integer, Integer>> res = new HashSet<>();

        Set<Integer> adjacentes = this.adj.get(v);
        if (adjacentes != null) {
            for (Integer dest : adjacentes) {
                res.add(Map.entry(v, dest));
            }
        }

        return res;
    }

    public Set<Map.Entry<Integer, Integer>> fanIn(Integer v) {
        Set<Map.Entry<Integer, Integer>> res = new HashSet<>();

        for (Map.Entry<Integer,Set<Integer>> entry : this.adj.entrySet()) {
            Integer origin = entry.getKey();

            for (Integer dest : entry.getValue()) {
                if (dest.equals(v)) 
                    res.add(Map.entry(origin, v));
            }
        }

        return res;
    }

    private boolean addEdge(Integer vOrig,Integer vDest) {
        Set<Integer> adjacentes = this.adj.get(vOrig);

        if (adjacentes != null) {
            for (Integer dest : adjacentes) {
                if (dest.equals(vDest)) return true;
            }
        }

        return false;
    }

    public boolean subGrafo(Grafo g) {
        for (Map.Entry<Integer,Set<Integer>> entry : this.adj.entrySet()) {
            Integer origin = entry.getKey();

            for (Integer dest : entry.getValue()) {
                if (!g.addEdge(origin, dest)) 
                    return false;
            }
        }

        return true;

    }

}