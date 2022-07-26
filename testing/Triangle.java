package com.company;

import java.util.Arrays;

public class Triangle {

    private final int[] sides;

    public boolean IsIsosceles() {
        return sides[0] == sides[1] || sides[1] == sides[2] || sides[0] == sides[2];
    }

    public boolean IsEquilateral() {
        return sides[0] == sides[1] && sides[1] == sides[2];
    }

    public int Perimeter() throws Exception {
        long res = (long) sides[0] + sides[1] + sides[2];
        if (res > Integer.MAX_VALUE) {
            throw new IllegalArgumentException("perimeter is out of integer");
        }
        return (int) res;
    }

    public float Square() throws Exception {
        double res;
        if (IsEquilateral()) {
            res = (double) sides[0] * (double) sides[0] * Math.sqrt(3) / 4;
        } else {
            res = Math.sqrt((double) Perimeter() * (double) (Perimeter() - 2 * sides[0]) * (Perimeter() - 2 * sides[1]) * (Perimeter() - 2 * sides[2])) / 4;
        }
        if (res > Float.MAX_VALUE) {
            throw new IllegalArgumentException("square is out of float");
        }
        return (float) res;
    }

    public Triangle(int side_1, int side_2, int side_3) throws Exception {
        if (side_1 <= 0 || side_2 <= 0 || side_3 <= 0) {
            throw new IllegalArgumentException("sides must be positive");
        }
        int[] res = new int[3];
        res[0] = side_1;
        res[1] = side_2;
        res[2] = side_3;
        Arrays.sort(res);
        if (res[2] >= res[1] + res[0])
            throw new IllegalArgumentException("this triangle doesn't exist");
        sides = res;
    }

    @Override
    public String toString() {
        String type;
        if (IsEquilateral()) {
            type = "equilateral";
        } else if (IsIsosceles()) {
            type = "isosceles";
        } else {
            type = "versatile";
        }
        try {
            return "triangle:" +
                    "\nsides = " + Arrays.toString(sides) +
                    "\nP = " + Perimeter() +
                    "\nS = " + Square() +
                    "\ntype = " + type;
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return "";
    }
}