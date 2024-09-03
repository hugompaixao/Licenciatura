
import java.util.Scanner;

public class Craftsman {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int p = sc.nextInt();

        sc.nextLine();

        String message = sc.nextLine();

        sc.close();

        String finalMessage = EncrypterSmith.smith(message, n, p);
        System.out.println(finalMessage);
    }
}
