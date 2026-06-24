    package DomusControl.analysis;

    import java.io.Serializable;
    import java.time.LocalDateTime;
    import java.time.LocalTime;
    import java.util.Objects;

    import DomusControl.automation.actions.TipoAcao;

    //agregação
    public class Padrao implements Serializable {
        private LocalTime horaAprox; // arredondada para baixo
        private TipoAcao tipoDeAcao;
        private String idDispositivo;
        private String emailUtilizador;
        
        private static int intervaloMinutos = 5;

        public static int getIntervaloMinutos() {
            return Padrao.intervaloMinutos;
        }

        public static void setIntervaloMinutos(int min) {
            Padrao.intervaloMinutos = min;
        }

        public Padrao(LocalDateTime hora, TipoAcao tipo, String dispositivo, String emailUtilizador) {
            this.horaAprox = this.arredondarParaIntervalo(hora);
            this.tipoDeAcao = tipo;
            this.idDispositivo = dispositivo;
            this.emailUtilizador = emailUtilizador;
        }

        public Padrao(Padrao p) {
            this.horaAprox = p.getHoraAprox();
            this.tipoDeAcao = p.getTipoDeAcao();
            this.idDispositivo = p.getIdDispositivo();
            this.emailUtilizador = p.getEmailUtilizador();
        }

        // Arredonda para baixo: 14:47 -> 14:40, 09:12 -> 09:10
        private LocalTime arredondarParaIntervalo(LocalDateTime t) { // é estático pq n depende do obj padrao
            int intervalo = Padrao.getIntervaloMinutos();
            int minutos = (t.getMinute() / intervalo) * intervalo;
            return t.withMinute(minutos).withSecond(0).withNano(0).toLocalTime();
        }

        public LocalTime getHoraAprox() {
            return this.horaAprox;
        }

        public TipoAcao getTipoDeAcao() {
            return this.tipoDeAcao;
        }

        public String getIdDispositivo() {
            return this.idDispositivo;
        }

        public String getEmailUtilizador() {
            return this.emailUtilizador;
        }

        public Padrao clone() {
            return new Padrao(this);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;

            if (o == null || this.getClass() != o.getClass()) return false;

            Padrao p = (Padrao) o;
            return this.horaAprox.equals(p.getHoraAprox()) 
                && this.tipoDeAcao == p.getTipoDeAcao()
                && this.idDispositivo.equals(p.getIdDispositivo())
                && this.emailUtilizador.equals(p.getEmailUtilizador());
        }

        @Override 
        public int hashCode() {
            return Objects.hash(this.horaAprox, this.tipoDeAcao, this.idDispositivo, this.emailUtilizador);
        }

        public String toString() {
            return "Padrao{" +
                "hora=" + this.horaAprox +
                ", acao=" + this.tipoDeAcao +
                ", dispositivo=" + this.idDispositivo +
                ", utilizador=" + this.emailUtilizador +
                '}';
        }
    }