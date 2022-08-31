import java.util.Iterator;

public class Trapezium extends Figure implements Comparable<Trapezium>, Iterator<Object>, Iterable<Object> {
    double h, m;
    Color fill, outline;

    // Функция, проверяющая, образуют ли точки трапецию.
    /* Для корректной работы необходимо вводить точки в необходимой последовательности,например:
       четырехугольник ABCD исследуется. Вводим в конструктор точки в последовательности A, B, C, D.*/

    boolean isTrapezium(Point A, Point B, Point C, Point D) {
        return koef(B, C) == koef(A, D) || koef(A, B) == koef(D, C);
    }

    static double koef(Point p1, Point p2) {
        if (p1.x == p2.x) {
            return Double.POSITIVE_INFINITY;
        }
        return (p1.y - p2.y) / (p1.x - p2.x);
    }

    // Конструктор

    double a, b, c, d;
    Trapezium(Point A, Point B, Point C, Point D, Color _fill, Color _outline) throws Exception {
        if (!isTrapezium(A, B, C, D)) {
            throw new Exception("Current Points A, B, C, D dont create trapezium");
        } else {
            a = Point.distance(A, B);
            b = Point.distance(B, C);
            c = Point.distance(C, D);
            d = Point.distance(D, A);
            h = Math.sqrt(Math.pow(a, 2) - Math.pow((Math.pow(d - b, 2) + Math.pow(a, 2) - Math.pow(c, 2)) / (2 * (d - b)), 2));
            m = (b + d) / 2;
            fill = _fill;
            outline = _outline;
        }
    }

    Trapezium(String str) throws Exception {
        if (str == null) {
            throw new Exception("Null pointer passed for str");
        }

        String[] parts = str.split("\\s");
        double bufferHeight = Double.parseDouble(parts[0]);
        double bufferMiddle = Double.parseDouble(parts[1]);
        int bufferFill = Integer.parseInt(parts[2]);
        int bufferOutline = Integer.parseInt(parts[3]);

        if ((bufferHeight > 0)) {
            h = bufferHeight;
        }
        if ((bufferMiddle > 0)) {
            m = bufferMiddle;
        }
        if (bufferFill == 1) {
            fill = Color.RED;
        }
        if (bufferFill == 2) {
            fill = Color.ORANGE;
        }
        if (bufferFill == 3) {
            fill = Color.YELLOW;
        }
        if (bufferFill == 4) {
            fill = Color.GREEN;
        }
        if (bufferFill == 5) {
            fill = Color.LIGHT_BLUE;
        }
        if (bufferFill == 6) {
            fill = Color.BLUE;
        }
        if (bufferFill == 7) {
            fill = Color.PURPLE;
        }

        if (bufferOutline == 1) {
            outline = Color.RED;
        }
        if (bufferOutline == 2) {
            outline = Color.ORANGE;
        }
        if (bufferOutline == 3) {
            outline = Color.YELLOW;
        }
        if (bufferOutline == 4) {
            outline = Color.GREEN;
        }
        if (bufferOutline == 5) {
            outline = Color.LIGHT_BLUE;
        }
        if (bufferOutline == 6) {
            outline = Color.BLUE;
        }
        if (bufferOutline == 7) {
            outline = Color.PURPLE;
        }
    }

    // Методы абстрактного класса Figure.
    double perimeter() {
        return a + b + c + d;
    }

    double area() {
        return m * h;
    }

    static int sortMarker = 0;

    public void setMarker(int inMarker) {
        if ((inMarker == 0) || (inMarker == 1) || (inMarker == 2) || (inMarker == 3)) {
            sortMarker = inMarker;
        }
    }

    @Override
    public int compareTo(Trapezium trap_1) {
        switch (sortMarker) {
            case 0:
                return Double.compare(h, trap_1.h);
            case 1:
                return Double.compare(m, trap_1.m);
            case 2:
                return Double.compare(fill.GetValue(), trap_1.fill.GetValue());
            case 3:
                return Double.compare(outline.GetValue(), trap_1.outline.GetValue());
            default:
                return -1;
        }
    }

    private int iter = 0;

    @Override
    public boolean hasNext() {
        return iter <= 3;
    }

    public void reset() {
        iter = 0;
    }

    @Override
    public Object next() throws IndexOutOfBoundsException {
        if (iter == 0) {
            ++iter;
            return h;
        } else if (iter == 1) {
            ++iter;
            return m;
        } else if (iter == 2) {
            ++iter;
            return fill;
        } else if (iter == 3) {
            ++iter;
            return outline;
        } else {
            reset();
            return null;
        }
    }

    @Override
    public Iterator<Object> iterator() {
        return this;
    }

    @Override
    public String toString() {
        return ("Trapezium height: " + h + "\nTrapezium middle: " + m + "\nTrapezium fill: " + fill + "\nTrapezium outline: " + outline + "\n");
    }
}