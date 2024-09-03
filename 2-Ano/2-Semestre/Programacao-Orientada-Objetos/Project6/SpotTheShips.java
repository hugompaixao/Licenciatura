
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class SpotTheShips {
    static Scanner sc = new Scanner(System.in);
    static List<String> strategies;
    static List <Character> orientations;

    /**
     * Receives all input, builds the board of ships and selects the strategy to use
     * @param args
     */
    public static void main(String[] args) {
        MatrixAndList.fillStrategies();
        MatrixAndList.fillOrientations();

        String strategy = InputCheckOutput.getCheckStrategy();

        int rows = InputCheckOutput.getCheckIntegers();
        int columns = InputCheckOutput.getCheckIntegers();
        int noShips = InputCheckOutput.getCheckIntegers();

        int[] row = new int[noShips];
        int[] column = new int[noShips];
        int[] shipSize = new int[noShips];
        char[] orientation = new char[noShips];

        for(int i = 0; i < noShips; i++) {
            row[i] = InputCheckOutput.getCheckIntegers();
            column[i] = InputCheckOutput.getCheckIntegers();
            shipSize[i] = InputCheckOutput.getCheckIntegers();
            orientation[i] = InputCheckOutput.getCheckOrientation();
        }

        char[][] matrix = new char[rows][columns];
        MatrixAndList.fillMatrix(matrix, rows, columns);
        MatrixAndList.placeShips(matrix, row, column, shipSize, orientation);

        List <Position> board = new ArrayList<>(rows*columns);
        MatrixAndList.putMatrixInList(rows, columns, matrix, board);

        int noShipsPositions = Arrays.stream(shipSize).sum();

        ISpotTheShips solve;
        if(strategy.equals("linear"))
            solve = new Linear();

        else if(strategy.equals("smart"))
            solve = new Smart();

        else
            solve = new Probabilistic();

        List <Position> scanList = solve.solve(board, noShipsPositions, rows, columns);
        int noScans = solve.noScans();

        InputCheckOutput.output(columns, noScans, scanList);
    }
}
