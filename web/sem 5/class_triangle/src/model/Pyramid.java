package model;

public class Pyramid {
    private final Triangle base;
    private final double height;

    public Triangle getBase() {
        return base;
    }

    public double getHeight() {
        return height;
    }

    /**
     * Constructs a pyramid with a base 'base' and height 'height'
     * @param base a base of a prism
     * @param height a height of a prism
     */
    public Pyramid(Triangle base, double height) {
        this.base = base;
        this.height = height;
    }

    /**
     * Constructs a pyramid with a base 'base' and height 'height'
     * @param a the first side of a pyramid base
     * @param b the second side of a pyramid base
     * @param c the third side of a pyramid base
     * @param height a height of a pyramid
     */
    public Pyramid(double height, double a, double b, double c) {
        this.height = height;
        this.base = new Triangle(a, b, c);
    }

    @Override
    public String toString() {
        return "pyramid { " +
                "height = " + height + ",\nbase: " +
                this.base.toString() + " }";
    }
}