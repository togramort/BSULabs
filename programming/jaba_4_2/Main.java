import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        try {
            Point A = new Point(0, 0);
            Point B = new Point(3, 4);
            Point C = new Point(6, 4);
            Point D = new Point(9, 0);

            Trapezium trap_1 = new Trapezium(A, B, C, D, Color.RED, Color.BLUE);
            System.out.println("trap 1 h: " + trap_1.h);
            System.out.println("trap 1 m: " + trap_1.m);
            System.out.println("trap 1 area: " + trap_1.area());
            System.out.println("trap 1 perimeter: " + trap_1.perimeter());
            System.out.println("trap 1 fill: " + trap_1.fill);
            System.out.println("trap 1 outline: " + trap_1.outline);
            System.out.println();

            for(Object field : trap_1) {
                System.out.println("iter trap 1: " + field);
            }
            System.out.println();

            Point A_1 = new Point(0, 0);
            Point B_1 = new Point(6, 8);
            Point C_1 = new Point(11, 8);
            Point D_1 = new Point(19.94427, 0);
            Trapezium trap_2 = new Trapezium(A_1, B_1, C_1, D_1, Color.GREEN, Color.PURPLE);

            System.out.println("trap 2 h: " + trap_2.h);
            System.out.println("trap 2 m: " + trap_2.m);
            System.out.println("trap 2 area: " + trap_2.area());
            System.out.println("trap 2 perimeter: " + trap_2.perimeter());
            System.out.println("trap 2 fill: " + trap_2.fill);
            System.out.println("trap 2 outline: " + trap_2.outline);
            System.out.println();

            trap_2.setMarker(1);
            System.out.println("comp trap 2 and 1 by col out: " + trap_2.compareTo(trap_1));
            System.out.println();

            Trapezium trap_3 = new Trapezium("20 5 7 1");
            Trapezium trap_4 = new Trapezium("19 19 4 3");
            Trapezium trap_5 = new Trapezium("99 20 2 5");
            System.out.println("trap 3 h: " + trap_3.h);
            System.out.println("trap 3 m: " + trap_3.m);
            System.out.println("trap 3 fill: " + trap_2.fill);
            System.out.println("trap 3 outline: " + trap_3.outline);
            System.out.println();

            Trapezium[] sortArray = new Trapezium[5];
            sortArray[0] = trap_1;
            sortArray[1] = trap_2;
            sortArray[2] = trap_3;
            sortArray[3] = trap_4;
            sortArray[4] = trap_5;

            Trapezium.sortMarker = 3;
            Arrays.sort(sortArray);
            System.out.println("sorted: ");
            for (int i = 0; i < 5; i++) {
                System.out.println(sortArray[i]);
            }

        } catch (Exception excp) {
            excp.printStackTrace();
        }
    }
}