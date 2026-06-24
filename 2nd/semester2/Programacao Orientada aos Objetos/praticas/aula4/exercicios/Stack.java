import java.util.*;

public class Stack {
    private List<String> list; 

    public Stack(int dim) {
        this.list = new ArrayList<String>(dim); // ele vai alocar logo um bloco de dim dimensoes String, se ultrapassar não há problema, apenas uma questão de performance
    }

    public Stack() {
        this.list = new ArrayList<String>();
    }

    public Stack(Stack s) {
        this.list = s.getList();
    }

    public List<String> getList() {
        ArrayList<String> listNova = new ArrayList<String>(this.list.size());

        for (String s : this.list) {
            listNova.add(s);
        }

        return listNova;
    }

    public void setList(List<String> a) {
        ArrayList<String> listNova = new ArrayList<String>(a.size());

        for (String s : a) {
            listNova.add(s);
        }

        this.list = listNova;
    } 

    public boolean empty() {
        return this.list.isEmpty();
    }

    public int length() {
        return this.list.size();
    }

    public String top() {
        if (this.empty()) return null;
        return list.get(this.length() - 1);
    }

    public void push (String s) {
        list.add(s);
    }

    public void pop() {
        if (this.empty()) return;
        list.removeLast();
    }

    public Stack clone() {
        return new Stack(this);
    }

    public String toString() {
        String out = "";

        for (int i = this.length() - 1; i >= 0; i--) {
            out += ("\n" + i + "  " + this.list.get(i));
        }

        return out;
    }

    public boolean equals(Object o) {
        if (o == this) return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        Stack s = (Stack) o;
        return s.getList().equals(this.list); 
    }

}
