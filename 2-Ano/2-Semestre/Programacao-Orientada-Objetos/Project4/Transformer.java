import java.util.Locale;
import java.util.Scanner;

public class Transformer {
    static Scanner sc = new Scanner(System.in);//.useLocale(Locale.ENGLISH);


    public static void check(double idObject) {
        if (idObject <= 2) {
            sc.close();

            System.out.println("Error");
            System.exit(0);
        }
    }

    public static void main(String[] args) {
        int idObject = sc.nextInt();
        check(idObject);
        double[] coordinates = new double[idObject];
        for (int i = 0; i < idObject; i++)
            coordinates[i] = sc.nextDouble();
        Point vector = new Point(sc.nextDouble(), sc.nextDouble());
        double angle = sc.nextDouble();
        sc.close();
        GeometricFigure gf = null;
        if (idObject == 3)
            gf = new Circle(coordinates);
        else if (idObject == 4)
            gf = new LineSegment(coordinates);
        else
            gf = new Polygon(coordinates);
        Point center = gf.centroid();
        System.out.println(center.pointoString());

        System.out.println(String.format("%.2f", gf.getArea()));

        System.out.println(gf);

        gf.move(vector.getX(), vector.getY());
        if (idObject != 3)
            gf.rotate(angle);
        System.out.println(gf);
    }
}