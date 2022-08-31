import java.io.Serializable;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Car implements Serializable {

    private static final long serialVersionUID = 1L;
    String number;
    String owner;
    private String dateStart;
    private String dateEnd;
    private double pricePerHour;

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


    public static boolean validateNumber(double number) {
        return number > 0;
    }

    public static boolean validateOwner(String owner) {
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

    public static boolean isDateValid(String date) {
        DateFormat df = new SimpleDateFormat(DATE_FORMAT);


        try {
            df.parse(date);
        } catch (ParseException e) {
            System.out.println(e);
        }
        return false;
    }

    public static Car read(String[] args) throws CustomException {
        Car car = new Car();

        car.number = args[0];

        String str = args[1];
        if(!validateOwner(str)) {
            throw new CustomException("wrong owner's name format");
        }
        car.owner = str;

        str = args[2];
        if (isDateValid(str))
            throw new CustomException("invalid format of date");
        car.dateStart = str;

        str = args[3];
        if (isDateValid(str))
            throw new CustomException("invalid format of date");
        car.dateEnd = str;

        double tmp = Double.parseDouble(args[4]);
        if (!validateNumber(tmp)) {
            throw new CustomException("wrong money format");
        }
        car.pricePerHour = Double.parseDouble(args[4]);

        if (car.getDuration() <= 0) {
            throw new CustomException("start time < end time...");
        }
        return car;
    }

    public Car() {}

    public String toString() {
            return  number + "|"
                    + owner + "|"
                    + dateStart + "|"
                    + dateEnd + "|"
                    + getDuration() + "|"
                    + pricePerHour;

    }
}