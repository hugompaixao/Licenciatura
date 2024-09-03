public class Point {
    private double x,y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public void move(double dx, double dy) {
        this.x = this.x + dx;
        this.y = this.y + dy;
    }

    public void rotateAround(Point center, double angle) {
        this.x = x - center.x;
        this.y = y - center.y;

        double rads = (angle * Math.PI) / 180;

        double tmpX = (this.x * Math.cos(rads)) - (this.y * Math.sin(rads));
        double tmpY = (this.x * Math.sin(rads)) + (this.y * Math.cos(rads));

        this.x = tmpX + center.x;
        this.y = tmpY + center.y;
    }

    public String pointoString() {
        return String.format("(%.2f,%.2f)", this.x, this.y);
    }
}
