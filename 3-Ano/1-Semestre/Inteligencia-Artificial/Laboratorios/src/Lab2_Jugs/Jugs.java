package Lab2_Jugs;

import java.util.*;

public class Jugs implements Ilayout, Cloneable{
    private static final int dim = 3, inDim = 5;
    private int jugsMax[] = {8, 5, 3};
    private int jugs[];

    public Jugs() {
        jugs = new int[dim];
    }

    public Jugs(String str) {
        if(str.length() != inDim) throw new
                IllegalStateException("Invalid arg in Jugs constructor");
        jugs = new int[dim];
        String str1 = str.replace(" ","");
        int si = 0;
        for(int i = 0; i < dim; i++)
            jugs[i] = Character.getNumericValue(str1.charAt(si++));
    }


    public String toString() {
        String str = jugs[0] + " " + jugs[1] + " " + jugs[2];
        return str;
    }

    @Override
    public Object clone() {
        return new Jugs(this.toString());
    }

    @Override
    public List<Ilayout> children() {
        List<Ilayout> children = new ArrayList<>();
        for(int i = 0; i < dim; i++)
            for(int j = 0; j < dim; j++)
                if((i != j) && (jugs[j] != jugsMax[j]))
                    children.add(childBuild(new Jugs(this.toString()), i, j));
        return children;
    }

    public Jugs childBuild(Jugs clone, int i, int j) {
        //if((i != j) && (jugs[j] != jugsMax[j])) {
            if (!((clone.jugs[i] == 0))) {// && (clone.jugs[j] == 0))) {
                int tmp = clone.jugs[i];
                clone.jugs[i] = tmp <= (jugsMax[j] - clone.jugs[j]) ? 0 : tmp - (jugsMax[j] - clone.jugs[j]);
                clone.jugs[j] = tmp >= (jugsMax[j] - clone.jugs[j]) ? jugsMax[j] : tmp + clone.jugs[j];
            }
        //}
        return clone;
    }

    @Override
    public boolean isGoal(Ilayout l) {
        Jugs tmp = (Jugs) l;
        return Arrays.equals(jugs, tmp.jugs);
    }

    @Override
    public double getG() {
        return 1;
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