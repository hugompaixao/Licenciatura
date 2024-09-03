
import java.util.List;

public interface ISpotTheShips {
    /**
     * @param board
     * @param noShips
     * @param rows
     * @param columns
     * @return List <Position>
     */
    List <Position> solve(List<Position> board, int noShips, int rows, int columns);

    /**
     * @return int
     */
    int noScans();
}
