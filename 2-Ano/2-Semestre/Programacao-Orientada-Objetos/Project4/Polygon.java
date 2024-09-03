public class Polygon extends GeometricFigure{
    public Polygon(double[] coordinates) {
        super(coordinates);
    }

    public double getArea() {
        double area = 0.0;
        int j = arr.length-1;
        for(int i = 0; i < arr.length; i++) {
            area += (arr[j].getX() + arr[i].getX()) * (arr[j].getY() - arr[i].getY());
            j = i;
        }
        return Math.abs(area / 2);
    }

    public Point centroid() {
        double x = 0, y = 0, sum = 0, tmp;
        for (int i = 0, j; i < arr.length; i++){
            if (i + 1 == arr.length)
                j = 0;
            else
                j = i + 1;

            tmp = ((arr[i].getX() * arr[j].getY()) - (arr[j].getX() * arr[i].getY()));
            sum += tmp;

            x += ( arr[i].getX() + arr[j].getX() ) * tmp;
            y += ( arr[i].getY() + arr[j].getY() ) * tmp;
        }

        x /= 3 * sum;
        y /= 3 * sum;

        return new Point(x, y);
    }

    public Point[] points() {
        return arr;
    }

    public String toString() {
        String finall = "Polygon(";
        String end = ")";
        for(int i = 0; i < arr.length; i++) {
            finall += String.format("(%.2f,%.2f)", arr[i].getX(), arr[i].getY());
            if(i < arr.length-1)
                finall += ",";
        }
        finall += end;
        return finall;
    }
}