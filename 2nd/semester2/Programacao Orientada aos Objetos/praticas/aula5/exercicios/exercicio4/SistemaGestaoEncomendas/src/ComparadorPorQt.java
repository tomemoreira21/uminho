import java.util.Comparator;

class ComparadorPorQt implements Comparator<Encomenda> {
    @Override
    public int compare(Encomenda e1,Encomenda e2) {
        return e1.numeroTotalProdutos() - e2.numeroTotalProdutos();
    }
}
