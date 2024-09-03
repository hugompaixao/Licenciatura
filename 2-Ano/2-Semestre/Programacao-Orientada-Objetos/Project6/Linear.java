
import java.util.List;

public class Linear implements ISpotTheShips {
    private int noScans;

    /**
     * Recives board - list with all the ships
     * the number of ships and number of rows and columns
     * After uses cicle while to check all positions until it finds all ships
     * @param board
     * @param noShips
     * @param rows
     * @param columns
     * @return scanList
     */
    @Override
    public List <Position> solve(List<Position> board, int noShips, int rows, int columns) {
        List <Position> scanList = board;
        int count = noShips;
        int i = 0;
        while(count > 0) {
            if(Character.compare(scanList.get(i).getType(), 'O') == 0) {
                count--;
                scanList.get(i).setType('+');
            }

            else
                scanList.get(i).setType('X');

            i++;
        }
        noScans = i;
        return scanList;
    }

    /**
     * @return noScans
     */
    @Override
    public int noScans() {
        return this.noScans;
    }
}
