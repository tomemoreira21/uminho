import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class CasaInteligente {
    private List<Lampada> lampadas;

    public CasaInteligente(List<Lampada> lampadas) {
        this.setLampadas(lampadas);
    }

    public CasaInteligente(CasaInteligente ci) {
        this.lampadas = ci.getLampadas();
    }

    public CasaInteligente() {
        this.lampadas = new ArrayList<Lampada>();
    }

    public List<Lampada> getLampadas() {
        ArrayList<Lampada> lampadasNovas = new ArrayList<>(this.lampadas.size());

        for (Lampada lampada : this.lampadas) {
            lampadasNovas.add(lampada.clone());
        }

        return lampadasNovas;
    }

    public void setLampadas(List<Lampada> l) {
        ArrayList<Lampada> lampadasNovas = new ArrayList<>(l.size());

        for (Lampada lampada : this.lampadas) {
            lampadasNovas.add(lampada.clone());
        }

        this.lampadas = lampadasNovas;        
    }

    public void addLampada(Lampada l) {
        this.lampadas.add(l.clone());
    }

    public void ligaLampadaNormal(int index) {
        Lampada l = this.lampadas.get(index);
        l.lampON();
    }

    public void ligaLampadaEco(int index) {
        Lampada l = this.lampadas.get(index);
        l.lampECO();
    }

    public int qtEmEco() {
        return (int)this.lampadas.stream().filter(l -> l.onECOMode()).count();
    }

    public void removeLampada(int index) {
        this.lampadas.remove(index);
    }


    public void ligaTodasEco() {
        this.lampadas.forEach(l -> l.lampECO());
    }

    public void ligaTodasMax() {
        this.lampadas.forEach(l -> l.lampON());
    }   

    public double consumoTotal() {
        return this.lampadas.stream()
                .mapToDouble(l -> l.getCustoTotal())
                .sum();
    }

    public Lampada maisGastadora() {
        double custoMax = 0;
        Lampada maisGasta = null;

        for (Lampada l : this.lampadas) {
            if (l.getCustoTotal() > custoMax) {
                custoMax = l.getCustoTotal();
                maisGasta = new Lampada(l);
            }
        }

        return maisGasta;
    }

    public Set<Lampada> lampadasEmModoEco() {
        return this.lampadas.stream().filter(Lampada :: onECOMode)
                            .map(Lampada :: clone)
                            .collect(Collectors.toSet());
    }

    public void reset() {
        this.lampadas.forEach(l -> l.setUpdate(0));
    }

    // considerado que as lampadas mais economicas têm um custo total menor
    public Set<Lampada> podiumEconomia() {
        Set<Lampada> lampadasTop = new HashSet<>(3);
        List<Lampada> listaLampadas = this.getLampadas();
        
        Lampada min = null;

        for (int i = 0; i < 3; i++) {
            for (Lampada l : listaLampadas) {
                if (min == null || (l.getCustoTotal() < min.getCustoTotal())) {
                    min = l;
                }
            }

            lampadasTop.add(min.clone());

            listaLampadas.remove(min);
            min = null;
        }

        return lampadasTop;
    }


    public CasaInteligente clone() {
        return new CasaInteligente(this);
    }

    public String toString() {
        String out = "";
        int inc = 0;

        for (Lampada l : this.lampadas) {
            out += ("Lampada " + inc + ": " + l.toString() + "\n");
            inc++;
        }

        return out;
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CasaInteligente c = (CasaInteligente) o;
        return c.getLampadas().equals(this.lampadas);
    }

}
