import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SmartTest {
    @Test
    public void solve() {
        int[] row1 = {1, 3};
        int[] column1 = {1, 3};
        int[] size1 = {4, 2};
        char[] orientation1 = {'E', 'S'};

        char[][] matrix1 = new char[5][6];
        MatrixAndList.fillMatrix(matrix1, 5, 6);
        MatrixAndList.placeShips(matrix1, row1, column1, size1, orientation1);

        List<Position> board1 = new ArrayList<>(5*6);
        MatrixAndList.putMatrixInList(5, 6, matrix1, board1);

        ISpotTheShips solve1 = new Smart();
        List<Position> list1 = solve1.solve(board1, 6, 5, 6);
        int scans1 = solve1.noScans();
        assertEquals(list1.size(), board1.size());
        assertEquals(18, scans1);

        int[] row2 = {0, 2, 2, 0, 1};
        int[] column2 = {0, 0, 5, 6, 3};
        int[] size2 = {2, 1, 5, 4, 1};
        char[] orientation2 = {'E', 'E', 'E', 'E', 'E'};

        char[][] matrix2 = new char[3][10];
        MatrixAndList.fillMatrix(matrix2, 3, 10);
        MatrixAndList.placeShips(matrix2, row2, column2, size2, orientation2);

        List<Position> board2 = new ArrayList<>(3*10);
        MatrixAndList.putMatrixInList(3, 10, matrix2, board2);

        ISpotTheShips solve2 = new Smart();
        List<Position> list2 = solve2.solve(board2, 13, 3, 10);
        int scans2 = solve2.noScans();
        assertEquals(list2.size(), board2.size());
        assertEquals(20, scans2);
    }
}
