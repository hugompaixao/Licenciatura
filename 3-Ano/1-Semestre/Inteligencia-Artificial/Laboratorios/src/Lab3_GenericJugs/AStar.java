package Lab3_GenericJugs;

import java.util.*;

public class AStar {
    static class State {

        private Ilayout layout, goal;
        private State father;
        private double g, f;

        public State(Ilayout l, State n, Ilayout goal) {
            layout = l;
            father = n;
            if(father != null) {
                g = father.g + l.getG();
                f = layout.getHeuristic(goal);
            } else {
                g = 0.0;
                f = 0.0;
            }
        }

        public String toString() {
            return layout.toString();
        }

        public double getG() {
            return g;
        }

        public double getF() {
            return f + g;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            State state = (State) o;
            return layout.equals(state.layout);
        }

        @Override
        public int hashCode() {
            return super.hashCode();
        }
    }

    private State actual;
    private Ilayout objective;

    private List<State> sucessores(State n, Ilayout goal) {
        List<State> sucs = new ArrayList<>();
        List<Ilayout> children = n.layout.children();
        for(Ilayout e: children) {
            if(n.father == null || !e.equals(n.father.layout)) {
                State nn = new State(e, n, goal);
                sucs.add(nn);
            }
        }
        return sucs;
    }

    final public boolean containList(List<State> fechados, State s) {
        for(State fechado : fechados)
            if(fechado.layout.isGoal(s.layout))
                return true;
        return false;
    }

    final public boolean containQueue(Queue<State> abertos, State s) {
        for(State aberto : abertos)
            if(aberto.layout.isGoal(s.layout))
                return true;
        return false;
    }

    final public Iterator<State> solve(Ilayout s, Ilayout goal) {
        objective = goal;
        Queue<State> abertos = new PriorityQueue<>(10, (s1, s2) -> (int) Math.signum(s1.getF()- s2.getF()));
        List<State> fechados = new ArrayList<>();
        abertos.add(new State(s, null, goal));
        List<State> sucs;
        List<State> result = new ArrayList<>();
        while(true) {
            if(abertos.isEmpty())
                return null;
            actual = abertos.poll();
            if(actual.layout.isGoal(objective)) {
                while(actual != null) {
                    result.add(actual);
                    actual = actual.father;
                }
                Collections.reverse(result);
                return result.iterator();
            } else {
                sucs = sucessores(actual, goal);
                fechados.add(actual);
                for(State var: sucs)
                    if(!containList(fechados, var) && !containQueue(abertos, var))
                        abertos.add(var);
            }
        }
    }
}
