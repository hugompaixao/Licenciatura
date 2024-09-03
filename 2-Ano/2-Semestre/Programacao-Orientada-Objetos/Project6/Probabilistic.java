
import java.util.ArrayList;
import java.util.List;

public class Probabilistic implements ISpotTheShips {
    private int noScans;
    private List <Position> scanList, highProbabilityList;
    private char[][] matrix;

    @Override
    public  List <Position> solve(List<Position> board, int noShips, int rows, int columns) {
        scanList = board;
        return scanList;
    }

    @Override
    public int noScans() {
        return this.noScans;
    }
}
