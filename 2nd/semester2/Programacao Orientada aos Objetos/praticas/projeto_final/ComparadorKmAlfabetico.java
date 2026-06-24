import java.util.Comparator;

public class ComparadorKmAlfabetico implements Comparator<Carro> {

    @Override
    // ordena de forma decrescente de kms, em caso de empate vai ver a matricula
    public int compare(Carro c1,Carro c2) {
        int res = Double.compare(c2.getNumeroKms(), c1.getNumeroKms()); 

        if (res == 0) {
            res = c1.getId().compareTo(c2.getId());
        }

        return res;
    }
    
}
