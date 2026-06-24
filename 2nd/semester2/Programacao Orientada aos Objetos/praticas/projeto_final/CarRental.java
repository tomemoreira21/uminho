import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

import exceptions.CarroInexistenteException;
import exceptions.CarroRepetidoException;

public class CarRental implements Serializable {
    private String nome;
    private Map<String, Carro> stockCarros;
    private static Map<String,Comparator<Carro>> comparadores = new HashMap<>();

    public CarRental(String nome) {
        this.nome = nome;
        this.stockCarros = new HashMap<>();
    }

    public CarRental() {
        this.nome = "";
        this.stockCarros = new HashMap<>();
    }

    public CarRental(CarRental c) {
        this.nome = c.getNome();
        this.stockCarros = c.getStockCarros();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Map<String,Carro> getStockCarros() {
        return this.stockCarros.entrySet()
                          .stream()
                          .collect(Collectors.toMap(
                            e -> e.getKey(),
                            e -> e.getValue().clone()
                            ));
    }

    public static Map<String,Comparator<Carro>> getCompadores() {
        return comparadores.entrySet()
                                .stream()
                                .collect(Collectors.toMap(
                                    e -> e.getKey(),
                                    e -> e.getValue()
                                ));
    }

    public void setStockCarros(Map<String,Carro> carros) {
        Map<String,Carro> novos_c = new HashMap<>();

        for (Map.Entry<String,Carro> c : carros.entrySet()) {
            novos_c.put(c.getKey(),c.getValue().clone());
        }

        this.stockCarros = novos_c;
    }

    public  static void setComparadores(Map<String,Comparator<Carro>> comparadores) {
        Map<String,Comparator<Carro>> comp = new HashMap<>();

        for (Map.Entry<String,Comparator<Carro>> c : comparadores.entrySet()) {
            comp.put(c.getKey(),c.getValue());
        }

        comparadores = comp;
    }

    public static void adicionaComparador(String nomeComp,Comparator<Carro> comp) {
        comparadores.put(nomeComp,comp);
    }

    public static Comparator<Carro> getComparador(String nomeComp) {
        return comparadores.get(nomeComp);
    }

    public boolean existeCarro(String cod) {
        return this.stockCarros.containsKey(cod);
    }
 
    public Carro getCarro(String cod) throws CarroInexistenteException {
        if (!this.stockCarros.containsKey(cod)) {
            throw new CarroInexistenteException(""+cod);
        }

        return this.stockCarros.get(cod).clone();
    }

    public int quantos() {
        return this.stockCarros.values().size();
    }

    public int quantos(String marca) {
        return (int)this.stockCarros.values().stream()
                                   .filter(c -> c.getMarca().equals(marca))
                                   .count();
    }

    public void adiciona(Carro v) throws CarroRepetidoException {
        if (this.stockCarros.containsKey(v.getId())) {
            throw new CarroRepetidoException(""+v.getId());
        }

        this.stockCarros.put(v.getId(),v.clone());
    }

    public void remove(String cod) throws CarroInexistenteException {
        Carro c = this.stockCarros.get(cod);

        if (c == null) {
            throw new CarroInexistenteException(cod);
        }

        this.stockCarros.remove(cod);
    }

    public List<Carro> getCarros() {
        return this.stockCarros.values()
                               .stream()
                               .map(Carro :: clone) 
                               .collect(Collectors.toList());
                               
    }

    public void adiciona(Set<Carro> vs) throws CarroRepetidoException {
        for (Carro c : vs) {
            this.adiciona(c.clone());
        }
    }


    public void registarViagem(String codCarro,int numKms) throws CarroInexistenteException {
        if (!this.stockCarros.containsKey(codCarro)) {
            throw new CarroInexistenteException(""+codCarro);
        }

        this.stockCarros.get(codCarro).registarViagem(numKms);
    }

    public void atestarCarro(String codCarro) {
        this.stockCarros.get(codCarro).atestar();
    }

    public Carro obterCarroMaisEconomico() {
        Comparator<Carro> cmp = (c1,c2) -> Double.compare(c1.custoPorKm(),c2.custoPorKm());

        return this.stockCarros.values()
                               .stream()
                               .sorted(cmp)
                               .findFirst()
                               .orElse(null);
    }

    public double obterMediaCustoPorKm() {
        return this.stockCarros.values()
                             .stream()
                             .mapToDouble(Carro :: custoPorKm)
                             .average()
                             .orElse(0.0);
    }


    public int custoRealKm(String cod) {
        return (int)this.stockCarros.get(cod).custoPorKmReal();
    }

    public Set<Carro> carrosComAlcance(int kms) {
        return this.stockCarros.values()
                               .stream()
                               .map(Carro :: clone)
                               .filter(carro -> carro.getAutonomia() >= kms)
                               .collect(Collectors.toSet());
    }

    public Set<CarroEletrico> comBateriaDe(int nivelMinimo) {
        return this.stockCarros.values()
                               .stream()
                               .filter(c -> (c instanceof CarroEletrico))
                               .map(c -> (CarroEletrico) c.clone())
                               .filter(c -> c.getNivelBateria() >= nivelMinimo)
                               .collect(Collectors.toSet());
    }

    
    public Carro carroComMaisKms() {
        return this.stockCarros.values()
                               .stream()
                               .sorted(new ComparadorKmAlfabetico())
                               .findFirst()
                               .map(Carro :: clone) 
                               .orElse(null);
    }


    public Set<CarroEletrico> obtemCarros() {
        return this.stockCarros.values()
                               .stream()
                               .filter(c -> (c instanceof CarroEletrico))
                               .map(c -> (CarroEletrico) c.clone())
                               .sorted()
                               .collect(Collectors.toSet());
    }


    public Iterator<Carro> ordenarCarros(String criterio) {
        Comparator<Carro> comparador = getComparador(criterio);

        return this.stockCarros.values()
                               .stream()
                               .map(Carro :: clone)
                               .sorted(comparador)
                               .iterator();

    }

    public Map<Integer,List<Carro>> carrosPorAutonomia() {
        Map<Integer,List<Carro>> carrosPorAutonomia = new HashMap<>();

        for (Carro c : this.stockCarros.values()) {
            Integer autonomia = (int)c.getAutonomia();  
            List<Carro> listCarros = carrosPorAutonomia.get(autonomia);

            if (listCarros == null) {
                listCarros = new ArrayList<Carro>();
            }

            listCarros.add(c.clone());
            carrosPorAutonomia.put(autonomia,listCarros);
        }

        return carrosPorAutonomia;
    }

    // versão com iterador interno (grouping by)
    public Map<Integer,List<Carro>> carrosPorAutonomia_v2() {
        return this.stockCarros.values()
                               .stream()
                               .collect(Collectors.groupingBy(
                                 c -> (int)c.getAutonomia()
                               ));
    }

    /*
    APENAS DISPONIBILIZA OS MÉTODOS PRESENTES NA INTERFACE PontosPorKms
    */
    public List<PontosPorKms> verPontos() {
        return this.stockCarros.values()
                               .stream()
                               .filter(c -> (c instanceof CarroEletrico))
                               .map(c -> (CarroEletrico) c.clone())
                               .map(c -> (PontosPorKms)c)
                               .collect(Collectors.toList());
    }

    public List<CarroHibrido> getHibridos() {
        return this.stockCarros.values()
                               .stream()
                               .filter(c -> c instanceof CarroHibrido)
                               .map(c -> (CarroHibrido)c.clone())
                               .collect(Collectors.toList());
    }

    public void gravarModoTexto(String ficheiro) throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(ficheiro);
        pw.println(this.stockCarros);
        pw.flush();
        pw.close();
    }

    public void guardaEstado(String nomeFicheiro) throws FileNotFoundException,IOException {
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    public static CarRental carregaEstado(String nomeFicheiro) throws FileNotFoundException,
                                                                      IOException,
                                                                      ClassNotFoundException {

       FileInputStream fis = new FileInputStream(nomeFicheiro);
       ObjectInputStream ois = new ObjectInputStream(fis);
       CarRental c = (CarRental) ois.readObject();
       ois.close();
       return c;
    }

    public String toString() {
        return "carros = " + this.stockCarros;
    }

}   