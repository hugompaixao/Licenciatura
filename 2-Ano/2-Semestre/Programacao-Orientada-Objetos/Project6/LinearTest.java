import org.junit.Assert;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class LinearTest {
    @Test
    public void solve() {
        int[] row = {1, 3};
        int[] column = {1, 3};
        int[] size = {4, 2};
        char[] orientation = {'E', 'S'};

        char[][] matrix = new char[5][6];
        MatrixAndList.fillMatrix(matrix, 5, 6);
        MatrixAndList.placeShips(matrix, row, column, size, orientation);

        List <Position> board = new ArrayList<>(5*6);
        MatrixAndList.putMatrixInList(5, 6, matrix, board);

        ISpotTheShips solve1 = new Linear();
        List<Position> list1 = solve1.solve(board, 6, 5, 6);
        int scans = solve1.noScans();
        assertEquals(list1.size(), board.size());
        assertEquals(28, scans);

        int[] row2 = {1, 3};
        int[] column2 = {1, 0};
        int[] size2 = {1, 4};
        char[] orientation2 = {'E', 'E'};

        char[][] matrix2 = new char[4][4];
        MatrixAndList.fillMatrix(matrix2, 4, 4);
        MatrixAndList.placeShips(matrix2, row2, column2, size2, orientation2);

        List<Position> board2 = new ArrayList<>(4*4);
        MatrixAndList.putMatrixInList(4, 4, matrix2, board2);

        ISpotTheShips solve2 = new Linear();
        List<Position> list2 = solve2.solve(board2, 5, 4, 4);
        int scans2 = solve2.noScans();
        assertEquals(list2.size(), board2.size());
        assertEquals(16, scans2);
    }
}
