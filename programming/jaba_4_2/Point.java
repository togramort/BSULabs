public class Point {
    protected double x;
    protected double y;

    //����������� � �����������.
    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    //����������� ����� ����� �������.
    public static double distance(Point p1, Point p2) {
        double xDistance = Math.abs(Math.abs(p1.x) - Math.abs(p2.x));
        double yDistance = Math.abs(Math.abs(p1.y) - Math.abs(p2.y));
        return Math.sqrt(xDistance * xDistance + yDistance * yDistance);
    }
}