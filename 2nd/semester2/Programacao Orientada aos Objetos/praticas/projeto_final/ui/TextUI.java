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


import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

import exceptions.CarroInexistenteException;
import exceptions.CarroRepetidoException;

public class TextUI {
  // o modelo
  private CarRental model;
  
  //scanner 
  private Scanner sc;

  /**
   * Construtor que cria os menus e o model
   */

  public TextUI() throws FileNotFoundException, IOException, ClassNotFoundException {
    this.model = createRental();
    sc = new Scanner(System.in);
  }
  
  public CarRental createRental() throws FileNotFoundException, IOException, ClassNotFoundException {
    try {
      return CarRental.carregaEstado("estado.dat");

    } catch (FileNotFoundException e) {
      System.out.println("Erro: O " + e.getMessage() + " não existe");

    } catch (ClassNotFoundException e) {
      System.out.println("Erro: O " + e.getMessage() + " não existe");

    } catch (IOException e) {
      System.out.println("Erro: O "+ e.getMessage() + " deu erro");

    }

    return new CarRental();
  }
  
  /**
   * Método que executa o menu principal.
   * Coloca a interface em execução.
   */
  
  public void run() {
    NewMenu menu = new NewMenu(new String[] {
            " Gestão de Veículos",
            " Dar Nome à Empresa"
    });
    
    //pré-condição: só se altera o nome da empresa se este for vazio!!
    menu.setPreCondition(2, () -> this.model.getNome().equals(""));
    //registar os métodos de tratamento, passados como 
    //expressões lambda (interface funcional)
    menu.setHandler(1, () -> gestaoVeiculos());
    menu.setHandler(2, () -> alterarNomeEmpresa());
    
    //colocar o menú em visualização e esperar leitura de opção
    menu.run();
  }
  
  /**
   * Métodos associados ao handler
   */
  private void gestaoVeiculos() {
    NewMenu menuVeiculos = new NewMenu(new String[] {"Adicionar Veiculo", 
                            "Listar Veiculo", 
                            "Remover Veiculo"});

    // pre condition
    menuVeiculos.setPreCondition(2, () -> this.model.quantos() != 0); 
    menuVeiculos.setPreCondition(3, () -> this.model.quantos() != 0);

    //registar os handlers
    menuVeiculos.setHandler(1, () -> addVeiculo());
    menuVeiculos.setHandler(2, () -> listVeiculo());
    menuVeiculos.setHandler(3, () -> remVeiculo());
    
    menuVeiculos.run();
  }
  
  
  private void alterarNomeEmpresa() {
    System.out.print("Novo nome da Empresa: ");
    String nome = sc.nextLine();
    this.model.setNome(nome);
  }
  
  private void addVeiculo() {
    System.out.print("Tipo de Carro (CarroEletrico/CarroCombustao/CarroHibrido): ");
    String tipo = sc.nextLine();

    System.out.print("ID: ");
    String id = sc.nextLine();

    System.out.print("Marca: ");
    String marca = sc.nextLine();

    System.out.print("Modelo: ");
    String modelo = sc.nextLine();

    System.out.print("Ano: ");
    int ano = Integer.parseInt(sc.nextLine());

    System.out.print("Velocidade Média: ");
    double vMedia = Double.parseDouble(sc.nextLine());

    System.out.print("Autonomia: ");
    double autonomia = Double.parseDouble(sc.nextLine());

    // CARRO ELÉTRICO
    if (tipo.equalsIgnoreCase("CarroEletrico")) {

        System.out.print("Dimensão da bateria: ");
        double dimensaoBateria = Double.parseDouble(sc.nextLine());

        System.out.print("Consumo (kWh/100km): ");
        double consumoKWh100Km = Double.parseDouble(sc.nextLine());

        System.out.print("Preço por kWh: ");
        double precoKWh = Double.parseDouble(sc.nextLine());

        try {
          Carro c = new CarroEletrico(id, marca, modelo, ano, vMedia, autonomia, vMedia, autonomia, dimensaoBateria, consumoKWh100Km, precoKWh);
          model.adiciona(c);

        } catch (CarroRepetidoException e) {
          System.out.println("Erro: O carro " + e.getMessage() + " já existe");

        } catch (Exception e) {
          System.out.println("Erro:" + e.getMessage());

        }

    // CARRO COMBUSTÃO
    } else if (tipo.equalsIgnoreCase("CarroCombustao")) {

        System.out.print("Tamanho do depósito: ");
        double tamanhoDeposito = Double.parseDouble(sc.nextLine());

        System.out.print("Consumo (L/100km): ");
        double consumoLitros100Km = Double.parseDouble(sc.nextLine());

        System.out.print("Preço por litro: ");
        double precoPorLitro = Double.parseDouble(sc.nextLine());

        try {
          Carro c = new CarroCombustao(id, marca, modelo, ano, vMedia, autonomia, vMedia, autonomia, tamanhoDeposito, consumoLitros100Km, precoPorLitro);
          model.adiciona(c);

        } catch (CarroRepetidoException e) {
          System.out.println("Erro: O carro " + e.getMessage() + " já existe");

        } catch (Exception e) {
          System.out.println("Erro:" + e.getMessage());
          
        }

    //  CARRO HÍBRIDO
    } else if (tipo.equalsIgnoreCase("CarroHibrido")) {

        // Parte elétrica
        System.out.print("Dimensão da bateria: ");
        double dimensaoBateria = Double.parseDouble(sc.nextLine());

        System.out.print("Consumo (kWh/100km): ");
        double consumoKWh100Km = Double.parseDouble(sc.nextLine());

        System.out.print("Preço por kWh: ");
        double precoKWh = Double.parseDouble(sc.nextLine());

        // Parte combustão
        System.out.print("Tamanho do depósito: ");
        double tamanhoDeposito = Double.parseDouble(sc.nextLine());

        System.out.print("Consumo (L/100km): ");
        double consumoLitros100Km = Double.parseDouble(sc.nextLine());

        System.out.print("Preço por litro: ");
        double precoPorLitro = Double.parseDouble(sc.nextLine());

        try {
          Carro c = new CarroHibrido(id, marca, modelo, ano, vMedia, autonomia, vMedia, autonomia, 
                                    tamanhoDeposito, consumoLitros100Km, precoPorLitro, dimensaoBateria, consumoKWh100Km, precoKWh);
          model.adiciona(c);

        } catch (CarroRepetidoException e) {
          System.out.println("Erro: O carro " + e.getMessage() + " já existe");

        } catch (Exception e) {
          System.out.println("Erro:" + e.getMessage());

        }

    } else {
        System.out.println("Tipo de carro inválido!");
    }
  }
  
  private void listVeiculo() {
    try {
      System.out.print("ID: ");
      String id = sc.nextLine();

      Carro c = this.model.getCarro(id);
      System.out.print(c.toString());

    } catch (CarroInexistenteException e) {
      System.out.println("Erro: O carro " + e.getMessage() + " não existe");

    } catch (Exception e) {
      System.out.println("Erro: " + e.getMessage());

    }
  }
  
  private void remVeiculo() {
    try {
      System.out.print("ID: ");
      String id = sc.nextLine();

      this.model.remove(id);
    }  catch (CarroInexistenteException e) {
      System.out.println("Erro: O carro " + e.getMessage() + " não existe");

    } catch (Exception e) {
      System.out.println("Erro: " + e.getMessage());

    }
  }
  
}
