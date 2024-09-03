public class LineSegment extends GeometricFigure {
    public LineSegment(double[] coordinates) {
        super(coordinates);
    }

    public Point centroid() {
        double mx = (arr[0].getX() + arr[1].getX()) / 2;
        double my = (arr[0].getY() + arr[1].getY()) / 2;

        Point m = new Point(mx, my);
        return m;
    }

    public Point[] points() {
        return arr;
    }

    public double getArea() {
        return 0;
    }

    public String toString() {
        return String.format("Segment((%.2f,%.2f),(%.2f,%.2f))", arr[0].getX(), arr[0].getY(), arr[1].getX(), arr[1].getY());
    }
}
