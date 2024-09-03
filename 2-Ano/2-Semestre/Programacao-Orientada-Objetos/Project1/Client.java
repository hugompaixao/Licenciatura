
import java.util.Scanner;

public class Client {

    public static void main(String[] arvg) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        sc.nextLine();
        if(n < 2) { sc.close(); return; }

        double[] arr = new double[n*2];
        int i = 0;
        while(i < n*2) {
            arr[i++] = sc.nextDouble();
        }

        sc.close();

        double distance = 0.0;

        for(int j = 1; j < arr.length - 1; j += 2) {
            Point p1 = new Point(arr[j-1], arr[j]);
            Point p2 = new Point(arr[j+1], arr[j+2]);
            distance += p1.distance(p2);
        }

        System.out.println(String.format("%.2f", distance));
    }
}
