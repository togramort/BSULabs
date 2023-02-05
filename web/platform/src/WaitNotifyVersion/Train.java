package WaitNotifyVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Runnable class for Train
 */
public class Train implements Runnable{
    private static Logger logger = LogManager.getLogger(Train.class.getPackageName());
    private int stopTime_;
    private String name;
    private int timeBetweenStations_;
    private Route route;
    private RouteIterator iterator;
    private boolean isOnStation = false;
    private int maxPassengers;
    private boolean finishThread = false;
    private List<Passenger> passengers;

    public Train(int stopTime, int timeBetweenStations, Route route, String name) {
        this.stopTime_ = stopTime;
        this.timeBetweenStations_ = timeBetweenStations;
        this.route = route;
        this.name = name;
        this.iterator = new RouteIterator(route);
        this.passengers = Collections.synchronizedList(new ArrayList<>());
    }

    /**
     * Move train to the next station in the route
     * @throws InterruptedException
     */
    public void goToNextStation() throws InterruptedException {
        Thread.sleep(timeBetweenStations_);
        Station target = this.iterator.next();
        if (this.route.getDirection() == RouteDirection.Forward){
            synchronized (target.forwardPlatform){
                target.setForwardPlatformTrain(this);
                this.isOnStation = true;
                Thread.sleep(stopTime_);
                this.isOnStation = false;
                target.setForwardPlatformTrain(null);
            }
        }else{
            synchronized (target.backwardPlatform){
                target.setBackwardPlatformTrain(this);
                this.isOnStation = true;
                Thread.sleep(stopTime_);
                this.isOnStation = false;
                target.setBackwardPlatformTrain(null);
            }
        }
    }

    /**
     * Check if train is on station
     * @return
     */
    public boolean isOnStation(){
        return isOnStation;
    }

    /**
     * Outer thread finish
     */
    public void finishThread(){
        this.finishThread = true;
    }


    /**
     * Get train name
     * @return
     */
    public String getName(){
        return this.name;
    }

    /**
     * Delete passenger from train
     * @param passenger
     */
    public void deletePassenger(Passenger passenger){
        synchronized (passengers){
            passengers.remove(passenger);
        }
    }

    public void addPassenger(Passenger passenger){
        synchronized (passengers){
            passengers.add(passenger);
        }
    }

    public List<Passenger> getPassengers(){
        return passengers;
    }

    public Station getCurrentStation(){
        return iterator.current();
    }

    @Override
    public void run() {
        while (!finishThread){
            try {
                this.goToNextStation();
            } catch (InterruptedException e) {
                logger.info("Interrupted exception in train object", e);
                throw new RuntimeException(e);
            }
        }
    }
}
