package WaitNotifyVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Random;


/**
 * Special buffer zone for passengers and trains, contain two platforms
 */
public class Station{
    private String name;
    private static final Logger logger = LogManager.getLogger(Station.class.getPackageName());
    private static final Random random = new Random();
    private List<Passenger> passengers;

    public Train forwardPlatformTrain;
    public Train backwardPlatformTrain;
    public final Object forwardPlatform, backwardPlatform;

    public Station(String name) {
        this.passengers = Collections.synchronizedList(new ArrayList<>());
        this.name = name;
        forwardPlatform = new Object();
        backwardPlatform = new Object();
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
     * @param passenger passengers
     */
    public void addPassenger(Passenger passenger){
        synchronized (passengers){
            passengers.add(passenger);
        }
    }

    /**
     * Remove passenger from the station
     * @param passenger passengers
     */
    public void deletePassenger(Passenger passenger){
        synchronized (passengers){
            passengers.remove(passenger);
        }
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
}
