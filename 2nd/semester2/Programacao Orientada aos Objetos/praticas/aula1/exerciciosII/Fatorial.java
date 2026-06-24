package exerciciosII;

public class Fatorial {
    public long factorial (int num) {
        if (num <= 1) return 1;
        return num * factorial(num - 1);
    }

    public long tempoGasto() {
        long nanoAgora = System.nanoTime(); // para ter mais exatidão
        factorial(5000);
        long nanoFinal = System.nanoTime();

        return (long) ((nanoFinal - nanoAgora) / 1000000);
    }
}
