package server;

import compositions.*;

import java.lang.reflect.InvocationTargetException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.function.Consumer;

public interface disk_remote {
    String address = "localhost";

    interface DiskServerInterface extends Remote {
        int getDuration(String diskName) throws RemoteException;

        records search(String diskName, String name, Integer duration, String composer) throws RemoteException;

        boolean createDisk(String diskName) throws RemoteException;

        void recordComposition(String diskName, records_list compositions, String name, int duration, String composer,
                               String performer, String tonality, String textWriter, String genre, String instrument)
                throws RemoteException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

        void sortComposer(String diskName) throws RemoteException;
        void sortDuration(String diskName) throws RemoteException;
        void sortName(String diskName) throws RemoteException;
    }
}
