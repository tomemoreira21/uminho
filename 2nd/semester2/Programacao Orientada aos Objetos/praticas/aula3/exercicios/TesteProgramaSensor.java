public class TesteProgramaSensor {
    public static void main(String[] args) {

        Sensor s1 = new Sensor(); // começa a 0
        System.out.println("Valor inicial: " + s1.getPressao());

        boolean resultado1 = s1.setPressao(25.5);
        System.out.println("Atualização 25.5: " + resultado1);
        System.out.println("Valor atual: " + s1.getPressao());

        boolean resultado2 = s1.setPressao(-10);
        System.out.println("Atualização -10: " + resultado2);
        System.out.println("Valor final: " + s1.getPressao());
    }
}
