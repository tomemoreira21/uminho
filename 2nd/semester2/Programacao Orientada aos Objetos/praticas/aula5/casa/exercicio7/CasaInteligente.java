import java.util.*;
import java.util.stream.Collectors;

public class CasaInteligente {
    private Map<String,Set<Lampada>> lampadas;

    public CasaInteligente(Map<String,Set<Lampada>> lampadas) {
        this.setLampadas(lampadas);
    }

    public CasaInteligente() {
        this.lampadas = new HashMap<>();
    }

    public CasaInteligente(CasaInteligente cI) {
        this.lampadas = cI.getLampadas();
    }

    public Map<String,Set<Lampada>> getLampadas() {
        return this.lampadas.entrySet()
                            .stream()
                            .collect(Collectors.toMap(e -> e.getKey(),
                                                      e -> e.getValue().stream().map(Lampada :: clone).collect(Collectors.toSet())
                ));
    }

    public void setLampadas (Map<String,Set<Lampada>> lamp) {
        Map<String,Set<Lampada>> l = new HashMap<>();

        for (Map.Entry<String,Set<Lampada>> entry : lamp.entrySet()) {
            l.put(entry.getKey(), entry.getValue().stream().map(Lampada :: clone).collect(Collectors.toSet()));
        }

        this.lampadas = l;
    }

    public CasaInteligente clone() {
        return new CasaInteligente(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CasaInteligente c = (CasaInteligente) o;
        return c.getLampadas().equals(this.lampadas);
    }

    public void setUpLayout(Collection<String> nomesDivisoes) {
        for (String divisao : nomesDivisoes) {
            if (this.lampadas.get(divisao) == null) 
                this.lampadas.put(divisao,new HashSet<>());
        }
    }   

    public void addLampada(Lampada l,String divisao) {
        Set<Lampada> lamps = this.lampadas.get(divisao);

        if (lamps == null) {
            lamps = new HashSet<>();
            this.lampadas.put(divisao,lamps);
        }

        lamps.add(l.clone());
    }

    public boolean existeDivisao(String divisao) {
        return this.lampadas.containsKey(divisao);
    }
   
    public Collection<Lampada> lampadasEmDivisao(String divisao) {
        if (!existeDivisao(divisao))
            return Collections.emptySet();

        return this.lampadas.get(divisao).stream()
                                  .map(Lampada :: clone)
                                  .collect(Collectors.toCollection(HashSet :: new));
    }

    public void setEstado(String divisao,Lampada.Estado estado) {
        if (existeDivisao(divisao)) {
            if (estado == Lampada.Estado.ON) { 
                this.lampadas.get(divisao)
                            .forEach(l -> l.lampON());
            } else if (estado == Lampada.Estado.ECO) {
                this.lampadas.get(divisao)
                            .forEach(l -> l.lampECO());
            } else {
                this.lampadas.get(divisao)
                            .forEach(l -> l.lampOFF());
            }
        }                      
    }
    
    public String maisIluminada() {
        return this.lampadas.keySet()
                            .stream()
                            .max(Comparator.comparingInt(s -> this.lampadas.get(s).size()))
                            .orElse(null);
    }

    public double consumoCasa() {
        double consumoTotal = 0;

        for (Map.Entry<String,Set<Lampada>> entry : this.lampadas.entrySet()) {
            double consumoDiv = entry.getValue()
                                     .stream()
                                     .mapToDouble(Lampada :: totalConsumo)
                                     .sum();

            consumoTotal += consumoDiv;
        }

        return consumoTotal;
    }

    // solução pouco eficiente (tem de percorrer tudo) 
    public Lampada removeLamp (String ident) {
        for (Map.Entry<String,Set<Lampada>> entry : this.lampadas.entrySet()) {
            Set<Lampada> lampsDiv = entry.getValue();

            for (Lampada lamp : lampsDiv) {
                if (lamp.getId().equals(ident)) {
                    lampsDiv.remove(lamp);
                    return lamp.clone();
                }
            }
        }

        return null;
    }


    public LampadaLed maisEconomica() {
        return this.lampadas.values()
                     .stream()
                     .flatMap(Set :: stream) // transforma Stream<Set<Lampada>> -> Stream<Lampada>
                     .filter (l -> l instanceof LampadaLed)
                     .map(l -> (LampadaLed) l)
                     .min(Comparator.comparingDouble(LampadaLed :: getCustoTotal))
                     .orElse(null);
    }

}
