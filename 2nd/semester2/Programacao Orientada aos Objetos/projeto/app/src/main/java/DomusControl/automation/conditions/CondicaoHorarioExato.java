package DomusControl.automation.conditions;

import java.time.LocalTime;

import DomusControl.home.Casa;

public class CondicaoHorarioExato implements CondicaoTemporal {
    private LocalTime hora;

    public CondicaoHorarioExato(LocalTime hora) {
        this.hora = hora;
    }

    public LocalTime getHora() {
        return hora;
    }

    public boolean verificar(Casa casa) {
        LocalTime agora = casa.getTempoAtual().toLocalTime();

        return agora.getHour() == hora.getHour() && 
               agora.getMinute() == hora.getMinute();
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        CondicaoHorarioExato c = (CondicaoHorarioExato)o;
        return c.getHora().equals(this.hora);
    }

    public String toString() {
        return "Às " + this.hora;
    }
}
