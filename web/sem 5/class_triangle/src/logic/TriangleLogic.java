package logic;

import model.Triangle;
import java.util.ArrayList;

public class TriangleLogic {
    /**
     * Calculates perimeter of the triangle
     * @param t triangle
     * @return perimeter
     */
    public static double calcPerimeter(Triangle t) {
        return t.getA() + t.getB() + t.getC();
    }

    /**
     * Calculates square of the triangle
     * @param t triangle
     * @return square
     */
    public static double calcSquare(Triangle t) {
        var p = TriangleLogic.calcPerimeter(t) / 2;
        return Math.sqrt(p * (p - t.getA()) * (p - t.getB()) * (p - t.getC()));
    }

    /**
     * Searches for a triangle with a maximal square in a list
     * @param triangles a list to search in
     * @return a triangle with a maximal square
     */
    public static Triangle getMaxSquare(ArrayList<Triangle> triangles) {
        double maxS = 0;
        Triangle trg = null;
        for (var tr : triangles) {
            if (TriangleLogic.calcSquare(tr) > maxS) {
                maxS = TriangleLogic.calcSquare(tr);
                trg = tr;
            }
        }
        return trg;
    }

    /**
     * Searches for a triangle with a minimal square in a list
     * @param triangles a list to search in
     * @return a triangle with a minimal square
     */
    public static Triangle getMinSquare(ArrayList<Triangle> triangles) {
        double minS = TriangleLogic.calcSquare(triangles.get(0));
        Triangle trg = triangles.get(0);
        for (var tr : triangles) {
            if (TriangleLogic.calcSquare(tr) < minS) {
                minS = TriangleLogic.calcSquare(tr);
                trg = tr;
            }
        }
        return trg;
    }

    /**
     * Searches for a triangle with a minimal perimeter in a list
     * @param triangles a list to search in
     * @return a triangle with a minimal perimeter
     */
    public static Triangle getMinPerimeter(ArrayList<Triangle> triangles) {
        double minP = TriangleLogic.calcPerimeter(triangles.get(0));
        Triangle trg = triangles.get(0);
        for (var tr : triangles) {
            if (TriangleLogic.calcPerimeter(tr) < minP) {
                minP = TriangleLogic.calcPerimeter(tr);
                trg = tr;
            }
        }
        return trg;
    }

    /**
     * Searches for a triangle with a maximal perimeter in a list
     * @param triangles a list to search in
     * @return a triangle with a maximal perimeter
     */
    public static Triangle getMaxPerimeter(ArrayList<Triangle> triangles) {
        double maxP = 0;
        Triangle trg = null;
        for (var tr : triangles) {
            if (TriangleLogic.calcPerimeter(tr) > maxP) {
                maxP = TriangleLogic.calcPerimeter(tr);
                trg = tr;
            }
        }
        return trg;
    }
}