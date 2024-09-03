
public class Point3D {
    private double x,y,z;

    public Point3D(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getZ() {
        return z;
    }

    public double distance(Point3D p) {
        double dx = x - p.x;
        double dy = y - p.y;
        double dz = z - p.y;
        return Math.sqrt(dx*dx + dy*dy + dz*dz);
    }
}
