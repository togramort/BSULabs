package SyncObjectsVersion;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

public class Train implements Runnable{
    private int stopTime_;
    private String name;
    private int timeBetweenStations_;
    private Route route;
    private RouteIterator iterator;
    private boolean isOnStation = false;
    private boolean finishThread = false;
    private List<Passenger> passengers;
    private ReentrantLock locker;

    public Train(int stopTime, int timeBetweenStations, Route route, String name) {
        this.stopTime_ = stopTime;
        this.timeBetweenStations_ = timeBetweenStations;
        this.route = route;
        this.name = name;
        this.iterator = new RouteIterator(route);
        this.passengers = Collections.synchronizedList(new ArrayList<>());
        this.locker = new ReentrantLock();
    }

    /**
     * Move train to the next station in the route
     * @throws InterruptedException exception
     */
    public void goToNextStation() throws InterruptedException {
        Thread.sleep(timeBetweenStations_);
        Station target = this.iterator.next();
        if (this.route.getDirection() == RouteDirection.Forward){
            target.forwardPlatform.lock();
            target.setForwardPlatformTrain(this);
            this.isOnStation = true;
            Thread.sleep(stopTime_);
            this.isOnStation = false;
            target.setForwardPlatformTrain(null);
            target.forwardPlatform.unlock();
        }else{
            target.backwardPlatform.lock();
            target.setBackwardPlatformTrain(this);
            this.isOnStation = true;
            Thread.sleep(stopTime_);
            this.isOnStation = false;
            target.setBackwardPlatformTrain(null);
            target.backwardPlatform.unlock();
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
        locker.lock();
        passengers.remove(passenger);
        locker.unlock();
    }

    public void addPassenger(Passenger passenger){
        locker.lock();
        passengers.add(passenger);
        locker.unlock();
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
                throw new RuntimeException(e);
            }
        }
    }
}
