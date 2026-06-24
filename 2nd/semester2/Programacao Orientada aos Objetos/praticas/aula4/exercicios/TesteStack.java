public class TesteStack {
    public static void main (String[] args) {
        Stack s = new Stack();
        
        System.out.format ("isEmpty? %s\n",(s.empty()) ? "Sim" : "Não");
        System.out.format("Elemento de topo = " + s.top() + "\n");
        
        s.push("Julio");
        s.push("Vitor");
        s.push("Carlos");
        s.push("Tomé");
        s.push("Luis");

        System.out.print ("----------------- Estado Inicial -----------------");
        System.out.println (s.toString());

        s.pop();
        s.pop();

        System.out.format ("\n----------------- Remoção de 2 elementos -----------------");
        System.out.println (s.toString());
        
        System.out.format("\nElemento de topo = " + s.top() + "\n");
    }
}
