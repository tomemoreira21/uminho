import java.util.Comparator;

class ComparadorPorValorDescrescente implements Comparator<Encomenda> {
    @Override
    public int compare(Encomenda e1,Encomenda e2) {
        int res;
        double valorEnc1 = e1.calculaValorTotal();
        double valorEnc2 = e2.calculaValorTotal();

        if (valorEnc1 == valorEnc2) {
            res = 0;
        } else if (valorEnc1 > valorEnc2) {
            res = -1;
        } else {
            res = 1;
        }

        return res;
    }   
}

