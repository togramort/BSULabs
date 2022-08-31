import java.io.Serializable;
import java.util.Scanner;

public class Car implements Serializable {

    String number;
    String owner;
    String dateStart;
    String timeStart;
    String dateEnd;
    String timeEnd;
    String pricePerHour;

    public static Car read(Scanner fin) {
        Car car = new Car();
        car.number = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.owner = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.dateStart = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.timeStart = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.dateEnd = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.timeEnd = fin.nextLine();
        if (!fin.hasNextLine()) return null;
        car.pricePerHour = fin.nextLine();
        return car;
    }

    public Car() {}

    public String toString() {
        return new String(
        		number + "|" +
        		owner + "|" +
                dateStart + "|" +
                timeStart + "|" +
                dateEnd + "|" +
                timeEnd + "|" +
                pricePerHour
        );
    }
}