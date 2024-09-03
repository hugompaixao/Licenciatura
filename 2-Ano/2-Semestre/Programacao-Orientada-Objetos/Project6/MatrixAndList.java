
import java.util.ArrayList;
import java.util.List;

public class MatrixAndList extends SpotTheShips {

    /**
     * Put all possible strategies into List strategies
     */
    public static void fillStrategies() {
        strategies = new ArrayList<String>(3);
        strategies.add("linear");
        strategies.add("smart");
        strategies.add("prob");
    }

    /**
     * Put all possible orientations into List orientations
     */
    public static void fillOrientations() {
        orientations = new ArrayList<Character>(4);
        orientations.add('N');
        orientations.add('S');
        orientations.add('O');
        orientations.add('E');
    }

    /**
     * Fill Matrix with a dot in every position
     * @param matrix
     * @param row - number of rows
     * @param column - number of columns
     */
    public static void fillMatrix(char[][] matrix, int row, int column) {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
                matrix[i][j] = '.';
    }

    /**
     * Given the characteristic to place the ships in matrix send the data
     * to place the ship to the right method
     * if the boat move in columns send to place OE if moves in rows sends to NS
     * @param matrix
     * @param row - array with row position for ship
     * @param column - array with column position for ship
     * @param shipSize
     * @param orientation If ship > size 1, gives the direction where the rest of the ship is
     */
    public static void placeShips(char[][] matrix, int[] row, int[] column, int[] shipSize, char[] orientation) {
        for(int i = 0; i < row.length; i++) {
            if(Character.compare(orientation[i], 'N') == 0 || Character.compare(orientation[i], 'S') == 0)
                placeShipsNS(matrix, orientation[i], row[i], column[i], shipSize[i]);
            if(Character.compare(orientation[i], 'O') == 0 || Character.compare(orientation[i], 'E') == 0)
                placeShipsOE(matrix, orientation[i], row[i], column[i], shipSize[i]);
        }
    }

    /**
     * After the selection in placeShips it will check if to place boat
     * will increment row or decrement
     * @pre - Orientation must equal 'N' or 'S'
     * @param matrix
     * @param orientation - direction for the rest of ship if size > 1
     * @param row - row index to where to place ship
     * @param column - column index to where to place ship
     * @param shipSize
     */
    public static void placeShipsNS(char[][] matrix, char orientation, int row, int column, int shipSize) {
        int var = 1;
        if(Character.compare(orientation, 'N') == 0)
            var = -1;
        for(int i = 0; i < shipSize; i++) {
            matrix[row][column] = 'O';
            row += var;
        }
    }

    /**
     * After the selection in placeShips it will check if to place boat
     * will increment column or decrement
     * @pre - Orientation must equal 'O' or 'E'
     * @param matrix
     * @param orientation- direction for the rest of ship if size > 1
     * @param row - row index to where to place ship
     * @param column - column index where to place ship
     * @param shipSize
     */
    public static void placeShipsOE(char[][] matrix, char orientation, int row, int column, int shipSize) {
        int var = 1;
        if(Character.compare(orientation, 'O') == 0)
            var = -1;
        for(int i = 0; i < shipSize; i++) {
            matrix[row][column] = 'O';
            column += var;
        }
    }

    /**
     * changes matrix into object positions and builds a list of objects
     * @param row
     * @param column
     * @param matrix
     * @param board
     */
    public static void putMatrixInList(int row, int column, char[][] matrix, List<Position> board) {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
                board.add(new Position(i, j, matrix[i][j]));
    }
}
