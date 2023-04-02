package model;

public class Triangle {
    private final double a;
    private final double b;
    private final double c;

    public double getA() {
        return a;
    }

    public double getB() {
        return b;
    }

    public double getC() {
        return c;
    }

    /**
     * Constructs a triangle by its sides
     * @param a the first side
     * @param b the second side
     * @param c the third side
     */
    public Triangle(double a, double b, double c) {
        assert a < b + c;
        assert b < a + c;
        assert c < a + b;
        this.a = a;
        this.b = b;
        this.c = c;
    }

    /**
     * Constructs an equilateral triangle with a side
     * @param a -- a side of a triangle
     */
    public Triangle(double a) {
        this.a = a;
        this.b = a;
        this.c = a;
    }

    /**
     * Determines if a triangle is equilateral
     * @return true if a triangle is equilateral, else returns false
     */
    public boolean isEquilateral() {
        return a == b && b == c;
    }

    /**
     * Determines if a triangle is isosceles
     * @return true if a triangle is isosceles, else returns false
     */
    public boolean isIsosceles() {
        return !isEquilateral() && (a == b || b == c || a == c);
    }

    /**
     * Determines if a triangle is rectangular
     * @return true if a triangle is rectangular, else returns false
     */
    public boolean isRectangular() {
        return (a * a + b * b == c * c) || (b * b + c * c == a * a) || (a * a + c * c == b * b);
    }

    @Override
    public String toString() {
        return "triangle { " +
                "a = " + a +
                ", b = " + b +
                ", c = " + c + " }";
    }
}