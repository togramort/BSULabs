package com.company;

public class Main {

    public static void main(String[] args) {
        /*
        ln (1 + x) = x - x^2/2 + x^3/3 - x^4/4 + ...
        x, (-1,1]
        k, k > 1
*/
        if (args.length != 2) {
            System.err.println("Invalid number of arguments");
            System.exit(1);
        }

        double x = Double.parseDouble(args[0]);
        if (x > 1 || x <= -1) {
            System.err.println("Invalid argument: " + x);
            System.exit(1);
        }

        int k = Integer.parseInt(args[1]);
        if (k <= 1) {
            System.err.println("Invalid argument: " + k);
            System.exit(1);
        }

        double Eps = 1 / Math.pow(10, k + 1);
        double result = 0;
        double step = x;
        int n = 1;
        while (Math.abs(step) >= Eps) {
            result += step;
            ++n;
            step = step * (n - 1) / n * (-x);
        }

        String fmt = "%." + args[1] + "f\n";
        System.out.printf(fmt, result);
        System.out.printf(fmt, Math.log(1 + x));
        System.exit(0);
    }
}
