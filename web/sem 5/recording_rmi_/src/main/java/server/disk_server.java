package server;

import cmp.cmpComposer;
import cmp.cmpDuration;
import cmp.cmpName;
import compositions.*;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.lang.reflect.InvocationTargetException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Consumer;

public class disk_server extends UnicastRemoteObject implements disk_remote.DiskServerInterface {
    private final ConcurrentHashMap<String, disk> disks = new ConcurrentHashMap<>();
    final Logger logger = LogManager.getLogger();

    public static void main(String[] args) {
        try {
            new disk_server();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Constructor without parameters
     * @throws RemoteException
     * @throws MalformedURLException
     */
    public disk_server() throws RemoteException, MalformedURLException {
        int PORT = 8080;
        LocateRegistry.createRegistry(PORT);
        System.setProperty("java.rmi.server.hostname", "localhost");
        String SERVER_NAME = "DiskServer";
        Naming.rebind("rmi://" + disk_remote.address + ":" + PORT + "/" + SERVER_NAME, this);
        logger.info("[start] Server is working!");
    }

    /**
     * @param diskName name of disk to calculate duration
     * @return duration of the disk
     * @throws RemoteException
     */
    @Override
    public int getDuration(String diskName) throws RemoteException {
        logger.info("Getting duration for disk" + diskName);
        return disk_util.getDuration(disks.get(diskName));
    }

    /**
     * @param diskName name of the disk
     * @param name name of composition
     * @param duration duration of the composition
     * @param composer composer of the composition
     * @return composition that is found
     * @throws RemoteException
     */
    @Override
    public records search(String diskName, String name, Integer duration, String composer)
            throws RemoteException {
        logger.info("Searching composition");
        return disk_util.search(disks.get(diskName), name, duration, composer);
    }

    /**
     * @param diskName name of disk to create
     * @return true if disk was successfully created, else false
     */
    @Override
    public boolean createDisk(String diskName) {
        try {
            logger.info("Creating disk");
            disks.put(diskName, new disk());
        }
        catch (Exception e){
            logger.warn("Something wrong while creating disk");
            return false;
        }
        return true;
    }

    /**
     * @param diskName name of disk
     * @param compositions type of composition
     * @param name name of composition
     * @param duration duration of composition
     * @param composer composer of the composition
     * @param performer performer of the composition
     * @param tonality tonality of the composition
     * @param textWriter text writer of the composition
     * @param genre genre of the composition
     * @param instrument instrument of the composition
     */
    @Override
    public void recordComposition(String diskName, records_list compositions, String name, int duration,
                                  String composer, String performer, String tonality, String textWriter,
                                  String genre, String instrument) throws InvocationTargetException, NoSuchMethodException, IllegalAccessException {
        logger.info("Recording composition");
        disks.get(diskName).recordComposition(compositions, name, duration, composer, performer, tonality,
                textWriter, genre, instrument);
    }

    @Override
    public void sortComposer(String diskName) throws RemoteException {
        logger.info("Sorting compositions");
        disks.get(diskName).sortComp();
    }

    @Override
    public void sortDuration(String diskName) throws RemoteException {
        logger.info("Sorting compositions");
        disks.get(diskName).sortDur();
    }

    @Override
    public void sortName(String diskName) throws RemoteException {
        logger.info("Sorting compositions");
        disks.get(diskName).sortName();
    }
}

