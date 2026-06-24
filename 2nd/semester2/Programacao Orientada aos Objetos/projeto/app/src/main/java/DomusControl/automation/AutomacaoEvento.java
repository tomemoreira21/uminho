package DomusControl.automation;

import java.time.LocalDate;
import java.util.List;
import java.util.Objects;

import DomusControl.automation.core.Acao;
import DomusControl.automation.core.Condicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;
import DomusControl.users.Utilizador;

/*
Automações de Eventos, por exemplo:
Numa determinada hora e minute, ligar a lampada
*/
public class AutomacaoEvento extends Automacao {
    private LocalDate ultimoDiaExecutado;

    public AutomacaoEvento(Condicao condicao, List<Acao> acoes, Utilizador user) {
        super(condicao, acoes, user);
        this.ultimoDiaExecutado = null;
    }

    public AutomacaoEvento() {
        super();
        this.ultimoDiaExecutado = null;
    }

    public AutomacaoEvento(AutomacaoEvento a) {
        super(a);
        this.ultimoDiaExecutado = a.getUltimoDiaExecutado();
    }

    public LocalDate getUltimoDiaExecutado() {
        return ultimoDiaExecutado;
    }

    public void setUltimoDiaExecutado(LocalDate ultimoDiaExecutado) {
        this.ultimoDiaExecutado = ultimoDiaExecutado;
    }

    @Override
    public void avaliarAutomacao(Casa casa) throws DomusControlException {
        if (super.getCondicao() == null) return;

        boolean ativa = getCondicao().verificar(casa);
        LocalDate hoje = casa.getTempoAtual().toLocalDate();

        if (ativa && (ultimoDiaExecutado == null || !ultimoDiaExecutado.equals(hoje))) {

            for (Acao a : getAcoes()) {
                a.executar(casa);
            }

            ultimoDiaExecutado = hoje;
        }
    }

    public AutomacaoEvento clone() {
        return new AutomacaoEvento(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AutomacaoEvento a = (AutomacaoEvento) o;
        return super.equals(a) &&
               a.getUltimoDiaExecutado().equals(this.ultimoDiaExecutado);
    }

    public String toString() {
        return super.toString() + ", ultimoDiaExecutado = " + this.ultimoDiaExecutado;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), this.ultimoDiaExecutado);
    }

}
