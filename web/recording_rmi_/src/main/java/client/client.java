package client;

import compositions.*;
import server.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationTargetException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Locale;
import java.util.Objects;
import java.util.Scanner;
import java.util.function.Consumer;

public class client {
    BufferedReader inReader;
    final disk_remote.DiskServerInterface server;

    public static void main(String[] args) {
        try {
            new client(System.in);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * @param in input stream
     * @throws IOException
     * @throws NotBoundException
     */
    public client(InputStream in) throws IOException, NotBoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException {
        inReader = new BufferedReader(new InputStreamReader(in));
        String hostname = "localhost";
        String serverName = "DiskServer";
        int PORT = 8080;
        server = (disk_remote.DiskServerInterface) Naming.lookup("rmi://" + hostname
                + ":" + PORT + "/" + serverName);
        userInterface();
    }

    /**
     * user interface
     */
    public void userInterface() throws InvocationTargetException, NoSuchMethodException, IllegalAccessException {
        var scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            clearConsole();
            System.out.println("Music Manager");
            System.out.println("""
                    Available operations:
                    1. create disk. Usage: 1 <name>
                    2. get duration. Usage: 2 <diskName>
                    3. search. Usage: 3 <diskName> <name> <duration> <composer>
                    Note: you can omit some parameters: just type "null" instead of it!
                    4. record composition. Usage: <diskName> <compositions> <name> <duration> <composer> <performer> 
                    <tonality> <textWriter> <genre> <instrument>
                    5. sort. Usage: 5 <diskName> <field>
                    Note: field must be name, duration or composer
                    """
            );
            var cmd = scanner.nextLine();
            var args = cmd.split(" ");
            System.out.println("Command recognized: " + args[0]);
            String resp;
            try {
                switch (args[0].toLowerCase(Locale.ROOT)) {
                    case "1" -> resp = createDisk(args);
                    case "2" -> resp = getDuration(args);
                    case "3" -> resp = search(args);
                    case "4" -> resp = recordComposition(args);
                    case "5" -> resp = sort(args);
                    default -> resp = "Wrong Command";
                }
                System.out.println(resp);
            }
            catch (input_parameters_exception ex){
                System.out.println(ex.getMessage());
            }catch(RemoteException e){
                e.printStackTrace();
            }
        }
    }

    /**
     * @param args arguments
     * @return string
     * @throws input_parameters_exception
     * @throws RemoteException
     */
    private String sort(String[] args) throws input_parameters_exception, RemoteException {
        if (args.length < 3) {
            throw new input_parameters_exception("In this command you need to type two parameters!");
        }
        if(Objects.equals(args[2], "name")) {
            server.sortName(args[1]);
        }
        if(Objects.equals(args[2], "composer")) {
            server.sortComposer(args[1]);
        }
        if(Objects.equals(args[2], "duration")) {
            server.sortDuration(args[1]);
        }
        return "Successfully sorted";
    }

    /**
     * @param args arguments
     * @return string
     * @throws input_parameters_exception
     * @throws RemoteException
     */
    private String recordComposition(String[] args) throws input_parameters_exception, RemoteException, InvocationTargetException, NoSuchMethodException, IllegalAccessException {
        if (args.length < 11) {
            throw new input_parameters_exception("In this command you need to type ten parameters!");
        }
        try {
            server.recordComposition(args[1], records_list.valueOf(args[2]), args[3], Integer.parseInt(args[4]), args[5],
                    args[6], args[7], args[8], args[9], args[10]);
        } catch (NumberFormatException e){
            return "The fifth parameter must be a number";
        } catch (IllegalArgumentException ex){
            return "The third parameter must be one of next values: " +
                    "Concert, " +
                    "Opera, " +
                    "Romance, " +
                    "Sonata, " +
                    "Song, " +
                    "Symphony";
        }
        return "Successfully recorded";
    }

    /**
     * @param args arguments
     * @return string
     * @throws input_parameters_exception
     * @throws RemoteException
     */
    private String search(String[] args) throws input_parameters_exception, RemoteException {
        if (args.length < 5) {
            throw new input_parameters_exception("In this command you need to type one parameter!");
        }
        records comp;
        try {
            comp = server.search(args[1], args[2], Integer.parseInt(args[3]), args[4]);
        }catch(NumberFormatException ex){
            return "The fourth parameter must be a number";
        }
        return "Composition: " + comp;
    }

    /**
     * @param args arguments
     * @return string
     * @throws input_parameters_exception
     * @throws RemoteException
     */
    private String getDuration(String[] args) throws input_parameters_exception, RemoteException {
        if (args.length < 2) {
            throw new input_parameters_exception("In this command you need to type one parameter!");
        }
        int dur = server.getDuration(args[1]);
        return "Duration = " + dur;
    }

    /**
     * @param args arguments
     * @return string
     * @throws input_parameters_exception
     * @throws RemoteException
     */
    private String createDisk(String[] args) throws input_parameters_exception, RemoteException {
        if (args.length < 2) {
            throw new input_parameters_exception("In this command you need to type one parameter!");
        }
        server.createDisk(args[1]);
        return "Successfully created";
    }

    /**
     * Clears the client`s console
     */
    private static void clearConsole() {
        try {
            if (System.getProperty("os.name").contains("Windows"))
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            else
                Runtime.getRuntime().exec("clear");
        } catch (IOException | InterruptedException ignored) {
        }
    }
}
