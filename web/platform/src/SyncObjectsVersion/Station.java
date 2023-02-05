package SyncObjectsVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Special buffer zone for passengers and trains, contain two platforms
 */
public class Station {

    private String name;
    private static final Logger logger = LogManager.getLogger(SyncObjectsVersion.Station.class.getPackageName());
    private static final Random random = new Random();
    private List<SyncObjectsVersion.Passenger> passengers;

    public SyncObjectsVersion.Train forwardPlatformTrain;
    public SyncObjectsVersion.Train backwardPlatformTrain;
    public ReentrantLock forwardPlatform, backwardPlatform, passengersAccess;

    public Station(String name) {
        this.passengers = Collections.synchronizedList(new ArrayList<>());
        this.name = name;
        forwardPlatform = new ReentrantLock();
        backwardPlatform = new ReentrantLock();
        passengersAccess = new ReentrantLock();
    }

    /**
     * Sets train to the forward platform
     * @param train target train
     */
    public void setForwardPlatformTrain(Train train){
        if (this.forwardPlatformTrain == null){
            logger.info(String.format("Train %s arrived at the forward platform of %s station", train.getName(), this.name));
            this.forwardPlatformTrain = train;
        }else{
            logger.info(String.format("Train %s left the forward platform of %s station", this.forwardPlatformTrain.getName(), this.name));
            this.forwardPlatformTrain = null;
        }
    }

    /**
     * Sets train to the backward platform
     * @param train target train
     */
    public void setBackwardPlatformTrain(Train train){
        if (this.backwardPlatformTrain == null){
            logger.info(String.format("Train %s arrived at the backward platform of %s station", train.getName(), this.name));
            this.backwardPlatformTrain = train;
        }else{
            logger.info(String.format("Train %s left the backward platform of %s station", this.backwardPlatformTrain.getName(), this.name));
            this.backwardPlatformTrain = null;
        }
    }

    /**
     * Add passenger to the station
     * @param passenger passenger
     */
    public void addPassenger(Passenger passenger){
        passengersAccess.lock();
        passengers.add(passenger);
        passengersAccess.unlock();
    }

    /**
     * Remove passenger from the station
     * @param passenger passenger
     */
    public void deletePassenger(Passenger passenger){
        passengersAccess.lock();
        passengers.remove(passenger);
        passengersAccess.unlock();
    }

    /**
     * Gets one of the station trains
     * @return train
     */
    public Train getSpareTrain(){
        if (forwardPlatformTrain != null){
            if (backwardPlatformTrain != null){
                return random.nextInt(2) == 1 ? forwardPlatformTrain : backwardPlatformTrain;
            }
            return forwardPlatformTrain;
        }else if (backwardPlatformTrain != null){
            return backwardPlatformTrain;
        }else{
            return null;
        }
    }

    /**
     * Gets station name
     * @return station name
     */
    public String getName(){
        return name;
    }
}
