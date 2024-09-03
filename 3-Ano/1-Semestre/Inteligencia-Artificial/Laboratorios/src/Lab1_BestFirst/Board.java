package Lab1_BestFirst;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Board implements Ilayout, Cloneable {
    private static final int dim = 3;
    private int board[][];

    public Board() {
        board = new int[dim][dim];
    }

    public Board(String str) throws IllegalStateException {
        if(str.length() != dim*dim) throw new
                IllegalStateException("Invalid arg in Board constructor");
        board = new int[dim][dim];
        int si = 0;
        for(int i = 0; i < dim; i++)
            for(int j = 0; j < dim; j++)
                board[i][j] = Character.getNumericValue(str.charAt(si++));
    }

    public String toString() {
        String str = new String();
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (board[i][j] == 0)
                    str += " ";
                else
                    str += Integer.toString(board[i][j]);
            }
            str += "\n";
        }
        return str;
    }

    public String constructorString() {
        String str = new String();
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++)
                str += Integer.toString(board[i][j]);
        }
        return str;
    }

    @Override
    public Object clone() {
        return new Board(this.toString().replace(" ", "0").replace("\n",""));
    }

    @Override
    public List<Ilayout> children() {
        List<Ilayout> children = new ArrayList<>();
        for(int i = 0; i < dim; i++)
            for(int j = 0; j < dim; j++)
                if(this.board[i][j] == 0)
                    children = child(i,j);
        return children;
    }

    public List<Ilayout> child(int i, int j) {
        List<Ilayout> children = new ArrayList<>();
        if(i+1 < dim)
            children.add(childBuild(new Board(this.constructorString()), i,j, i+1, j));
        if(i-1 >= 0)
            children.add(childBuild(new Board(this.constructorString()), i,j, i-1, j));
        if(j+1 < dim)
            children.add(childBuild(new Board(this.constructorString()), i,j, i, j+1));
        if(j-1 >= 0)
            children.add(childBuild(new Board(this.constructorString()), i,j, i, j-1));
        return children;
    }

    public Board childBuild(Board clone, int i, int j, int newI, int newJ){
        clone.board[i][j] = clone.board[newI][newJ];
        clone.board[newI][newJ] = 0;
        return clone;
    }

    @Override
    public boolean isGoal(Ilayout l) {
        Board tmp = (Board) l;
        return Arrays.deepEquals(board, tmp.board);
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
        String str = ((Board) o).constructorString();
        return str.equals(this.constructorString());
    }

    @Override
    public int hashCode() {
        return Objects.hash(this);
    }
}