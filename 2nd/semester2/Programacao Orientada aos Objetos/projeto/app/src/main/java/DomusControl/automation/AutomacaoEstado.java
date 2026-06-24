package DomusControl.automation;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.core.Condicao;
import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;
import DomusControl.users.Utilizador;

/*
Destinada para automações de estado, ou seja, para automações que envolvem transições

Mudanças de estado
*/
public class AutomacaoEstado extends Automacao {
    private List<Acao> acoesInativo; // acoes necessários para executar após a condição ser false

    private boolean estadoAtual = false; // resultado da condição na última verificacao 

    public AutomacaoEstado(Condicao condicao,List<Acao> acoesAtivo,List<Acao> acoesInativo,Utilizador user) {
        super(condicao, acoesAtivo, user);
        this.acoesInativo = new ArrayList<>(acoesInativo);
    }

    public AutomacaoEstado(Condicao condicao,List<? extends AcaoComInversa> acoesAtivo, Utilizador user) {
        super(condicao, acoesAtivo,  user);
        this.acoesInativo = acoesAtivo.stream()
                                      .map(AcaoComInversa :: inversa)
                                      .collect(Collectors.toList());
    }

    public AutomacaoEstado() {
        super();
        this.acoesInativo = new ArrayList<>();
    }

    public AutomacaoEstado(AutomacaoEstado a) {
        super(a);
        this.acoesInativo = a.getAcoesInativo();
    }

    public List<Acao> getAcoesInativo() {
        return this.acoesInativo.stream().collect(Collectors.toList());
    }

    public void setAcoesInativo(List<Acao> acoesInativo) {
        this.acoesInativo = new ArrayList<>(acoesInativo);
    }

    public boolean getEstadoAtual() {
        return estadoAtual;
    }

    public void setEstadoAtual(boolean estadoAtual) {
        this.estadoAtual = estadoAtual;
    }

    public AutomacaoEstado clone() {
        return new AutomacaoEstado(this);
    }

    @Override
    public void avaliarAutomacao(Casa casa) throws DomusControlException {
        if (super.getCondicao() == null) return;

        boolean novoEstado = super.getCondicao().verificar(casa);

        // OFF -> ON
        if (novoEstado && !estadoAtual) {
            for (Acao a : super.getAcoes()) {
                a.executar(casa);
            }
        }

        // ON -> OFF
        if (!novoEstado && estadoAtual && !acoesInativo.isEmpty()) {
            for (Acao a : acoesInativo) {
                a.executar(casa);
            }
        }

        estadoAtual = novoEstado;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        AutomacaoEstado a = (AutomacaoEstado) o;
        return super.equals(a) &&
               a.getAcoesInativo().equals(this.acoesInativo) &&
               a.getEstadoAtual() == this.estadoAtual;
    }

    public String toString() {
        return super.toString() + ", acoesInativo = " + this.acoesInativo + ", estadoAtual = " + this.estadoAtual;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), this.acoesInativo,this.estadoAtual);
    }


}
