import logic.TriangleLogic;
import model.Triangle;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        int n = 10;
        Triangle[] triangles = new Triangle[n];
        int[][] abc = {{3, 4, 5}, {4, 4, 4}, {2, 2, 3}, {6, 8, 10}, {7, 7, 7},
                {7, 7, 12}, {3, 8, 9}, {1, 1, 1}, {9, 9, 9}, {4, 5, 7}};
        for (int i = 0; i < n; i++) {
            triangles[i] = new Triangle(abc[i][0], abc[i][1], abc[i][2]);
        }
        int cntE = 0, cntI = 0, cntR = 0, cntA = 0;
        ArrayList<Triangle> rect = new ArrayList<>();
        ArrayList<Triangle> iso = new ArrayList<>();
        ArrayList<Triangle> equ = new ArrayList<>();
        ArrayList<Triangle> arb = new ArrayList<>();
        for (var tr : triangles) {
            if (tr.isRectangular()) {
                cntR++;
                rect.add(tr);
            } else if (tr.isIsosceles()) {
                cntI++;
                iso.add(tr);
            } else if (tr.isEquilateral()) {
                cntE++;
                equ.add(tr);
            } else {
                cntA++;
                arb.add(tr);
            }
        }

        System.out.println("isosceles triangles: " + cntI +
                "\nequilateral triangles: " + cntE +
                "\nrectangular triangles: " + cntR +
                "\narbitrary triangles: " + cntA);
        System.out.println("\nmin perimeters:");
        System.out.println(TriangleLogic.getMinPerimeter(iso).toString());
        System.out.println(TriangleLogic.getMinPerimeter(equ).toString());
        System.out.println(TriangleLogic.getMinPerimeter(rect).toString());
        System.out.println(TriangleLogic.getMinPerimeter(arb).toString());
        System.out.println("\nmax perimeters:");
        System.out.println(TriangleLogic.getMaxPerimeter(iso).toString());
        System.out.println(TriangleLogic.getMaxPerimeter(equ).toString());
        System.out.println(TriangleLogic.getMaxPerimeter(rect).toString());
        System.out.println(TriangleLogic.getMaxPerimeter(arb).toString());
        System.out.println("\nmin squares:");
        System.out.println(TriangleLogic.getMinSquare(iso).toString());
        System.out.println(TriangleLogic.getMinSquare(equ).toString());
        System.out.println(TriangleLogic.getMinSquare(rect).toString());
        System.out.println(TriangleLogic.getMinSquare(arb).toString());
        System.out.println("\nmax squares:");
        System.out.println(TriangleLogic.getMaxSquare(iso).toString());
        System.out.println(TriangleLogic.getMaxSquare(equ).toString());
        System.out.println(TriangleLogic.getMaxSquare(rect).toString());
        System.out.println(TriangleLogic.getMaxSquare(arb).toString());

        model.Pyramid p = new model.Pyramid(triangles[0], 15);
        System.out.println("\n" + p);

        model.Prism pr = new model.Prism(triangles[0], 13);
        System.out.println("\n" + pr);
    }
}