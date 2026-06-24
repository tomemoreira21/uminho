package DomusControl.ui;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/*********************************************************************************/
/** DISCLAIMER: Este código foi criado e alterado durante as aulas práticas      */
/** de POO. Representa uma solução em construção, com base na matéria leccionada */ 
/** até ao momento da sua elaboração, e resulta da discussão e experimentação    */
/** durante as aulas. Como tal, não deverá ser visto como uma solução canónica,  */
/** ou mesmo acabada. É disponibilizado para auxiliar o processo de estudo.      */
/** Os alunos são encorajados a testar adequadamente o código fornecido e a      */
/** procurar soluções alternativas, à medida que forem adquirindo mais           */
/** conhecimentos de POO.                                                        */
/*********************************************************************************/


import java.util.Scanner;
import java.util.Set;
import java.util.function.Predicate;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.Duration;
import java.time.LocalDateTime;

import DomusControl.DomusControl;
import DomusControl.automation.Automacao;
import DomusControl.automation.Cenario;
import DomusControl.automation.actions.generica.AcaoPorFiltro;
import DomusControl.automation.core.Acao;
import DomusControl.automation.core.AcaoComInversa;
import DomusControl.automation.interfaces_genericas.FiltroDispositivo;
import DomusControl.device.ColunaSom;
import DomusControl.device.Cortina;
import DomusControl.device.Dispositivo;
import DomusControl.device.DispositivoAbertura;
import DomusControl.device.DispositivoMedicao;
import DomusControl.device.Lampada;
import DomusControl.device.PortaoGaragem;
import DomusControl.device.Rele;
import DomusControl.device.SensorChuva;
import DomusControl.device.SensorLuminosidade;
import DomusControl.exceptions.DomusControlException;
import DomusControl.exceptions.casa.AcessoNegadoException;
import DomusControl.exceptions.casa.CasaJaExisteException;
import DomusControl.exceptions.casa.CasaNaoExisteException;
import DomusControl.exceptions.casa.CenarioInexistenteException;
import DomusControl.exceptions.casa.DivisaoInexistenteException;
import DomusControl.exceptions.casa.DivisaoJaExisteException;
import DomusControl.exceptions.casa.UtilizadorJaExisteExecption;
import DomusControl.exceptions.casa.UtilizadorNaoExisteException;
import DomusControl.exceptions.dispositivo.AberturaInvalidaException;
import DomusControl.exceptions.dispositivo.AcaoNaoReversivelException;
import DomusControl.exceptions.dispositivo.CorInvalidadeException;
import DomusControl.exceptions.dispositivo.DispositivoJaExisteException;
import DomusControl.exceptions.dispositivo.DispositivoNaoESensorException;
import DomusControl.exceptions.dispositivo.DispositivoNaoExisteException;
import DomusControl.exceptions.dispositivo.IntensidadeInvalidaException;
import DomusControl.exceptions.dispositivo.TipoDispositivoInvalidoException;
import DomusControl.exceptions.dispositivo.VolumeInvalidoException;
import DomusControl.home.Casa;
import DomusControl.users.Papel;
import DomusControl.users.Utilizador;

public class TextUI {
  private SistemaController controller;
  private Scanner sc;

  /**
   * Construtor que cria os menus e o model
   */

  public TextUI() {
    sc = new Scanner(System.in);

    try {
        this.controller = new SistemaController();
        System.out.println("Estado carregado com sucesso");

    } catch (FileNotFoundException e) {
        System.out.println("Nenhum estado anterior encontrado. A iniciar novo sistema.");
        this.controller = new SistemaController(new DomusControl());

    } catch (ClassNotFoundException e) {
        System.out.println("Erro de compatibilidade ao carregar o estado.");
        this.controller = new SistemaController(new DomusControl());

    } catch (IOException e) {
            System.out.println("Erro ao ler o ficheiro de estado: " + e.getMessage());
        this.controller = new SistemaController(new DomusControl());
    }

  }
  
  
  /**
   * Método que executa o menu principal.
   * Coloca a interface em execução.
   */
  
  public void run() {
    menuInicial();
  }

  private void menuInicial() {
        NewMenu menu = new NewMenu(new String[] {
            "Criar utilizador",
            "Iniciar sessão",
        });

        menu.setPreCondition(2, () -> controller.getNumeroUtilizadores() > 0);

        menu.setHandler(1, () -> criarUtilizador());
        menu.setHandler(2, () -> { 
        login(); 
        if (controller.getEmailUtilizadorAtual() != null) {
            menuCasa();
        }
        });

        menu.run();

        // sair da aplicacao
        controller.logout();
        guardarEstado();
  }

  private void menuCasa() {
      NewMenu menu = new NewMenu(new String[] {
          "Criar casa",
          "Selecionar casa"
      });

      menu.setPreCondition(2, () -> controller.getNumeroCasas() > 0);

      menu.setHandler(1, () -> criarCasa());
      menu.setHandler(2, () -> {
        selecionarCasa();
        if (controller.getNomeCasaAtual() != null) {
            menuPrincipal();
        }
      });

      menu.run();

      // voltar menu principal
      controller.logout();
  }

  private void menuPrincipal() {
      NewMenu menu = new NewMenu(new String[] {
            "Gerir divisões",
            "Gerir dispositivos",
            "Gerir automações",
            "Gerir cenários",
            "Consultar dados",
            "Consultar sugestões de automações/escalonamentos",
            "Simulação temporal"
      });   

      menu.setHandler(1, () -> gestaoDivisoes());
      menu.setHandler(2, () -> menuDispositivos());
      menu.setHandler(3, () -> menuAutomacoes());
      menu.setHandler(4, () -> menuCenarios());
      menu.setHandler(5, () -> menuConsultas());
      menu.setHandler(6, () -> menuSugestoes());
      menu.setHandler(7, () -> avancaTempoCasa());

      menu.run();

      // sair da casa
      controller.sairCasa();
  }

  private void gestaoDivisoes() {
    NewMenu menuDivisoes = new NewMenu(new String[] {
      "Adicionar divisão",
      "Listar divisões"
     });

     menuDivisoes.setPreCondition(2, () -> controller.existem(casa -> casa.getDivisoes().size()));

     menuDivisoes.setHandler(1, () -> criarDivisao());
     menuDivisoes.setHandler(2, () -> listarDivisoes());

     menuDivisoes.run();
  }

  private void menuDispositivos() {
    NewMenu menuDispositivos = new NewMenu(new String[] {
      "Adicionar Dispositivo",
      "Selecionar Dispositivo",
      "Listar Dispositivos"
    });

    menuDispositivos.setPreCondition(2, () -> controller.existem(casa -> casa.getDispositivos().size()));
    menuDispositivos.setPreCondition(3, () -> controller.existem(casa -> casa.getDispositivos().size()));

    menuDispositivos.setHandler(1, () -> criacaoDispositivos());
    menuDispositivos.setHandler(2, () -> selecionarDispositivo());
    menuDispositivos.setHandler(3, () -> menuListarDispositivos());
    
    menuDispositivos.run();
  }

  private void menuConsultas() {
     NewMenu menu = new NewMenu(new String[] {
        "Casa com maior consumo",
        "Top 3 divisões com mais dispositivos",
        "Utilizador com mais casas (admin)",
        "Consumo médio por divisão (casa atual)",
        "Top 3 dispositivos mais usados (casa atual)"
    });

    menu.setHandler(1, () -> casaMaiorConsumo());
    menu.setHandler(2, () -> topDivisoes());
    menu.setHandler(3, () -> userMaisAdmin());
    menu.setHandler(4, () -> consumoPorDivisao());
    menu.setHandler(5, () -> topDispositivos());

    menu.run();
  }

  private void menuConsultaDispositivo() {
    NewMenu menu = new NewMenu(new String[] {
        "Listar dispositivo",
        "Executar uma ação",
    });

    menu.setHandler(1, () -> listarDispositivo());
    menu.setHandler(2, () -> executarAcaoSobreDispositivo());

    menu.run();

    controller.sairDispositivo();
  }

  private void menuSugestoes() {
    try {
        controller.analisarSugestoes();

        List<Automacao> sugestoes = controller.getSugestoesAutomacoes();

        if (sugestoes.isEmpty()) {
            System.out.println("Não existem sugestões.");
            return;
        }

         int i = 1;
            for (Automacao a : sugestoes) {
                System.out.println("\nSugestão " + i++);
                mostrarAutomacao(a);

                System.out.print("Aceitar? (s/n): ");
                String op = sc.nextLine();

                if (op.equalsIgnoreCase("s")) {
                    controller.adicionarAutomacao(a);
                    System.out.println("Adicionada.");
                } else {
                    System.out.println("Ignorada.");
                }
            }

            controller.limparSugestoes();

        } catch (UtilizadorNaoExisteException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não existe na casa");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
  }

    private void mostrarAutomacao(Automacao a) {
        System.out.println("Tipo: " + a.getClass().getSimpleName());
        System.out.println("Utilizador: " + a.getUtilizador().getNome());

        if (a.getCondicao() != null) {
            System.out.println("Condição: " + a.getCondicao());
        }

        System.out.println("Ações:");
        int i = 1;
        for (Acao acao : a.getAcoes()) {
            System.out.println("  " + (i++) + ". " + acao);
        }
    }

  private void listarDispositivo() {
     try {
        System.out.println(controller.getDispositivoAtual());

     } catch (DispositivoNaoExisteException e) {
        System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

    } catch (Exception e) {
        System.out.println("Erro ao listar dispositivo: " + e.getMessage());
    }
  }

  private void listarCenarios() {
    try {
        Map<String, Cenario> cenarios = controller.getCenarios();

        if (cenarios.isEmpty()) {
            System.out.println("Não existem cenários registados.");
            return;
        }

        System.out.println("\n=== Cenários da casa ===");

        int i = 1;
        for (Map.Entry<String,Cenario> c : cenarios.entrySet()) {
            System.out.println(i++ + " - " + c.getKey());
        }

    } catch (Exception e) {
        System.out.println("Erro: " + e.getMessage());
    }
}

  private void executarAcaoSobreDispositivo() {
    try {
        Dispositivo d = controller.getDispositivoAtual();

        if (d instanceof Lampada) {
            menuLampada();
        } 
        else if (d instanceof DispositivoAbertura) {
            menuAbertura();
        }
        else if (d instanceof DispositivoMedicao) {
            menuSensor();
        }
        else if (d instanceof ColunaSom) {
            menuColuna();
        } 
        else {
            menuOnOff();
        }
    
    } catch (DispositivoNaoExisteException e) {
        System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

    } catch (Exception e) {
        System.out.println("Erro ao executar ação: " + e.getMessage());
    }
  }

  private void menuOnOff() {
      NewMenu menu = new NewMenu(new String[] {
          "Ligar",
          "Desligar"
      });

      menu.setHandler(1, () -> ligarDispositivo());
      menu.setHandler(2, () -> desligarDispositivo());

      menu.run();
  }

  private void menuSensor() {
    NewMenu menu = new NewMenu(new String[] {
          "Ligar",
          "Desligar",
          "Alterar valor medido"
    });

    menu.setHandler(1, () -> ligarDispositivo());
    menu.setHandler(2, () -> desligarDispositivo());
    menu.setHandler(3, () -> alterarValorSensor());

    menu.run();
  }

  private void menuColuna() {
    NewMenu menu = new NewMenu(new String[] {
          "Ligar",
          "Desligar",
          "Alterar volume"
    });

    menu.setHandler(1, () -> ligarDispositivo());
    menu.setHandler(2, () -> desligarDispositivo());
    menu.setHandler(3, () -> alterarSomColuna());

    menu.run();
  }

  private void menuAbertura() {
    NewMenu menu = new NewMenu(new String[] {
          "Abrir totalmente",
          "Fechar totalmente",
          "Abrir com um grau de abertura"
    });

    menu.setHandler(1, () -> abrirDispositivo());
    menu.setHandler(2, () -> fecharDispositivo());
    menu.setHandler(3, () -> alterarValorAbertura());

    menu.run();
  }


  private void menuLampada() {
    NewMenu menu = new NewMenu(new String[] {
        "Ligar",
        "Desligar",
        "Alterar luminosidade",
        "Alterar cor"
    });

    menu.setHandler(1, () -> ligarDispositivo());
    menu.setHandler(2, () -> desligarDispositivo());
    menu.setHandler(3, () -> alterarLuminosidade());
    menu.setHandler(4, () -> alterarCor());

    menu.run();
  }


  private void menuListarDispositivos() {
    NewMenu menu = new NewMenu(new String[] {
        "Listar as lâmpadas",
        "Listar as colunas de som",
        "Listar as cortinas",
        "Listar os portões de garagem",
        "Listar os relé",
        "Listar os sensores de pluviosidade",
        "Listar os sensores de luminosidade",
        "Listar todos os dispositivos"
    });

    menu.setPreCondition(1, () -> existemDispositivosComFiltro(d -> d instanceof Lampada));
    menu.setPreCondition(2, () -> existemDispositivosComFiltro(d -> d instanceof ColunaSom));
    menu.setPreCondition(3, () -> existemDispositivosComFiltro(d -> d instanceof Cortina));
    menu.setPreCondition(4, () -> existemDispositivosComFiltro(d -> d instanceof PortaoGaragem));
    menu.setPreCondition(5, () -> existemDispositivosComFiltro(d -> d instanceof Rele));
    menu.setPreCondition(6, () -> existemDispositivosComFiltro(d -> d instanceof SensorChuva));
    menu.setPreCondition(7, () -> existemDispositivosComFiltro(d -> d instanceof SensorLuminosidade));
    menu.setPreCondition(8, () -> existemDispositivosComFiltro(d -> true));

    menu.setHandler(1, () -> listarComFiltro((casa,d) -> d instanceof Lampada));
    menu.setHandler(2, () -> listarComFiltro((casa,d) -> d instanceof ColunaSom));
    menu.setHandler(3, () -> listarComFiltro((casa,d) -> d instanceof Cortina));
    menu.setHandler(4, () -> listarComFiltro((casa,d) -> d instanceof PortaoGaragem));
    menu.setHandler(5, () -> listarComFiltro((casa,d) -> d instanceof Rele));
    menu.setHandler(6, () -> listarComFiltro((casa,d) -> d instanceof SensorChuva));
    menu.setHandler(7, () -> listarComFiltro((casa,d) -> d instanceof SensorLuminosidade));
    menu.setHandler(8, () -> listarComFiltro((casa,d) -> true));

    menu.run();
  }

  private void menuAutomacoes() {
    NewMenu menu = new NewMenu(new String[] {
        "Criar automação por sensor",
        "Criar escalonamento por horário exato",
        "Criar escalonamento por intervalo",
        "Listar automações e escalonamentos"
    });

    menu.setPreCondition(1, () -> existemDispositivosComFiltro(d -> d instanceof DispositivoMedicao));
    menu.setPreCondition(4, () -> controller.existem(casa -> casa.getAutomacoes().size()));

    menu.setHandler(1, () -> criaAutomacaoPorSensor());
    menu.setHandler(2, () -> criaAutomacaoPorHorario());
    menu.setHandler(3, () -> criaAutomacaoPorIntervalo());
    menu.setHandler(4, () -> listarAutomacoes());

    menu.run();
  }

  private void menuCenarios() {
    NewMenu menu = new NewMenu(new String[] {
        "Criar cenário",
        "Listar cenários",
        "Executar cenários"
    });

    menu.setPreCondition(2, () -> controller.existem(casa -> casa.getCenarios().size()));
    menu.setPreCondition(3, () -> controller.existem(casa -> casa.getCenarios().size()));

    menu.setHandler(1, () -> criaCenario());
    menu.setHandler(2, () -> listarCenarios());
    menu.setHandler(3, () -> executarCenario());

    menu.run();
  }

  private void avancaTempoCasa() {
    try {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

        LocalDateTime antes = controller.getTempoCasaAtual();
        System.out.println("Tempo atual da casa: " + antes.format(formatter));

        Duration d = lerDuracao();
        controller.avancaTempoLocal(d);

        LocalDateTime depois = controller.getTempoCasaAtual();
        System.out.println("Novo tempo da casa: " + depois.format(formatter));
        System.out.println("Automações temporais foram avaliadas automaticamente.");
    
    } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

    } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

    } catch (Exception e) {
        System.out.println("Erro: " + e.getMessage());
    }
  }

  private Duration lerDuracao() {
    System.out.println("Introduza o tempo a avançar (use 0 se não aplicável).");

    System.out.print("Dias a avançar: ");
    long dias = Long.parseLong(sc.nextLine());

    System.out.print("Horas a avançar: ");
    long horas = Long.parseLong(sc.nextLine());

    System.out.print("Minutos a avançar: ");
    long minutos = Long.parseLong(sc.nextLine());

    return Duration.ofDays(dias)
                   .plusHours(horas)
                   .plusMinutes(minutos);
  }

    private void casaMaiorConsumo() {
        Casa c = controller.getCasaComMaiorConsumo();
        if (c != null)
            System.out.println("casa = " + c.getNome());
        else
            System.out.println("Sem casas.");
    }

    private void topDivisoes() {
        try {
            var lista = controller.getTopTresDivisoesComMaisDipositivos();
            lista.forEach(System.out::println);

        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void userMaisAdmin() {
        Utilizador u = controller.utilizadorComMaisCasasComoAdmin();
        if (u != null)
            System.out.println(u);
        else
            System.out.println("Sem utilizadores.");
    }

    private void consumoPorDivisao() {
        try {
            Map<String, Double> res = controller.getConsumoMedioPorDivisao();

            if (res != null) 
                res.forEach((div, cons) ->
                    System.out.println(div + " -> " + cons));
            else 
                System.out.println("Sem divisões.");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void topDispositivos() {
        try {
            var lista = controller.getTresDispositivosMaisUsados();

            if (lista != null) 
                lista.forEach(System.out::println);
            else 
                System.out.println("Sem dispositivos.");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void executarCenario() {
        try {
            listarCenarios();

            System.out.print("Nome do cenário que pretende executar: ");
            String nome = sc.nextLine();

            controller.executarCenario(nome);

            System.out.println("Cenário executado.");

        } catch (CenarioInexistenteException e) {
            System.out.println("Erro: O cenário " + e.getMessage() + " não existe");
        
        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador não possui autorização para executar o cenário " + e.getMessage());

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (AberturaInvalidaException e) {
            System.out.println("Erro: Não é possível definir uma abertura de " + e.getMessage());

        } catch (IntensidadeInvalidaException e) {
            System.out.println("Erro: Não é possível definir uma intensidade de " + e.getMessage());

        } catch (CorInvalidadeException e) {
            System.out.println("Erro: Não é possível definir uma cor de " + e.getMessage());

        } catch (VolumeInvalidoException e) {
            System.out.println("Erro: Não é possível definir um volume de " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro ao executar o cenário: " + e.getMessage());
        }
    }

    private void criarUtilizador() {
        try {
            System.out.print("Nome: ");
            String nome = sc.nextLine();

            System.out.print("Email: ");
            String email = sc.nextLine();

            controller.criarUtilizador(nome, email);
            System.out.println("Utilizador criado com sucesso.");

        } catch (UtilizadorJaExisteExecption e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " já existe");
            
        } catch(Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void login() {
        try {
            System.out.print("Email do utilizador: ");
            String email = sc.nextLine();
            controller.selecionarUtilizador(email);

            System.out.println("Sessão iniciada.");

        } catch (UtilizadorNaoExisteException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não existe");
        
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void criarCasa() {
        try {
            System.out.print("Nome da casa: ");
            String nome = sc.nextLine();

            controller.criarCasa(nome);
            System.out.println("Casa criada com sucesso.");

        } catch (CasaJaExisteException e) {
            System.out.println("Erro: A casa " + e.getMessage() + " já existe");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void selecionarCasa() {
        try {
            System.out.print("Nome da casa: ");
            String nome = sc.nextLine();

            controller.selecionarCasa(nome);

            if (!controller.utilizadorTemAcessoCasaSelecionada()) {
                System.out.println("Não tens acesso a esta casa.");
                System.out.print("Queres pedir acesso? (s/n): ");
                String resp = sc.nextLine();

                if (resp.equalsIgnoreCase("s")) {
                    System.out.print("Papel (ADMIN / USER): ");
                    String papel = sc.nextLine();

                    controller.garantirAcessoCasa(Papel.valueOf(papel.toUpperCase()));
                    System.out.println("Acesso atribuído.");
                } else {
                    System.out.println("Acesso negado.");
                    controller.setNomeCasaAtual(null);
                    return;
                }
            }
            
            System.out.println("Casa selecionada com sucesso.");

        } catch (CasaNaoExisteException e) {
            System.out.println("Erro: A casa " + e.getMessage() + " não existe");
        
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void selecionarDispositivo() {
        try {
            System.out.print("ID do dispositivo: ");
            String id = sc.nextLine();

            controller.selecionarDispositivo(id);
            System.out.println("Dispositivo selecionado com sucesso.");
            menuConsultaDispositivo();

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");
        
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    // ACÕES 
    private void ligarDispositivo() {
        try {
            controller.ligarDispositivo();
            System.out.println("Dispositivo ligado.");

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }
        
    private void desligarDispositivo() {
            try {
                controller.desligarDispositivo();
                System.out.println("Dispositivo desligado.");

            } catch (DispositivoNaoExisteException e) {
                System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

            } catch (TipoDispositivoInvalidoException e) {
                System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

            } catch (Exception e) {
                System.out.println("Erro: " + e.getMessage());

            }
    }

    private void abrirDispositivo() {
        try {
            controller.abrirDispositivo();
            System.out.println("Dispositivo aberto.");

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void fecharDispositivo() {
        try {
            controller.fecharDispositivo();
            System.out.println("Dispositivo fechado.");

       } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void alterarValorAbertura() {
        try {
            System.out.print("Novo grau de abertura (0-100): ");
            int valor = Integer.parseInt(sc.nextLine());
            
            controller.alterarAberturaDispositivo(valor);
            System.out.println("Abertura do dispositivo alterada para " + valor + "%.");

         } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (AberturaInvalidaException e) {
            System.out.println("Erro: Não é possível definir uma abertura de " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void alterarLuminosidade() {
        try {
            System.out.print("Nova luminosidade (0-100): ");
            int valor = Integer.parseInt(sc.nextLine());

            controller.alterarLuminosidadeLampada(valor);
            System.out.println("Luminosidade da lâmpada alterada para " + valor + "%.");

       } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (IntensidadeInvalidaException e) {
            System.out.println("Erro: Não é possível definir uma intensidade de " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void alterarCor() {
        try {
            System.out.print("Nova cor (2700 - 4000): ");
            int valor = Integer.parseInt(sc.nextLine());

            controller.alterarCorLampada(valor);
            System.out.println("Cor da lâmpada alterada para " + valor + "%.");

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (CorInvalidadeException e) {
            System.out.println("Erro: Não é possível definir uma cor de " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void alterarSomColuna() {
        try {
            System.out.print("Novo volume (0 - 100): ");
            int valor = Integer.parseInt(sc.nextLine());

            controller.alterarVolumeColuna(valor);
            System.out.println("Volume da coluna alterada para " + valor + ".");

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (VolumeInvalidoException e) {
            System.out.println("Erro: Não é possível definir um volume de " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void alterarValorSensor() {
        try {
            System.out.print("Novo valor medido: ");
            double valor = Double.parseDouble(sc.nextLine());

            controller.alterarValorMedido(valor);
            System.out.println("Valor do sensor alterado para " + valor + ".");
            System.out.println("Automações associadas foram avaliadas automaticamente.");

        } catch (DispositivoNaoExisteException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");

        } catch (TipoDispositivoInvalidoException e) {
            System.out.println("Erro: O dispositivo " + e.getMessage() + " não permite executar essa ação");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void listarComFiltro(FiltroDispositivo filtro) {
        try {
            controller.listar(filtro);
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private boolean existemDispositivosComFiltro(Predicate<Dispositivo> filtro) {
        try {
            return controller.existemDispositivos(filtro);
        } catch (DomusControlException e) {
            System.out.println("Erro: " + e.getMessage());
            return false;
        }
    }

    private Acao criarAcaoInterativa() {
        try {
            System.out.print("Tipo de dispositivo para aplicar a ação (ex: lampada, cortina, ...): ");
            String tipo = sc.nextLine();

            String acaoNome = null;
            Integer valor = null;

            switch (tipo.toLowerCase()) {

                case "lampada":
                    System.out.println("1-Ligar 2-Desligar 3-Luminosidade 4-Cor");
                    int opL = Integer.parseInt(sc.nextLine());

                    switch (opL) {
                        case 1 -> acaoNome = "LIGAR";
                        case 2 -> acaoNome = "DESLIGAR";
                        case 3 -> {
                            acaoNome = "LUMINOSIDADE";
                            System.out.print("Valor (0-100): ");
                            valor = Integer.parseInt(sc.nextLine());
                        }
                        case 4 -> {
                            acaoNome = "COR";
                            System.out.print("Valor (2700-4000): ");
                            valor = Integer.parseInt(sc.nextLine());
                        }
                    }
                    break;
                    
                case "colunasom":
                    System.out.println("1-Ligar 2-Desligar 3-Alterar volume");
                    int opC = Integer.parseInt(sc.nextLine());

                    switch (opC) {
                        case 1 -> acaoNome = "LIGAR";
                        case 2 -> acaoNome = "DESLIGAR";
                        case 3 -> {
                            acaoNome = "VOLUME";
                            System.out.print("Valor (0-100): ");
                            valor = Integer.parseInt(sc.nextLine());
                        }
                    }
                    break;

                case "cortina":
                case "portaogaragem":
                    System.out.println("1-Abrir 2-Fechar 3-Abertura");
                    int opA = Integer.parseInt(sc.nextLine());

                    switch (opA) {
                        case 1 -> acaoNome = "ABRIR";
                        case 2 -> acaoNome = "FECHAR";
                        case 3 -> {
                            acaoNome = "ABERTURA";
                            System.out.print("Valor (0-100): ");
                            valor = Integer.parseInt(sc.nextLine());
                        }
                    }
                    break;

                default:
                    System.out.println("1-Ligar 2-Desligar");
                    int op = Integer.parseInt(sc.nextLine());
                    acaoNome = (op == 1) ? "LIGAR" : "DESLIGAR";
            }

            // Divisão (opcional)
            System.out.print("Divisão (ENTER para ignorar): ");
            String divisao = sc.nextLine();
            if (divisao.isBlank()) divisao = null;

            // Criar ação final
            return new AcaoPorFiltro(
                controller.criarFiltro(tipo, divisao),
                controller.criarFactory(acaoNome, valor)
            );

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
            return null;
        }
    }

    private AcaoComInversa criarAcaoInterativaReversivel() {
        Acao acao = criarAcaoInterativa();

        if (acao == null) {
            return null;
        }

        if (!(acao instanceof AcaoComInversa acaoInv)) {
            throw new AcaoNaoReversivelException("A ação selecionada não suporta inversão automática.");
        }

        return acaoInv;
    }

    public void criaAutomacaoPorSensor() {
            try {
                System.out.print("ID do sensor: ");
                String idSensor = sc.nextLine();

                System.out.print("Tipo de comparação (MAIOR/MENOR): ");
                String comparacao = sc.nextLine();

                System.out.print("Valor de referência: ");
                double valorReferencia = Double.parseDouble(sc.nextLine());

                List<AcaoComInversa> acoes = new ArrayList<>();
                String resposta;

                do {
                    AcaoComInversa a = criarAcaoInterativaReversivel();
                    if (a != null) acoes.add(a);

                    System.out.print("Deseja adicionar outra ação? (s/n): ");
                    resposta = sc.nextLine();

                } while (resposta.equalsIgnoreCase("s"));

                controller.criarAutomacaoPorSensor(
                        idSensor,
                        comparacao,
                        valorReferencia,
                        acoes
                );

                System.out.println("Automação criada com sucesso!");
            
            } catch (DispositivoNaoExisteException e) {
                System.out.println("Erro: O dispositivo " + e.getMessage() + " não existe");
            
            } catch (DispositivoNaoESensorException e) {
                System.out.println("Erro: O dispositivo " + e.getMessage() + " não é um sensor");
            
            } catch (AcaoNaoReversivelException e) {
                System.out.println("Erro: " + e.getMessage());

            } catch (Exception e) {
                System.out.println("Erro ao criar automação: " + e.getMessage());
            }
    }

    public void criaAutomacaoPorHorario() {
        try {
            System.out.print("Hora (HH:mm): ");
            LocalTime hora = LocalTime.parse(sc.nextLine()).withSecond(0);

            List<Acao> acoes = new ArrayList<>();
            String resposta;

            do {
                Acao a = criarAcaoInterativa();
                if (a != null) acoes.add(a);

                System.out.print("Deseja adicionar outra ação? (s/n): ");
                resposta = sc.nextLine();
            } while (resposta.equalsIgnoreCase("s"));

            controller.criarAutomacaoPorHorario(hora, acoes);
            System.out.println("Automação criada com sucesso!");
        }
        catch (Exception e) {
            System.out.println("Erro ao criar automação: " + e.getMessage());
        }
    }


    public void criaAutomacaoPorIntervalo() {
        try {
            System.out.print("Hora início (HH:mm): ");
            LocalTime inicio = LocalTime.parse(sc.nextLine())
                    .withSecond(0);

            System.out.print("Hora fim (HH:mm): ");
            LocalTime fim = LocalTime.parse(sc.nextLine())
                    .withSecond(0);

            List<AcaoComInversa> acoes = new ArrayList<>();
            String resposta;

            do {
                AcaoComInversa a = criarAcaoInterativaReversivel();
                if (a != null) acoes.add(a);

                System.out.print("Deseja adicionar outra ação? (s/n): ");
                resposta = sc.nextLine();
            } while (resposta.equalsIgnoreCase("s"));

            controller.criarAutomacaoPorIntervalo(inicio, fim, acoes);
            System.out.println("Automação criada com sucesso!");

        } catch (AcaoNaoReversivelException e) {
            System.out.println("Erro: " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    public void criaCenario() {
        try {
            System.out.print("Nome do cenário: ");
            String nome = sc.nextLine();

            List<Acao> acoes = new ArrayList<>();
            String resposta;

            do {
                Acao a = criarAcaoInterativa();
                if (a != null) acoes.add(a);

                System.out.print("Deseja adicionar outra ação? (s/n): ");
                resposta = sc.nextLine();
           } while (resposta.equalsIgnoreCase("s"));

           controller.criarCenario(nome,acoes);
           System.out.println("Cenário criado com sucesso!");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }   
    }

    private void listarDivisoes() {
        try {
            Map<String, Set<Dispositivo>> divs = controller.getDivisoes();

            if (divs.isEmpty()) {
                System.out.println("Não existem divisões.");
                return;
            }

            for (String nome : divs.keySet()) {
                int num = divs.get(nome).size(); // já tens o set
                System.out.println(nome + " (" + num + " dispositivos)");
            }

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void listarAutomacoes() {
        try {
            Set<Automacao> automacoes = controller.listarAutomacoes();

            if (automacoes.isEmpty()) {
                System.out.println("Não existem automações.");
                return;
            }

            for (Automacao a : automacoes) {
                System.out.println(a); // chama toString automaticamente
            }

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private void criarDivisao() {
        try {
            System.out.print("Nome da divisão: ");
            String nome = sc.nextLine();

            controller.criarDivisao(nome);
            System.out.println("Divisão criada com sucesso.");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");

        } catch (DivisaoJaExisteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " já existe");

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criacaoDispositivos() {
        NewMenu menuCriacao = new NewMenu(new String[] {
        "Criar lâmpada",
        "Criar coluna de som",
        "Criar cortina",
        "Criar portão de garagem",
        "Criar relé",
        "Criar sensor de pluviosidade",
        "Criar sensor de luminosidade"
        });

        menuCriacao.setHandler(1, () -> criarLampada());
        menuCriacao.setHandler(2, () -> criarColunaSom());
        menuCriacao.setHandler(3, () -> criarCortina());
        menuCriacao.setHandler(4, () -> criarPortaoGaragem());
        menuCriacao.setHandler(5, () -> criarRele());
        menuCriacao.setHandler(6, () -> criarSensorChuva());
        menuCriacao.setHandler(7, () -> criarSensorLuminosidade());

        menuCriacao.run();
    }

    private void guardarEstado() {
        try {
            controller.guardarEstado("estado.dat");
            System.out.println("Estado guardado com sucesso.");

        } catch (FileNotFoundException e) {
            System.out.println("Não foi possível criar o ficheiro de estado.");

        } catch (IOException e) {
            System.out.println("Erro ao guardar o estado: " + e.getMessage());

        }
    }

    // métodos auxiliares para leitura
    private String ler(String campo) {
        System.out.print(campo + ": ");
        return sc.nextLine();
    }

    private double lerDouble(String campo) {
        System.out.print(campo + ": ");
        return Double.parseDouble(sc.nextLine());
    }

    private void criarLampada() {
        try {
            controller.criarLampada(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora"),
                ler("Divisão à qual pretende adicionar")
            );

            System.out.println("Lâmpada criada com sucesso.");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");

        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarColunaSom() {
        try {
            controller.criarColunaSom(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora"),
                ler("Divisão à qual pretende adicionar")
            );

            System.out.println("Coluna de som criada com sucesso.");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");

        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarCortina() {
        try {
            controller.criarPortaoGaragem(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora"),
                lerDouble("Tempo total de abertura (segundos)"),
                ler("Divisão à qual pretende adicionar")
            );

            System.out.println("Cortina criada com sucesso.");
        
        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");
        
        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarPortaoGaragem() {
        try {
            controller.criarPortaoGaragem(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora"),
                lerDouble("Tempo total de abertura (segundos)"),
                ler("Divisão à qual pretende adicionar")
            );

            System.out.println("Portão criado com sucesso.");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");

        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarRele() {
        try {
            controller.criarRele(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora"),
                ler("Divisão à qual pretende adicionar")
            );

            System.out.println("Relé criado com sucesso.");
        
        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DivisaoInexistenteException e) {
            System.out.println("Erro: A divisão " + e.getMessage() + " não existe");

        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarSensorChuva() {
        try {
            controller.criarSensorChuva(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora")
            );

            System.out.println("Sensor de pluviosidade criado com sucesso.");
       
        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

    private void criarSensorLuminosidade() {
        try {
            controller.criarSensorLuminosidade(
                ler("ID"),
                ler("Marca"),
                ler("Modelo"),
                lerDouble("Consumo por hora")
            );

            System.out.println("Sensor de luminosidade criado com sucesso.");

        } catch (AcessoNegadoException e) {
            System.out.println("Erro: O utilizador " + e.getMessage() + " não tem permissões");
        
        } catch (DispositivoJaExisteException e) {
            System.out.println("Erro: Já existe um dispositivo na casa com id " + e.getMessage());

        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());

        }
    }

}
