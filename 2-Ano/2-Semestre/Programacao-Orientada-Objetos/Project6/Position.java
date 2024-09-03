
import java.util.Objects;

public class Position {
    private int x, y;
    private char type;

    /**
     * Object constructor
     * @param x
     * @param y
     * @param type
     */
    public Position(int x, int y, char type) {
        this.x = x;
        this.y = y;
        this.type = type;
    }

    /**
     * @return x
     */
    public int getX() {
        return this.x;
    }

    /**
     * @return y
     */
    public int getY() {
        return this.y;
    }

    /**
     * @return type
     */
    public char getType() {
        return this.type;
    }

    /**
     * set new type for object
     * @param type
     */
    public void setType(char type) {
        this.type = type;
    }

    /**
     * @param o
     * @return boolean
     */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        Position position = (Position) o;
        return x == position.x && y == position.y && type == position.type;
    }

    /**
     * @return
     */
    @Override
    public int hashCode() {
        return Objects.hash(x, y, type);
    }
}
