package model;

public class Prism {
    private final Triangle base;
    private final double height;

    public Triangle getBase() {
        return base;
    }

    public double getHeight() {
        return height;
    }

    /**
     * Constructs a prism with a base 'base' and height 'height'
     * @param base a base of a prism
     * @param height a height of a prism
     */
    public Prism(Triangle base, double height) {
        this.base = base;
        this.height = height;
    }

    /**
     * Constructs a prism with a base 'base' and height 'height'
     * @param a the first side of a prism base
     * @param b the second side of a prism base
     * @param c the third side of a prism base
     * @param height a height of a prism
     */
    public Prism(double height, double a, double b, double c) {
        this.height = height;
        this.base = new Triangle(a, b, c);
    }

    @Override
    public String toString() {
        return "prism { " +
                "height = " + height + ",\nbase: " +
                this.base.toString() + " }";
    }
}