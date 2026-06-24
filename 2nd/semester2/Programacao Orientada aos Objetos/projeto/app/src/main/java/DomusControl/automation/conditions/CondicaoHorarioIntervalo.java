package DomusControl.automation.conditions;

import DomusControl.home.Casa;

import java.time.LocalTime;

public class CondicaoHorarioIntervalo implements CondicaoTemporal {
    private LocalTime inicio;
    private LocalTime fim;

    public CondicaoHorarioIntervalo(LocalTime inicio, LocalTime fim) {
        this.inicio = inicio;
        this.fim = fim;
    }

    public LocalTime getInicio() {
        return inicio;
    }

    public LocalTime getFim() {
        return fim;
    }

    @Override
    public boolean verificar(Casa casa) {
        LocalTime agora = casa.getTempoAtual().toLocalTime();
        
        // Verifica se estamos no intervalo [inicio, fim]
        return !agora.isBefore(inicio) && !agora.isAfter(fim);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CondicaoHorarioIntervalo c = (CondicaoHorarioIntervalo)o;
        return c.getInicio().equals(this.inicio) &&
               c.getFim().equals(this.fim);
    }

    public String toString() {
        return "Entre " + inicio + " e " + fim;
    }
}