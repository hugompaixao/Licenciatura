package Lab3_GenericJugs;

import java.util.*;

public class GenericJugs implements Ilayout, Cloneable{
    private static int size;
    private static int[] jugsMax;
    private int jugs[];

    public GenericJugs() {
        jugs = new int[0];
    }

    public GenericJugs(String str) {
        String[] values = getValues(str);
        jugs = new int[size];
        for(int i = 0; i < size; i++)
            jugs[i] = Integer.parseInt(values[i]);
    }

    public static void setMax(String max) {
        String[] value = getValues(max);
        jugsMax = new int[size];
        for(int i = 0; i < size; i++) {
            jugsMax[i] = Integer.parseInt(value[i]);
        }
    }

    public static String[] getValues(String str) {
        int space = 0;
        for(int i = 0; i < str.length(); i++)
            if(Character.isWhitespace(str.charAt(i)))
                space++;
        size = space + 1;
        String[] result = str.split(" ", size);
        return result;
    }

    public String toString() {
        String str = new String();
        for(int i = 0; i < size; i++) {
            str += Integer.toString(jugs[i]);
            if(i + 1 != size)
                str += " ";
        }
        return str;
    }

    @Override
    public Object clone() {
        return new GenericJugs(this.toString());
    }

    @Override
    public List<Ilayout> children() {
        List<Ilayout> children = new ArrayList<>();
        for(int i = 0; i < size; i++)
            if(jugs[i] != 0)
                for(int j = 0; j < size; j++)
                    if((i != j) && (jugs[j] != jugsMax[j]))
                        children.add(childBuild(new GenericJugs(this.toString()), i, j));
        return children;
    }

    public GenericJugs childBuild(GenericJugs clone, int i, int j) {
        if (!(clone.jugs[i] == 0)) {
            int tmp = clone.jugs[i];
            clone.jugs[i] = tmp <= (jugsMax[j] - clone.jugs[j]) ? 0 : tmp - (jugsMax[j] - clone.jugs[j]);
            clone.jugs[j] = tmp >= (jugsMax[j] - clone.jugs[j]) ? jugsMax[j] : tmp + clone.jugs[j];
        }
        return clone;
    }

    @Override
    public boolean isGoal(Ilayout l) {
        GenericJugs tmp = (GenericJugs) l;
        return Arrays.equals(jugs, tmp.jugs);
    }
    @Override
    public double getG() {
        return 1;
    }

    @Override
    public double getHeuristic(Ilayout goal) {
        double heuristic = 0;
        GenericJugs tmp = (GenericJugs) goal;
        for(int i = 0; i < size; i++) {
            if(jugs[i] != tmp.jugs[i])
                heuristic++;
        }
        return heuristic;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        String str = (o).toString();
        return str.equals(this.toString());
    }

    @Override
    public int hashCode() {
        return Objects.hash(this);
    }

}
