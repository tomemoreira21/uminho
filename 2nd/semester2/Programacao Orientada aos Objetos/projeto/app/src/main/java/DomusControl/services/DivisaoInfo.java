package DomusControl.services;

import DomusControl.exceptions.DomusControlException;
import DomusControl.home.Casa;

public class DivisaoInfo {
    private String nomeCasa;
    private String nomeDivisao;
    private int numDispositivos;

    public DivisaoInfo(Casa casa, String nomeDiv) throws DomusControlException {
        this.nomeCasa =  casa.getNome();
        this.nomeDivisao = nomeDiv;
        this.numDispositivos = casa.getNumDispositivosDiv(nomeDiv);
    }

    public String getCasa() {
        return this.nomeCasa;
    }

    public String getNomeDivisao() {
        return this.nomeDivisao;
    }

    public int getNumDispositivos() {
        return this.numDispositivos;
    }

    public String toString() {
        return "casa = " + this.nomeCasa + ", divisao = " + this.nomeDivisao + ", numDispositivos = " + this.numDispositivos;
    }
}     

