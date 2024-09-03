import java.util.Scanner;

public class PlanetClash {

    public static void checkRadiusOk(Point3D p, Sphere s) {
        if(s.getRadius() < 0) {
            System.out.println(String.format("iv: C(%.1f,%.1f,%.1f) r=%.1f", p.getX(), p.getY(), p.getZ(), s.getRadius()));
            System.exit(0);
        }
    }

    public static void main(String[] argv) {
        Scanner sc = new Scanner(System.in);

        Point3D p1 = new Point3D(sc.nextDouble(), sc.nextDouble(), sc.nextDouble());
        Sphere s1 = new Sphere(sc.nextDouble());
        Point3D p2 = new Point3D(sc.nextDouble(), sc.nextDouble(), sc.nextDouble());
        Sphere s2 = new Sphere(sc.nextDouble());

        sc.close();

        checkRadiusOk(p1,s1);
        checkRadiusOk(p2,s2);

        System.out.println(String.format("%.2f",s1.volume()));
        System.out.println(String.format("%.2f",s2.volume()));

        double dist = p1.distance(p2);
        double rSum = s1.radiusSum(s2);

        if(dist > rSum) System.out.println("no collision");
        else System.out.println("collision");

    }
}
