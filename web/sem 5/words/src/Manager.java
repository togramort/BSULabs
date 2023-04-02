import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;
import java.util.Properties;
import java.util.Scanner;

public class Manager {
    private Properties properties;
    private Scanner scanner;
    private Text text;
    private boolean isParsed = false;

    public Manager(Localization localization) {

        properties = new Properties();
        switch (localization){
            case English -> {
                try {
                    properties.load(new FileInputStream("english.properties"));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                break;
            }
            case Russian -> {
                try {
                    properties.load(new FileReader("russian.properties"));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                break;
            }
            default -> {
                throw new RuntimeException("Manager constructor do not work with such localization");
            }
        }
        scanner = new Scanner(System.in);
    }

    public void showMenu(){
        while (true){
            System.out.println(properties.getProperty("menu"));
            int choice = scanner.nextInt();
            switch (choice){
                case 1 -> {
                    parseFile();
                    break;
                }
                case 2 -> {
                    printParsedFile();
                    break;
                }
                case 3 -> {
                    deleteFirstLetterRepetitions();
                    break;
                }
                case 4 -> {
                    return;
                }
                default -> System.out.println(properties.getProperty("tryAgain"));
            }
        }
    }

    private void parseFile(){
        System.out.println(properties.getProperty("getFilename"));
        String filename = scanner.next();
        String text_str = "";
        try{
            text_str = readFile(filename);
        } catch (NoSuchFileException ex){
            System.err.println(properties.getProperty("fileNotFound"));
            return;
        }catch (IOException ex){
            System.err.println(properties.getProperty("fileError"));
            return;
        }
        text = new Text(text_str);
        isParsed = true;
        System.out.println(properties.getProperty("success"));
    }

    private String readFile(String fileName) throws NoSuchFileException, IOException {
        return new String(Files.readAllBytes(Paths.get(fileName)));
    }

    private void printParsedFile(){
        if (isParsed){
            System.out.println(text);
        }else{
            System.out.println(properties.getProperty("notParsed"));
        }
    }

    private void deleteFirstLetterRepetitions(){
        if (isParsed){
            text.deleteFirstLetterRepetition();
            System.out.println(properties.getProperty("success"));
        }else{
            System.out.println(properties.getProperty("notParsed"));
        }
    }
}
