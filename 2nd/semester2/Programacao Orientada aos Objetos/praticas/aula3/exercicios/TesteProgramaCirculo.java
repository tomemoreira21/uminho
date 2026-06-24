public class TesteProgramaCirculo {
    public static void main (String[] args) {
        Circulo c1 = new Circulo();
        Circulo c2 = new Circulo(5,6,2);

        System.out.println(c1.toString());
        System.out.println(c2.toString());

        c1.alteraCentro(2, 3);
        System.out.println(c1.toString());

        System.out.format ("Área: %.2f\n",c2.calculaArea());
        System.out.format ("Perímetro: %.2f\n",c1.calculaPerimetro());
    }
}
