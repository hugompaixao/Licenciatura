
import java.util.List;

public class InputCheckOutput extends SpotTheShips{

    /**
     * Reads string that will define the strategy used
     * if string read != from every strategy
     * exit program - print error message
     * @return String
     */
    public static String getCheckStrategy(){
        String inputStrategy = sc.next();
        if(!strategies.contains(inputStrategy)) {
            sc.close();
            System.out.println("Error, strategy no valid.");
            System.exit(1);
        }
        return inputStrategy;
    }

    /**
     * Reads every integer checks if any integer < 0 if so
     * exit program - print error message
     * @return int
     */
    public static int getCheckIntegers() {
        int integerInput = sc.nextInt();
        if(integerInput < 0) {
            sc.close();
            System.out.println("Error, negative integer entered.");
            System.exit(1);
        }
        return integerInput;
    }

    /**
     * Reads every char that defines orientation of the ships
     * if any char read != from N S O E
     * exit program - print error message
     * @return
     */
    public static char getCheckOrientation() {
        char inputOrientation = sc.next().charAt(0);
        if(!orientations.contains(inputOrientation)) {
            sc.close();
            System.out.println("Error, orientation not valid.");
            System.exit(1);
        }
        return inputOrientation;
    }

    /**
     * Print the result
     * @param columns
     * @param noScans
     * @param scanList
     */
    public static void output(int columns, int noScans, List <Position> scanList) {
        System.out.println(noScans);

        int i = 0;
        while(i < scanList.size()) {
            if(i != 0 && i % columns == 0)
                System.out.println();
            System.out.print(scanList.get(i).getType());
            i++;
        }
        System.out.println();
    }
}
