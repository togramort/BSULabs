package pack;

import java.util.Random;
import java.util.Date;

public class Main {

    static int n = 5;

    public static void main(String[] args) {
        Random rand = new Random((new Date()).getTime());

        Interval[] intervals = new Interval[n];
        intervals[0] = new Interval();

        for (int i = 1; i < n; ++i) {
            intervals[i] = new Interval(rand.nextDouble(), rand.nextDouble());
            intervals[i].Print(i);
        }

        int j = rand.nextInt(n);
        double distance = rand.nextDouble();
        intervals[j].MoveLeft(distance);
        System.out.println("The interval #" + j + " has been moved to the left by a distance of " + distance);
        intervals[j].Print(j);

        j = rand.nextInt(n);
        distance = rand.nextDouble();
        intervals[j].MoveRight(distance);
        System.out.println("The interval #" + j + " has been moved to the right by a distance of " + distance);
        intervals[j].Print(j);

        j = rand.nextInt(n);
        double factor = rand.nextDouble();
        intervals[j].Stretch(factor);
        System.out.println("The interval #" + j + " has been stretched by " + factor);
        intervals[j].Print(j);


        j = rand.nextInt(n);
        int k = rand.nextInt(n);
        System.out.println("The result of comparing interval #" + j + " and interval #" + k + " is " + Interval.Compare(intervals[j], intervals[k]));
        System.out.println();

        j = rand.nextInt(n);
        k = rand.nextInt(n);
        System.out.print("The result of adding interval #" + j + " to interval #" + k + " is ");
        intervals[j].Add(intervals[k]).Print();

        j = rand.nextInt(n);
        k = rand.nextInt(n);
        System.out.print("The result of subtracting interval #" + j + " from interval #" + k + " is ");
        intervals[j].Subtract(intervals[k]).Print();

        System.out.print("The result of subtracting interval #" + 1 + " from interval #" + 1 + " is ");
        intervals[1].Subtract(intervals[1]).Print();
    }
}