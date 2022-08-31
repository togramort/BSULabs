import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.text.ParseException;
import java.util.*;

import static java.lang.System.exit;
import static javax.swing.JOptionPane.showMessageDialog;


public class Main {
    private static JCheckBox zip;
    private static JFrame choiceFrame;
    private static JTextArea keyArea;
    private static JFrame deleteFrame;
    private static JFrame saveFrame;
    private static JFrame frame;

    static class appendItemBtnListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String[] args = new String[7];

            args[0] = numberArea.getText();
            args[1] = ownerArea.getText();
            args[2] = dateStartArea.getText();
            args[3] = dateEndArea.getText();
            args[4] = priceArea.getText();
            for (int i = 0; i < 5; i++)
                if (args[i].equals("")) {
                    showMessageDialog(inputFrame, "Все поля должны быть заполнены!");
                    return;
                }
            try {
                appendFile(args, zip.isSelected());
            } catch (IOException | ClassNotFoundException | KeyNotUniqueException | CustomException ioException) {
                ioException.printStackTrace();
            }
            inputFrame.setVisible(false);
        }
    }

    // The main program
    static ArrayList<Car> array;

    private static final JTextArea textArea = new JTextArea();
    public static FontChooser fChooser;
    private static JFrame inputFrame;
    private static JTextArea numberArea;
    private static JTextArea ownerArea;
    private static JTextArea dateStartArea;
    private static JTextArea dateEndArea;
    private static JTextArea priceArea;

    public static void main(String[] args) {

        frame = new JFrame("Lab 8");

        // Handle window close requests by exiting the VM
        frame.addWindowListener(new WindowAdapter() { // Anonymous inner class
            public void windowClosing(WindowEvent e) {
                exit(0);
            }
        });

        textArea.setEditable(false);

        JMenuBar menubar = new JMenuBar();

        JMenu menu;
        JMenuItem item;
        // File/Quite
        menu = new JMenu("File");
        menubar.add(menu);

        JMenuItem open = new JMenuItem("Open");
        JFileChooser fileChooser = new JFileChooser();
        open.addActionListener(actionEvent -> {
            fileChooser.setCurrentDirectory(new File(System.getProperty("user.dir")));
            int result = fileChooser.showOpenDialog(frame);
            if (result == JFileChooser.APPROVE_OPTION) {
                textArea.setText(null);
                String[] strs = fileChooser.getSelectedFile().getName().split("\\.");
                if (!strs[strs.length - 1].equals("dat")) {
                    textArea.append("Choose file with extension .dat");
                } else
                    filename = fileChooser.getSelectedFile().getName();
            }
        });
        menu.add(open);

        JMenuItem save = new JMenuItem("Save data in file...");
        save.addActionListener(e -> createSaveFile());
        menu.add(save);

        JMenuItem exit = new JMenuItem("Quit");
        exit.addActionListener(actionEvent -> {
            Object[] options = {"Yes!", "No!"};
            int n = JOptionPane.showOptionDialog(frame,
                    "Exit application?",
                    "Exit",
                    JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null,
                    options,
                    options[0]);
            if (n == JOptionPane.OK_OPTION) {
                deleteFile();
                frame.setVisible(false);
                System.exit(0);
            }
        });
        menu.add(exit);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        //////////////////View
        menu = new JMenu("View");

        /////////////View/Font
        item = new JMenuItem("Font");
        fChooser = new FontChooser(frame);
        item.addActionListener(e -> {

            fChooser.setVisible(true);
            textArea.setFont(fChooser.selectedFont);

        });
        menu.add(item);
        menubar.add(menu);


        //////////////////View/Look and Feel


        JMenu plafmenu = new JMenu("Look and Feel");
        ButtonGroup radiogroup = new ButtonGroup();
        UIManager.LookAndFeelInfo[] plafs =
                UIManager.getInstalledLookAndFeels();
        for (UIManager.LookAndFeelInfo plaf : plafs) {
            String plafName = plaf.getName();
            final String plafClassName = plaf.getClassName();

            item = plafmenu.add(new JRadioButtonMenuItem(plafName));

            item.addActionListener(e -> {
                try {
                    // Set the new look and feel
                    UIManager.setLookAndFeel(plafClassName);
                    // Tell each component to change its look-and-feel
                    SwingUtilities.updateComponentTreeUI(frame);
                    // Tell the frame to resize itself to the its
                    // children's new desired sizes
                    frame.pack();
                } catch (Exception ex) {
                    showMessageDialog(frame, ex);
                }
            });

            // Only allow one menu item to be selected at once
            radiogroup.add(item);
        }
        menu.add(plafmenu);


        ///////////////////Help
        menu = new JMenu("Help");
        menubar.add(menu);
        ///////////////////Help/About
        item = new JMenuItem("About");

        item.addActionListener(actionEvent -> {
            JDialog dialog = new JDialog(frame, "Info", true);
            JPanel panel = new JPanel();
            JTextArea text = new JTextArea("Student: Margot Golubovich\nGroup: 13\nCourse: 2\n" +
                    "Faculty: FAMCS\nUniversity: BSU\nTask: 8. запись в журнале стоянки автомобиля имеет атрибуты: номер авто, ФИО владельца, дата и время начала, дата и время окончания, тариф за час. индексировать по: номер авто, ФИО владельца, время стоянки");
            text.setSize(500, 200);
            panel.setSize(500, 200);

            dialog.setMinimumSize(new Dimension(600, 200));
            text.setLineWrap(true);
            panel.add(text);
            text.setEditable(false);

            JButton button = new JButton("OK");
            button.addActionListener(actionEvent1 -> dialog.dispose());
            button.setSize(50, 50);
            button.isVisible();
            panel.add(button);

            dialog.add(panel);
            dialog.setResizable(false);
            dialog.setLocation(300, 300);

            dialog.setVisible(true);
            dialog.pack();
            dialog.addWindowListener(new WindowAdapter() { // Anonymous inner class
                public void windowClosing(WindowEvent e) {
                    dialog.dispose();
                }
            });
        });
        menu.add(item);


///////////////////////////////////////////////////////////////////////////
        //Add
        JMenu commands = new JMenu("Commands");
        menubar.add(commands);

        JMenu addMenu = new JMenu("Append");

        JMenuItem addNew = new JMenuItem("Append data");
        addNew.addActionListener(e -> createInputFrame());

        commands.add(addMenu);
        addMenu.add(addNew);
        //addMenu.add(addNewCompressed);*/


        //////////////////////////////////////////////////////////////////////////////////
        JMenu printMenu = new JMenu("Print");
        //////////////////////////////////////////////////////////////////////////////////
        JMenu printAllRecords = new JMenu("Print all data");
        JMenu printAllRecordsReverse = new JMenu("Print all data reversed");
        /////////////////////////////////////////////////////////////////////////////////
        JMenuItem printUnsorted = new JMenuItem("Print all data unsorted");
        printUnsorted.addActionListener(e -> {
            try {
                printFile();
            } catch (IOException | ClassNotFoundException ioException) {
                ioException.printStackTrace();
            }
        });
        JMenuItem printSortedByNumber = new JMenuItem("Print all data sorted by car's number");
        printSortedByNumber.addActionListener(e -> {
            try {
                printFile("n", false);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });
        JMenuItem printSortedByNumberR = new JMenuItem("Print all data sorted by car's number");
        printSortedByNumberR.addActionListener(e -> {
            try {
                printFile("n", true);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });
        JMenuItem printSortedByOwner = new JMenuItem("Print all data sorted by owner's name");
        printSortedByOwner.addActionListener(e -> {
            try {
                printFile("o", false);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });
        JMenuItem printSortedByOwnerR = new JMenuItem("Print all data sorted by owner's name");
        printSortedByOwnerR.addActionListener(e -> {
            try {
                printFile("o", true);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });
        JMenuItem printSortedByDuration = new JMenuItem("Print all data sorted by duration");
        printSortedByDuration.addActionListener(e -> {
            try {
                printFile("d", false);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });
        JMenuItem printSortedByDurationR = new JMenuItem("Print all data sorted by duration");
        printSortedByDurationR.addActionListener(e -> {
            try {
                printFile("d", true);
            } catch (ClassNotFoundException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });

        commands.add(printMenu);
        printMenu.add(printAllRecords);
        printMenu.add(printAllRecordsReverse);
        printAllRecords.add(printUnsorted);
        printAllRecords.add(printSortedByNumber);
        printAllRecords.add(printSortedByOwner);
        printAllRecords.add(printSortedByDuration);
        printAllRecordsReverse.add(printSortedByNumberR);
        printAllRecordsReverse.add(printSortedByOwnerR);
        printAllRecordsReverse.add(printSortedByDurationR);

//delete and find by key
        JMenu find = new JMenu("Find");
        JMenuItem findBy = new JMenuItem("Find by key...");
        findBy.addActionListener(e -> createFindFrame());
        commands.add(find);
        find.add(findBy);

        JMenu delete = new JMenu("Delete");
        JMenuItem deleteAll = new JMenuItem("Delete all data");
        deleteAll.addActionListener(e -> deleteFile());
        JMenuItem deleteKey = new JMenuItem("Delete by key");
        deleteKey.addActionListener(e -> createDeleteFrame());
        commands.add(delete);
        delete.add(deleteAll);
        delete.add(deleteKey);

        frame.setJMenuBar(menubar);
        frame.pack();              //Make frame as big as its kids need
        frame.setVisible(true);    //Make the frame visible on the screen
        frame.setLocation(650, 300);
        frame.setMinimumSize(new Dimension(500, 500));
        JScrollPane scroller = new JScrollPane(textArea);

        frame.getContentPane().add(BorderLayout.CENTER, scroller);
        //plafmenu.setFont(fChooser.selectedFont);
        //menu.setFont(fChooser.selectedFont);
        //menubar.setFont(fChooser.selectedFont);
        //plafmenu.setFont(fChooser.selectedFont);
        ///////////////body
        // JEditorPane htmlP=new JEditorPane(html);

    }

    static void createDeleteFrame() {
        deleteFrame = new JFrame("Choose key");
        deleteFrame.setVisible(true);
        deleteFrame.setSize(400, 450);
        JPanel inputPanel = new JPanel(new GridLayout(0, 1));

        JLabel keyPanel = new JLabel("Enter key");
        keyArea = new JTextArea();
        keyArea.setColumns(15);

        final String[] criterionStr = {""};

        JLabel criterion = new JLabel("Choose criterion");
        ButtonGroup group3 = new ButtonGroup();
        JRadioButton deleteNumber = new JRadioButton("Delete by number");
        deleteNumber.addActionListener(e -> criterionStr[0] = "n");
        JRadioButton deleteOwner = new JRadioButton("Delete by owner");
        deleteOwner.addActionListener(e -> criterionStr[0] = "o");
        JRadioButton deleteDuration = new JRadioButton("Delete by duration");
        deleteDuration.addActionListener(e -> criterionStr[0] = "d");
        group3.add(deleteNumber);
        group3.add(deleteOwner);
        group3.add(deleteDuration);

        JButton enter = new JButton("Enter");
        enter.addActionListener(e -> {
            //String str=criterionStr[0]+keyArea.getText();
            String[] args = new String[]{"-dk", criterionStr[0], keyArea.getText()};
            if (args[1].equals("") || args[2].equals("")) {
                showMessageDialog(choiceFrame, "Все поля должны быть заполнены!");
                return;
            }
            try {
                deleteFile(args);
            } catch (ClassNotFoundException | KeyNotUniqueException | IOException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
            deleteFrame.setVisible(false);
        });

        deleteFrame.add(inputPanel);
        inputPanel.add(keyPanel);
        inputPanel.add(keyArea);
        inputPanel.add(criterion);
        inputPanel.add(deleteNumber);
        inputPanel.add(deleteOwner);
        inputPanel.add(deleteDuration);
        inputPanel.add(enter);
    }

    static void createFindFrame() {
        choiceFrame = new JFrame("Choose key");
        choiceFrame.setVisible(true);
        choiceFrame.setSize(290, 250);
        JPanel inputPanel = new JPanel();

        JLabel keyPanel = new JLabel("Enter key");
        keyArea = new JTextArea();
        keyArea.setColumns(15);

        final String[] criterionStr = {""};

        JLabel criterion = new JLabel("Choose criterion");
        ButtonGroup group1 = new ButtonGroup();
        JRadioButton findNumber = new JRadioButton("Find by number");
        findNumber.addActionListener(e -> criterionStr[0] = "n");
        JRadioButton findOwner = new JRadioButton("Find by owner");
        findOwner.addActionListener(e -> criterionStr[0] = "o");
        JRadioButton findDuration = new JRadioButton("Find by duration");
        findDuration.addActionListener(e -> criterionStr[0] = "d");
        group1.add(findNumber);
        group1.add(findOwner);
        group1.add(findDuration);

        final String[] comparisonStr = {""};
        JLabel comparison = new JLabel("Choose comparison");
        ButtonGroup group2 = new ButtonGroup();
        JRadioButton equal = new JRadioButton("Find equal...");
        equal.addActionListener(e -> comparisonStr[0] = "-f");
        JRadioButton before = new JRadioButton("Find before...");
        before.addActionListener(e -> comparisonStr[0] = "-fl");
        JRadioButton after = new JRadioButton("Find after...");
        after.addActionListener(e -> comparisonStr[0] = "-fr");
        group2.add(equal);
        group2.add(before);
        group2.add(after);

        //final String[] str = {""};
        JButton enter = new JButton("Enter");
        enter.addActionListener(e -> {
            //String str=criterionStr[0]+keyArea.getText();
            String[] args = new String[]{comparisonStr[0], criterionStr[0], keyArea.getText()};
            textArea.setText(null);
            if (args[0].equals("") || args[1].equals("") || args[2].equals("")) {
                showMessageDialog(choiceFrame, "Все поля должны быть заполнены!");
                return;
            }
            if (equal.isSelected()) {
                try {
                    if (!findByKey(args)) {
                        //textArea.setText("");
                        textArea.setText("Key not found");
                    }
                } catch (ClassNotFoundException | IOException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }

            } else if (before.isSelected()) {
                try {
                    if (!findByKey(args, false)) {
                        textArea.setText("Key not found");
                    }
                } catch (ClassNotFoundException | IOException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
            } else {
                try {
                    if (!findByKey(args, true)) {
                        textArea.setText("Key not found");
                    }
                } catch (ClassNotFoundException | IOException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
            }
            choiceFrame.setVisible(false);
        });

        choiceFrame.add(inputPanel);

        inputPanel.add(keyPanel);
        inputPanel.add(keyArea);

        inputPanel.add(criterion);
        inputPanel.add(findNumber);
        inputPanel.add(findOwner);
        inputPanel.add(findDuration);

        inputPanel.add(comparison);
        inputPanel.add(equal);
        inputPanel.add(before);
        inputPanel.add(after);

        inputPanel.add(enter);
    }

    static void createSaveFile() {
        saveFrame = new JFrame("Save data");
        saveFrame.setVisible(true);
        saveFrame.setSize(200, 300);
        JPanel inputPanel = new JPanel(new GridLayout(0, 1));

        JLabel saveLabel = new JLabel("Enter file name");
        JTextArea saveArea = new JTextArea();

        JButton enter = new JButton("Enter");
        enter.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                /*try (FileWriter fw = new FileWriter(saveArea.getText() + ".dat")) {
                    saveData(fw);
                } catch (IOException ex) {
                    showMessageDialog(frame,);("Don't create save file!");
                }*/
                new File(filename).renameTo(new File(saveArea.getText() + ".dat"));
                filename = saveArea.getText() + ".dat";
                saveFrame.setVisible(false);
            }
        });

        saveFrame.add(inputPanel);
        inputPanel.add(saveLabel);
        inputPanel.add(saveArea);
        inputPanel.add(enter);
    }

    static void createInputFrame() {
        inputFrame = new JFrame("Enter data");
        inputFrame.setVisible(true);
        inputFrame.setSize(80, 450);
        JPanel inputPanel = new JPanel();

        JLabel numberLabel = new JLabel("Number: ");
        numberArea = new JTextArea();
        numberArea.setColumns(15);

        JLabel ownerLabel = new JLabel("Person full name: ");
        ownerArea = new JTextArea();
        ownerArea.setColumns(15);

        JLabel dateStartLabel = new JLabel("Beginning: ");
        dateStartArea = new JTextArea();
        dateStartArea.setColumns(15);

        JLabel dateEndLabel = new JLabel("Ending: ");
        dateEndArea = new JTextArea();
        dateEndArea.setColumns(15);

   /*     JLabel durationLabel = new JLabel("Duration: ");
        durationArea = new JTextArea();
        durationArea.setColumns(15);*/

        JLabel priceLabel = new JLabel("Price: ");
        priceArea = new JTextArea();
        priceArea.setColumns(15);

        final boolean[] needZip = {false};
        zip = new JCheckBox("Needed to zip");
        zip.addActionListener(e -> needZip[0] = !needZip[0]);

        JButton appendItemBtn = new JButton("Add data");
        appendItemBtn.addActionListener(new appendItemBtnListener());

        inputPanel.add(numberLabel);
        inputPanel.add(numberArea);

        inputPanel.add(ownerLabel);
        inputPanel.add(ownerArea);

        inputPanel.add(dateStartLabel);
        inputPanel.add(dateStartArea);

        inputPanel.add(dateEndLabel);
        inputPanel.add(dateEndArea);

        inputPanel.add(priceLabel);
        inputPanel.add(priceArea);

        inputPanel.add(zip);

        inputPanel.add(appendItemBtn);

        inputFrame.getContentPane().add(BorderLayout.CENTER, inputPanel);

    }


    static String filename = "Car.dat";
    static final String filenameBak = "Car.~dat";
    static final String idxname = "Car.idx";
    static final String idxnameBak = "Car.~idx";

    // input file encoding:
    private static final String encoding = "Cp866";
    private static final PrintStream carOut = System.out;

    static Car readCar(String[] args) throws CustomException {
        return Car.read(args);
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

    static boolean deleteFile(String[] args)
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
        //-dk  {n|o|d} key      - clear data by key
        if (args.length != 3) {
            showMessageDialog(frame, "Invalid number of arguments");
            return false;
        }
        long[] poss;
        try (Index idx = Index.load(idxname)) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (pidx == null) {
                return false;
            }
            if (!pidx.contains(args[2])) {
                showMessageDialog(frame, "Key not found: " + args[2]);
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
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return true;
    }

    static void appendFile(String[] args, Boolean zipped)
            throws IOException, ClassNotFoundException,
            KeyNotUniqueException, CustomException {
        //Scanner fin = new Scanner(System.in, encoding);
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            Car car = readCar(args);
            idx.test(car);
            long pos = Buffer.writeObject(raf, car, zipped);
            idx.put(car, pos);
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    private static void printRecord(RandomAccessFile raf, long pos)
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[]{false};
        Car car = (Car) Buffer.readObject(raf, pos, wasZipped);
        if (wasZipped[0]) {
            textArea.append(" compressed");
        }
        textArea.append(" record at position " + pos + ": \n" + car + "\n");
    }

    private static void printRecord(RandomAccessFile raf, String key,
                                    IndexBase pidx) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get(key);
        for (long pos : poss) {
            textArea.append("*** Key: " + key + " points to");
            printRecord(raf, pos);
        }
    }

    static void printFile()
            throws IOException, ClassNotFoundException {
        textArea.setText(null);
        long pos;
        int rec = 0;
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            while ((pos = raf.getFilePointer()) < raf.length()) {
                textArea.append("#" + (++rec));
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
                showMessageDialog(frame, "Invalid index specified: " + arg);
        }
        return pidx;
    }

    static boolean printFile(String arg, boolean reverse)
            throws ClassNotFoundException, IOException {
        textArea.setText(null);
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(arg, idx);
            if (pidx == null) {
                return false;
            }
            Comparator <String> comp = arg.equals("d") ? (reverse ? new DateCompReverse() : new DateComp()) :
                    (reverse ? new StringCompReverse() : new StringComp());
            String[] keys = pidx.getKeys(comp);

            for (String key : keys) {
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }

    static boolean findByKey(String[] args)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            showMessageDialog(frame, "Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (!pidx.contains(args[2])) {
                showMessageDialog(frame, "Key not found: " + args[2]);
                return false;
            }
            printRecord(raf, args[2], pidx);
        }
        return true;
    }

    static boolean findByKey(String[] args, boolean reverse)
            throws ClassNotFoundException, IOException {
        if (args.length != 3) {
            showMessageDialog(frame, "Invalid number of arguments");
            return false;
        }
        try (Index idx = Index.load(idxname);
             RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            IndexBase pidx = indexByArg(args[1], idx);
            if (!pidx.contains(args[2])) {
                showMessageDialog(frame, "Key not found: " + args[2]);
                return false;
            }
            Comparator <String> comp = args[1].equals("d") ? (reverse ? new DateCompReverse() : new DateComp()) :
                    (reverse ? new StringCompReverse() : new StringComp());
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