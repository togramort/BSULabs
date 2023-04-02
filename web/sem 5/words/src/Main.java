import java.util.Scanner;

/**
 * Main class to create manager instance and choose localization
 */
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Localization loc;
        while (true){
            System.out.println("Choose the localization:\n1) English\n2) Russian");
            int choice = scanner.nextInt();
            switch (choice) {
                case 1 -> {
                    loc = Localization.English;
                    break;
                }
                case 2 -> {
                    loc = Localization.Russian;
                    break;
                }
                default -> {
                    System.out.println("Wrong choice. Try again!");
                    continue;
                }
            }
            break;
        }
        Manager manager;
        try{
            manager = new Manager(loc);
        }catch (RuntimeException ex){
            return;
        }
        manager.showMenu();
    }
}