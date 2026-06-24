
public class TesteProgramaFutebol {
    public static void main (String[] args) {
        Futebol f = new Futebol("FC Porto", "SC Benfica",Futebol.Estado.PorIniciar , 0, 0);

        f.startGame();
        f.goloVisitado();
        f.goloVisitado();
        f.goloVisitado();
        f.goloVisitante();
        f.endGame();

        System.out.println(f.resultadoActual());
        
        // tenta marcar golos após terminar o jogo
        f.goloVisitado();
        f.goloVisitante();
        System.out.println(f.resultadoActual());
    }
}
