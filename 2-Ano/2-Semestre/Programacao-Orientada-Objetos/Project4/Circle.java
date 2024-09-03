public class Circle extends GeometricFigure {
    private double r;

    public Circle(double[] coordinates) {
        super(coordinates);
        this.r = coordinates[2];
    }

    public double getRadius() {
        return this.r;
    }

    public double getArea() {
        return Math.PI * (r*r);
    }

    public Point centroid() {
        return arr[0];
    }

    public Point[] points() {
        return arr;
    }

    public String toString() {
        return String.format("Circle((%.2f,%.2f),%.2f)", arr[0].getX(), arr[0].getY(), this.r);
    }
}
