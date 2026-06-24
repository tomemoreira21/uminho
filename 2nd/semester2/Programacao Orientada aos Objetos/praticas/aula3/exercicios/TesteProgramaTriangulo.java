public class TesteProgramaTriangulo {
    public static void main (String[] args) {
        Ponto p1 = new Ponto(3, 0);
        Ponto p2 = new Ponto(-3, 0);
        Ponto p3 = new Ponto(0, 3);
        Triangulo t = new Triangulo(p1, p2, p3);

        System.out.println("---------------- Triângulo ---------------");
        System.out.println(t.toString());

        System.out.format("\nÁrea: %.2f\n",t.calculaAreaTriangulo());
        System.out.format("Perímetro: %.2f\n",t.calculaPerimetroTriangulo());
        System.out.format("Altura: %.2f\n",t.calculaAltura());
    }
}
