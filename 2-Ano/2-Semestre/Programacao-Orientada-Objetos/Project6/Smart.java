
import java.util.List;

public class Smart implements ISpotTheShips {
    private int i, j, k, var, count, noScans, column;
    private List<Position> scanList;

    /**
     * Recives board - list with all the ships
     * the number of ships and number of rows and columns
     * After uses cycle while to check all positions until it finds all ships
     * @param board
     * @param noShips
     * @param rows
     * @param columns
     * @return scanList
     */
    @Override
    public List <Position> solve(List<Position> board, int noShips, int rows, int columns) {
        scanList = board;
        count = noShips;
        column = columns;
        i = 0;
        j = 0;
        var = 0;
        while(count > 0) {
            if(Character.compare(scanList.get(i).getType(), '.') == 0)
                scanList.get(i).setType('X');

            else if(Character.compare(scanList.get(i).getType(), 'X') == 0 || Character.compare(scanList.get(i).getType(), '+') == 0)
                j++;

            else {
                count--;
                scanList.get(i).setType('+');
                markDiagonals(i);
                k = i + columns;
                checkEast();
                checkSouth();
            }

            i++;
        }

        noScans = (i + var) - j;
        return scanList;
    }

    /**
     * When ships is found mark diagonals
     * as empty
     * @param index
     */
    public void markDiagonals(int index) {
        if(index < scanList.size() - column) {
            if (index % column == 0)
                scanList.get(index + (column + 1)).setType('X');

            else if (index % column == column - 1)
                scanList.get(index + (column - 1)).setType('X');

            else {
                scanList.get(index + (column - 1)).setType('X');
                scanList.get(index + (column + 1)).setType('X');
            }
        }
    }

    /**
     * Ship is found
     * Checks the next East position
     * If ship found keep checking
     */
    public void checkEast() {
        if(scanList.get(++i).getY() < column) {
            if(Character.compare(scanList.get(i).getType(), '.') == 0)
                scanList.get(i).setType('X');

            else if(Character.compare(scanList.get(i).getType(), 'X') == 0 || Character.compare(scanList.get(i).getType(), '+') == 0)
                j++;

            else {
                count--;
                scanList.get(i).setType('+');
                markDiagonals(i);
                if(count == 0)
                    return;
                checkEast();
            }
        }
    }

    /**
     * Ship is found
     * Checks the next South position
     * If ship found keep checking
     */
    public void checkSouth() {
        if(k < scanList.size()) {
            if(Character.compare(scanList.get(k).getType(), '.') == 0)
                scanList.get(i).setType('X');

            else if(Character.compare(scanList.get(k).getType(), 'X') == 0 || Character.compare(scanList.get(k).getType(), '+') == 0) {
                var++;
                j++;
            }

            else {
                count--;
                scanList.get(k).setType('+');
                var++;

                markDiagonals(k);

                if(count == 0)
                    return;

                k += column;
                checkSouth();
            }
        }
    }

    /**
     * @return noScans
     */
    @Override
    public int noScans() {
        return this.noScans;
    }
}
