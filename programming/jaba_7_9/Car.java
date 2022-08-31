import java.io.PrintStream;
import java.io.Serializable;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Car implements Serializable {

    private static final long serialVersionUID = 1L;
    String number;
    static final String P_number = "number";
    String owner;
    String dateStart;
    String dateEnd;
    String pricePerHour;

    public long getDuration()  {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat(
                    "dd-MM-yyyy HH:mm");

            // parse method is used to parse
            // the text from a string to
            // produce the date
            Date d1 = sdf.parse(dateStart);
            Date d2 = sdf.parse(dateEnd);

            // Calucalte time difference
            // in milliseconds
            return d2.getTime() - d1.getTime();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }


	/*
	 * private boolean validateNumber(String number) { char[] chars =
	 * number.toCharArray(); for (char c : chars) { if (!Character.isDigit(c))
	 * return false; } return true; }
	 */

    private boolean validateOwner(String owner) {
        if (owner.contains(" ")) {
            char[] chars = owner.replaceAll(" ", "").toCharArray();
            for (char c : chars) {
                if (!Character.isLetter(c))
                    return false;
            }
            return true;
        }
        return false;
    }

    final static String DATE_FORMAT = "dd-MM-yyyy HH:mm";

    public static void isDateValid(String date) {
        DateFormat df = new SimpleDateFormat(DATE_FORMAT);

        try {
            df.parse(date);
        } catch (ParseException e) {
            System.out.println(e);
        }
    }

    public static Car read(Scanner fin, PrintStream carOut) {
        Car car = new Car();
        String str;

        car.number = fin.nextLine();
        if (!fin.hasNextLine()) {
            return null;
        }

        str = fin.nextLine();
        if (!car.validateOwner(str)) {
            throw new IllegalArgumentException("wrong owner's name format");
        }
        car.owner = str;

        str = fin.nextLine();
        isDateValid(str);
        car.dateStart = str;

        str = fin.nextLine();
        isDateValid(str);
        car.dateEnd = str;

        str = fin.nextLine();
        if (Double.parseDouble(str) < 0) {
            throw new IllegalArgumentException("wrong money format");
        }
        car.pricePerHour = str;
        return car;
    }

    public Car() {}

        public static Boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(P_number, fin, out);
    }

    static Boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public String toString() {
            return  number + "|"
                    + owner + "|"
                    + dateStart + "|"
                    + dateEnd + "|"
                    + getDuration() + "|"
                    + pricePerHour;

    }
}