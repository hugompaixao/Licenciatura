public abstract class GeometricFigure {
    public Point[] arr;

    public GeometricFigure(double[] coordinates) {
        int length = coordinates.length;
        if(coordinates.length == 3)
            length--;

        this.arr = new Point[length/2];
        int j = 0;
        for(int i = 0; i < length; i += 2) {
            arr[j] = new Point(coordinates[i], coordinates[i+1]);
            j++;
        }
    }

    public void move(double dx, double dy) {
        for(int i = 0; i < arr.length; i++)
            arr[i].move(dx,dy);
    }

    public void rotate(double angle) {
        Point center = this.centroid();
        for(int i = 0; i < arr.length; i++)
            arr[i].rotateAround(center, angle);
    }

    public abstract Point centroid();

    public abstract Point[] points();

    public abstract double getArea();

    public abstract String toString();
}

