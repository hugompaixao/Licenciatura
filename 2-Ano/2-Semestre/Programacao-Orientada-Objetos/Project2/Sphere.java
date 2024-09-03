
public class Sphere {
    private double r;

    public Sphere(double r) {
        this.r = r;
    }

    public double getRadius() {
        return r;
    }

    public double volume() {
        return (4.0/3) * Math.PI * (r*r*r);
    }

    public double radiusSum(Sphere s) {
        return r + s.r;
    }
}
