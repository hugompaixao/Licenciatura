package Lab2_Jugs;

import java.util.*;

public class BestFirst {
    static class State {

        private Ilayout layout;
        private State father;
        private double g;

        public State(Ilayout l, State n) {
            layout = l;
            father = n;
            if(father != null)
                g = father.g + l.getG();
            else g = 0.0;
        }

        public String toString() {
            return layout.toString();
        }

        public double getG() {
            return g;
        }
    }

    protected Queue<State> abertos;
    private List<State> fechados;
    private State actual;
    private Ilayout objective;

    final private List<State> sucessores(State n) {
        List<State> sucs = new ArrayList<>();
        List<Ilayout> children = n.layout.children();
        for(Ilayout e: children) {
            if(n.father == null || !e.equals(n.father.layout)) {
                State nn = new State(e, n);
                sucs.add(nn);
            }
        }
        return sucs;
    }

    final public Iterator<State> solve(Ilayout s, Ilayout goal) {
        objective = goal;
        Queue<State> abertos = new PriorityQueue<>(10, (s1, s2) -> (int) Math.signum(s1.getG()- s2.getG()));
        List<State> fechados = new ArrayList<>();
        abertos.add(new State(s, null));
        List<State> sucs;
        List<State> result = new ArrayList<State>();
        while(true) {
            if(abertos.isEmpty())
                return null;
            actual = abertos.remove();
            if(actual.layout.isGoal(objective)) {
                while(actual != null) {
                    result.add(actual);
                    actual = actual.father;
                }
                Collections.reverse(result);
                return result.iterator();
            } else {
                sucs = sucessores(actual);
                fechados.add(actual);
                for(State var: sucs)
                    if(!fechados.contains(var))
                        abertos.add(var);
            }
        }
    }
}