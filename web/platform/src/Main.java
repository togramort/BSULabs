//import WaitNotifyVersion.*;
import SyncObjectsVersion.*;

import java.util.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("Welcome to the child railway simulation.\nIt consist of 4 stations. Main cycle route is Minsk - Moscow - Kiev - Warsaw.");
        Thread.sleep(1000);

        Route forward = new Route("Forward", RouteDirection.Forward);
        Route backward = new Route("Backward", RouteDirection.Backward);

        Station first = new Station("Minsk");
        Station second = new Station("Moscow");
        Station third = new Station("Kiev");
        Station fourth = new Station("Warsaw");

        forward.addNewRouteNode(first);
        forward.addNewRouteNode(second);
        forward.addNewRouteNode(third);
        forward.addNewRouteNode(fourth);

        backward.addNewRouteNode(fourth);
        backward.addNewRouteNode(third);
        backward.addNewRouteNode(second);
        backward.addNewRouteNode(first);

        Passenger passenger1 = new Passenger("John", null, first);
        Passenger passenger2 = new Passenger("Sam", null, fourth);
        Passenger passenger3 = new Passenger("Sarah", null, second);
        Passenger passenger4 = new Passenger("Mallory", null, third);

        Train firstTrain = new Train(3000, 7000, forward, "Martin");
        Train secondTrain = new Train(2000, 4000, backward, "Adler");

        Thread t1 = new Thread(firstTrain);
        Thread t2 = new Thread(secondTrain);

        Thread t3 = new Thread(passenger1);
        Thread t4 = new Thread(passenger2);
        Thread t5 = new Thread(passenger3);
        Thread t6 = new Thread(passenger4);

        t1.start();
        t2.start();
        t3.start();
        t4.start();
        t5.start();
        t6.start();
        Scanner scanner = new Scanner(System.in);
        while (true){
            if (scanner.nextInt() == 0){
                firstTrain.finishThread();
                secondTrain.finishThread();
                passenger1.finishThread();
                passenger2.finishThread();
                passenger4.finishThread();
                passenger3.finishThread();
                break;
            }
        }
    }
}