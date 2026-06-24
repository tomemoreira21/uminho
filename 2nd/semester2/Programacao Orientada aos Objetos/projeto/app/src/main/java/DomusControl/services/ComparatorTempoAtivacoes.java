package DomusControl.services;

import java.util.Comparator;

import DomusControl.device.Dispositivo;

public class ComparatorTempoAtivacoes implements Comparator <Dispositivo>{
    
    public int compare(Dispositivo d1, Dispositivo d2) {
        double tempoAtivo1 = d1.getTempoAtivo();
        double tempoAtivo2 = d2.getTempoAtivo();

        if (tempoAtivo1 > tempoAtivo2) return -1;
        if (tempoAtivo1 < tempoAtivo2) return 1;
        
        return Integer.compare(d2.getNumAtivacoes(),d1.getNumAtivacoes());
    }
}