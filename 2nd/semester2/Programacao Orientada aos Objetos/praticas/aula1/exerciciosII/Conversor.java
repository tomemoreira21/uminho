package exerciciosII;

public class Conversor {

    public double celsiusParaFarenheit(double graus) {
        // °F = (°C × 9/5) + 32
        double vF = (graus * 1.8) + 32;
        return vF;
    }
}
