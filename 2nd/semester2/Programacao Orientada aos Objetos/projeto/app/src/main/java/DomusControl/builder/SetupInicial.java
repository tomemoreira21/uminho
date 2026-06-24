package DomusControl.builder;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.List;

import DomusControl.DomusControl;
import DomusControl.automation.*;
import DomusControl.automation.actions.abertura.Abrir;
import DomusControl.automation.actions.abertura.Fechar;
import DomusControl.automation.actions.generica.AcaoPorFiltro;
import DomusControl.automation.actions.onoff.Desligar;
import DomusControl.automation.actions.onoff.Ligar;
import DomusControl.automation.actions.onoff.lampada.AlterarLuminosidade;
import DomusControl.automation.conditions.CondicaoComparativaSensor;
import DomusControl.automation.conditions.CondicaoHorarioExato;
import DomusControl.automation.conditions.CondicaoHorarioIntervalo;
import DomusControl.automation.conditions.TipoComparacao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.device.ColunaSom;
import DomusControl.device.Cortina;
import DomusControl.device.DispositivoOnOff;
import DomusControl.device.Lampada;
import DomusControl.device.PortaoGaragem;
import DomusControl.device.SensorChuva;
import DomusControl.device.SensorLuminosidade;
import DomusControl.users.Utilizador;

 
public class SetupInicial {
     public static DomusControl criarEstado() throws Exception {
       
        DomusControl dc = new DomusControl();

        // USERS
        dc.addUtilizador("Diogo", "diogo@email.com");
        dc.addUtilizador("Ana", "ana@email.com");
        dc.addUtilizador("Rui", "rui@email.com");

        dc.addCasa("diogo@email.com", "CasaInteligente");
        dc.addCasa("ana@email.com","CasaSegura");
        dc.addCasa("rui@email.com", "CasaConforto");
        dc.addCasa("ana@email.com", "CasaVida");

        Utilizador diogo = dc.getUtilizador("diogo@email.com");
        Utilizador ana = dc.getUtilizador("ana@email.com");
        Utilizador rui = dc.getUtilizador("rui@email.com");

        // Casa1
        dc.executarNaCasa("CasaInteligente",
                          diogo.getEmail(),
                          (casa, u) -> {
                                casa.addDivisao(u,"Sala");
                                casa.addDivisao(u, "Quarto");
                                casa.addDivisao(u, "Cozinha");
                                casa.addDivisao(u, "Garagem");
                            }
                        );

        // dispositivos
        dc.executarNaCasa("CasaInteligente",
                         diogo.getEmail(), 
                         (casa,u) -> {
                            casa.addDispositivoADivisao(u, "Sala", new Lampada("L1","Philips","Hue",10));
                            casa.addDispositivoADivisao(u, "Sala", new ColunaSom("S1","Sony","X",15));
                            casa.addDispositivoADivisao(u, "Sala", new Cortina("C1", "Ikea", "Smart", 3, 0.05));
                            casa.addDispositivoADivisao(u, "Quarto", new Lampada("L2","LG","Warm",8));
                            casa.addDispositivoADivisao(u, "Quarto",new Cortina("C2","Ikea","Basic",2,0.05));
                            casa.addDispositivoADivisao(u, "Cozinha", new Lampada("L3","Philips","White",7));
                            casa.addDispositivoADivisao(u, "Garagem", new PortaoGaragem("P1","Somfy","AutoGate",5,0.05));
                         }
                    );


        // ESCALONAMENTO: abrir cortinas de manhã e o portão da garagem
        Automacao abrirManha = new AutomacaoEvento(
            new CondicaoHorarioExato(LocalTime.of(8,0)),
            List.of( 
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Cortina || d instanceof PortaoGaragem,
                    d -> new Abrir(d.getId())
            )),
            diogo
        );


        // ESCALONAMENTO: desligar tudo à noite
        Automacao desligarNoite = new AutomacaoEvento(
            new CondicaoHorarioExato(LocalTime.of(23,30)),
            List.of( 
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof DispositivoOnOff,
                    d -> new Desligar(d.getId())
            )),
            diogo
        );

        // CENÁRIO: ver cinema apenas na sala -> liga as luzes com intensidade fraca e liga a coluna
        Cenario verCinema = new Cenario(
            "Ver Cinema", 
            List.of(
            new AcaoPorFiltro(
                (casa,d) -> d instanceof Lampada && casa.dispositivoPertenceDivisao("Sala", d), 
                d -> new Ligar(d.getId())
            ),
            new AcaoPorFiltro(
                (casa,d) -> d instanceof Lampada && casa.dispositivoPertenceDivisao("Sala", d),
                d -> new AlterarLuminosidade(d.getId(), 10)),
            new AcaoPorFiltro(
                (casa,d) -> d instanceof ColunaSom && casa.dispositivoPertenceDivisao("Sala", d),
                d -> new Ligar(d.getId())))
            , diogo);

        dc.executarNaCasa("CasaInteligente", 
                casa -> {
                    casa.addAutomacao(abrirManha);
                    casa.addAutomacao(desligarNoite);
                    casa.addCenario(verCinema);
                }
        );
      
        // Casa2
        dc.executarNaCasa("CasaSegura", ana.getEmail(), (casa, u) -> {
                casa.addDivisao(u, "Sala");
                casa.addDivisao(u, "Quarto");

                casa.addDispositivoADivisao(u, "Sala", new Lampada("L4","Philips","Hue",10));
                casa.addDispositivoADivisao(u, "Sala", new Cortina("C3","Ikea","Smart",2,0.03));
                casa.addDispositivoADivisao(u, "Quarto", new Lampada("L5","LG","Warm",8));
                casa.addDispositivoADivisao(u, "Quarto", new Cortina("C4","Ikea","Basic",2,0.03));
            });

        // Sensores
        dc.executarNaCasa("CasaSegura", ana.getEmail(), (casa, u) -> {
            SensorChuva chuva = new SensorChuva("SC1","Netatmo","Rain",2);
            SensorLuminosidade luz = new SensorLuminosidade("SL1","Netatmo","Light",2);

            chuva.setValor(30);  // está a chover
            luz.setValor(20); // pouca luz

            casa.addDispositivo(u,chuva);
            casa.addDispositivo(u,luz); 

            // Cortinas começam abertas (necessário para verificar o sensor chuva)
            casa.atuarDispositivo(u, new Abrir("C3"));
            casa.atuarDispositivo(u, new Abrir("C4"));
        });

        // Automação: FECHAR cortinas se chover
        List<AcaoComInversa> acoesFechar =  List.of(new AcaoPorFiltro((casa,d) -> d instanceof Cortina, d -> new Fechar(d.getId())));

        Automacao fecharCortinasChuva = new AutomacaoEstado(
            new CondicaoComparativaSensor("SC1", 0.0, TipoComparacao.MAIOR),
            acoesFechar,
            ana
        );

        // Automação: LIGAR luzes se pouca luminosidade
        List<AcaoComInversa> acoesLigar = List.of(new AcaoPorFiltro((casa,d) -> d instanceof Lampada, d -> new Ligar(d.getId())));

        Automacao luzAutomatica = new AutomacaoEstado(
            new CondicaoComparativaSensor("SL1", 50.0, TipoComparacao.MENOR),
            acoesLigar,
            ana
        );

        dc.executarNaCasa("CasaSegura",
                    casa -> {
                        casa.addAutomacao(fecharCortinasChuva);
                        casa.addAutomacao(luzAutomatica);
                    }
        );

        // Casa3
        dc.executarNaCasa("CasaConforto", rui.getEmail(), (casa,u) -> {
            casa.addDivisao(u, "Sala");
            casa.addDivisao(u,"Quarto");

            casa.addDispositivoADivisao(u, "Sala", new Lampada("L6","Philips","Warm",9));
            casa.addDispositivoADivisao(u, "Sala", new ColunaSom("S3","JBL","Boom",20));
            casa.addDispositivoADivisao(u, "Sala", new Cortina("C5","Ikea","Smart",3,0.04));
            casa.addDispositivoADivisao(u, "Quarto", new Lampada("L7","Xiaomi","Soft",7));
            casa.addDispositivoADivisao(u, "Quarto", new Cortina("C6","Ikea","Basic",2,0.04));
            }
        );

        // Escalonamento: 20:00 - 23:00 ligar as luzes da sala
        List<AcaoComInversa> ligarLuzesSala = List.of(
            new AcaoPorFiltro(
                (casa,d) -> d instanceof Lampada && casa.dispositivoPertenceDivisao("Sala", d),
                d -> new Ligar(d.getId())
            )
        );

        Automacao noite = new AutomacaoEstado(
            new CondicaoHorarioIntervalo(LocalTime.of(20,0), LocalTime.of(23,0)),
            ligarLuzesSala,
            rui
        );


       // Escalonamento: 08:00 abrir a cortina do quarto
        Automacao abrirCortinasManha = new AutomacaoEvento(
            new CondicaoHorarioExato(LocalTime.of(8,0)),
            List.of( 
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Cortina && casa.dispositivoPertenceDivisao("Quarto", d),
                    d -> new Abrir(d.getId())
            )),
            rui
        );

        dc.executarNaCasa("CasaConforto", 
            casa -> {
                casa.addAutomacao(noite);
                casa.addAutomacao(abrirCortinasManha);
            }
        );

        // Casa4
        dc.executarNaCasa("CasaVida", ana.getEmail(), (casa,u) -> {
            casa.addDivisao(u,"Sala");
            casa.addDivisao(u, "Quarto");
            casa.addDivisao(u, "Cozinha");
            casa.addDivisao(u, "Garagem");
            casa.addDivisao(u, "Jardim");

            casa.addDispositivoADivisao(u, "Sala", new Lampada("L8","Philips","Hue",10));
            casa.addDispositivoADivisao(u, "Sala", new ColunaSom("S4","JBL","Party",20));
            casa.addDispositivoADivisao(u, "Sala", new Cortina("C7","Ikea","Smart",3,0.04));
            casa.addDispositivoADivisao(u, "Quarto", new Lampada("L9","Xiaomi","Soft",7));
            casa.addDispositivoADivisao(u, "Quarto", new Cortina("C8","Ikea","Basic",2,0.04));
            casa.addDispositivoADivisao(u, "Cozinha", new Lampada("L10","Philips","White",8));
            casa.addDispositivoADivisao(u, "Garagem", new PortaoGaragem("P2","Somfy","AutoGate",5,0.05));
            }
        );

        // Simulação de uma semana: feito para o analisar detetar padrões
        dc.executarNaCasa("CasaVida", ana.getEmail(), (casa, u) -> {
            casa.setTempoAtual(LocalDateTime.of(2025,1,1,0,0));

            for (int dia = 1; dia <= 7; dia++) {
                // 08:00
                casa.avancarTempo(Duration.ofHours(8));
                casa.atuarDispositivo(u, new Abrir("C8")); // cortina quarto
                casa.atuarDispositivo(u, new Ligar("L9")); // luz quarto

                // 13:00 
                casa.avancarTempo(Duration.ofHours(5));
                casa.atuarDispositivo(u, new Ligar("L8"));
                casa.atuarDispositivo(u, new Ligar("S4"));

                // 20:00
                casa.avancarTempo(Duration.ofHours(7));
                casa.atuarDispositivo(u, new Desligar("L8"));
                casa.atuarDispositivo(u, new Desligar("S4"));

                 // 23:00
                casa.avancarTempo(Duration.ofHours(3));
                casa.atuarDispositivo(u, new Desligar("L9"));
                casa.atuarDispositivo(u, new Fechar("C8"));

                // 00:00 → próximo dia
                casa.avancarTempo(Duration.ofHours(1));
            }
        });

        // Cenário: sair de casa vai desligar luzes,som,fehcar cortinas e fechar portao
        Cenario sairCasa = new Cenario(
            "Sair de Casa",
            List.of(
                new AcaoPorFiltro((casa,d) -> d instanceof Lampada, d -> new Desligar(d.getId())),
                new AcaoPorFiltro((casa,d) -> d instanceof ColunaSom, d -> new Desligar(d.getId())),
                new AcaoPorFiltro((casa,d) -> d instanceof Cortina, d -> new Fechar(d.getId())),
                new AcaoPorFiltro((casa,d) -> d instanceof PortaoGaragem, d -> new Fechar(d.getId()))
            ),
            ana
        );

        // Cenário: jantar com amigos baixar as luzes, ligar coluna e fechar cortinas
        Cenario jantarAmigos = new Cenario(
            "Jantar com Amigos",
            List.of(
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Lampada && casa.dispositivoPertenceDivisao("Sala", d),
                    d -> new AlterarLuminosidade(d.getId(), 30)
                ),
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof ColunaSom,
                    d -> new Ligar(d.getId())
                ),
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Cortina,
                    d -> new Fechar(d.getId())
                )
            ),
            ana
        );

        // Cenário: deitar vai apagar tudo
        Cenario deitar = new Cenario(
            "Deitar",
            List.of(
                new AcaoPorFiltro((casa,d) -> d instanceof Lampada, d -> new Desligar(d.getId())),
                new AcaoPorFiltro((casa,d) -> d instanceof ColunaSom, d -> new Desligar(d.getId())),
                new AcaoPorFiltro((casa,d) -> d instanceof Cortina, d -> new Fechar(d.getId()))
            ),
            ana
        );

        // Cenário: acordar vai abrir cortinas, ligar luz do quarto e ligar musica
        Cenario acordar = new Cenario(
            "Acordar",
            List.of(
                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Cortina,
                    d -> new Abrir(d.getId())
                ),

                new AcaoPorFiltro(
                    (casa,d) -> d instanceof Lampada && casa.dispositivoPertenceDivisao("Quarto", d),
                    d -> new Ligar(d.getId())
                ),

                new AcaoPorFiltro(
                    (casa,d) -> d instanceof ColunaSom,
                    d -> new Ligar(d.getId())
                )
            ),
            ana
        );

         dc.executarNaCasa("CasaVida", 
            casa -> {
                casa.addCenario(acordar);
                casa.addCenario(jantarAmigos);
                casa.addCenario(deitar);
                casa.addCenario(sairCasa);
            }
        );

        return dc;
     }

}
