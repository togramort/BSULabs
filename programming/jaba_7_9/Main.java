import java.io.*;
import java.text.ParseException;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        try {
            if (args.length >= 1) {
                switch (args[0]) {
                    case "-?":
                    case "-h":
                        System.out.println(
                                "Syntax:\n" +
                                        "\t-a  [file [encoding]] - append data\n" +
                                        "\t-az [file [encoding]] - append data, compress every record\n" +
                                        "\t-d                    - clear all data\n" +
                                        "\t-dk  {n|o|d} key      - clear data by key\n" +
                                        "\t-p                    - print data unsorted\n" +
                                        "\t-ps  {n|o|d}          - print data sorted by number/owner/duration \n" +
                                        "\t-psr {n|o|d}          - print data reverse sorted by number/owner/duration\n" +
                                        "\t-f   {n|o|d} key      - find record by key\n" +
                                        "\t-fr  {n|o|d} key      - find records > key\n" +
                                        "\t-fl  {n|o|d} key      - find records < key\n" +
                                        "\t-?, -h                - command line syntax\n"
                        );

                        break;
                    case "-a":
                        appendFile(args, false);
                        break;
                    case "-az":
                        appendFile(args, true);
                        break;
                    case "-p":
                        printFile();
                        break;
                    case "-ps":
                        if (!printFile(args, false)) {
                            System.exit(1);
                        }
                        break;
                    case "-psr":
                        if (!printFile(args, true)) {
                            System.exit(1);
                        }
                        break;
                    case "-d":
                        // delete files
                        if (args.length != 1) {
                            System.err.println("Invalid number of arguments");
                            System.exit(1);
                        }
                        deleteFile();
                        break;
                    case "-dk":
                        if (!deleteFile(args)) {
                            System.exit(1);
                        }
                        break;
                    case "-f":
                        if (!findByKey(args)) {
                            System.exit(1);
                        }
                        break;
                    case "-fr":
                        // Find record(s) by key large than key
                         if (!findByKey(args, true)) {
                            System.exit(1);
                        }
                        break;
                    case "-fl":
                        // Find record(s) by key less then key
                        if (!findByKey(args, false)) {
                            System.exit(1);
                        }
                        break;
                    default:
                        System.err.println("Option is not realised: " + args[0]);
                        System.exit(1);
                }
            } else {
                System.err.println("Main: Nothing to do! Enter -? for options");
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            e.printStackTrace();
            System.exit(1);
        }
        System.err.println( "Main finished..." );
        System.exit(0);
    }

    static final String filename = "Cars.dat";
    static final String filenameBak = "Cars.~dat";
    static final String idxname = "Cars.idx";
    static final String idxnameBak = "Cars.~idx";

    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream carOut = System.out;

    static Car readCar(Scanner fin) {
        return Car.nextRead(fin, carOut)
                ? Car.read(fin, carOut) : null;
    }

    private static void deleteBackup() {
        new File(filenameBak).delete();
        new File(idxnameBak).delete();
    }

    static void deleteFile() {
        deleteBackup();
        new File(filename).delete();
        new File(idxname).delete();
    }

    private static void backup() {
        deleteBackup();
        new File(filename).renameTo(new File(filenameBak));
        new File(idxname).renameTo(new File(idxnameBak));
    }


    static boolean deleteFile(String[] args) throws ClassNotFoundException, IOException, KeyNotUniqueException, ParseException {
        //-dk  {n|o|d} key      - clear data by key
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }

        long[] poss = null;
        try (Index idx = Index.load(idxname)) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            if (!pidx.contains(args[2])) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            poss = pidx.get(args[2]);
        }
        backup();
        Arrays.sort(poss);
        try (Index idx = Index.load(idxname);
             RandomAccessFile fileBak = new RandomAccessFile(filenameBak, "rw");
             RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            boolean[] wasZipped = new boolean[]{false};
            long pos;
            while ((pos = fileBak.getFilePointer()) < fileBak.length()) {
                Car car = (Car)
                        Buffer.readObject(fileBak, pos, wasZipped);
                if (Arrays.binarySearch(poss, pos) < 0) { // if not found in deleted
                    long ptr = Buffer.writeObject(file, car, wasZipped[0]);
                    idx.put(car, ptr);
                }
            }
        }
        return true;
    }

    static void appendFile(String[] args, Boolean zipped)
            throws IOException, ClassNotFoundException,
            KeyNotUniqueException, ParseException {
        if (args.length >= 2) {
            FileInputStream stdin = new FileInputStream(args[1]);
            System.setIn(stdin);
            if (args.length == 3) {
                encoding = args[2];
            }
            // hide output:
            carOut = new PrintStream("null");
        }
        appendFile(zipped);
    }

    static void appendFile(Boolean zipped)
            throws IOException, ClassNotFoundException,
            KeyNotUniqueException, ParseException {
        Scanner fin = new Scanner(System.in, encoding);
        carOut.println("Enter car data: ");
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            for (; ; ) {
                Car car = readCar(fin);
                if (car == null)
                    break;
                idx.test(car);
                long pos = Buffer.writeObject(raf, car, zipped);
                idx.put(car, pos);
                if (fin.hasNextLine()) {
                    fin.nextLine();
                }
            }
        }
    }

    private static void printRecord(RandomAccessFile raf, long pos)
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[]{false};
        Car car = (Car) Buffer.readObject(raf, pos, wasZipped);
        if (wasZipped[0]) {
            System.out.print(" compressed");
        }
        System.out.println(" record at position " + pos + ": \n" + car);
    }

    private static void printRecord(RandomAccessFile raf, String key,
                                    IndexBase pidx) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get(key);
        for (long pos : poss) {
            System.out.print("*** Key: " + key + " points to");
            printRecord(raf, pos);
        }
    }

    static void printFile()
            throws IOException, ClassNotFoundException {
        long pos;
        int rec = 0;
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            while ((pos = raf.getFilePointer()) < raf.length()) {
                System.out.print("#" + (++rec));
                printRecord(raf, pos);
            }
            System.out.flush();
        }
    }

    private static IndexBase indexByArg(String arg, Index idx) {
        IndexBase pidx = null;
        switch (arg) {
            case "n":
                pidx = idx.number;
                break;
            case "o":
                pidx = idx.owner;
                break;
            case "d":
                pidx = idx.duration;
                break;
            default:
                System.err.println("Invalid index specified: " + arg);
                break;
        }
        return pidx;
    }

    static boolean printFile(String[] args, boolean reversed)
            throws ClassNotFoundException, IOException {
        if (args.length != 2) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            Comparator <String> comp = args[1].equals("d") ? (reversed ? new DateCompReverse() : new DateComp()) :
                    (reversed ? new StringCompReverse() : new StringComp());

            String[] keys =
                    pidx.getKeys(comp);
            for (String key : keys) {
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }

    static boolean findByKey(String[] args)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (!pidx.contains(args[2])) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            printRecord(raf, args[2], pidx);
        }
        return true;
    }

    static boolean findByKey(String[] args, boolean reversed)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            System.err.println("Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (!pidx.contains(args[2])) {
                System.err.println("Key not found: " + args[2]);
                return false;
            }
            Comparator <String> comp = args[1].equals("d") ? (reversed ? new DateCompReverse() : new DateComp()) :
                    (reversed ? new StringComp() : new StringCompReverse());
            String[] keys = pidx.getKeys(comp);
            for (String key : keys) {
                if (key.equals(args[2])) {
                    break;
                }
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }
}