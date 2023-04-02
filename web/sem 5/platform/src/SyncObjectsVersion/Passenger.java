package SyncObjectsVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Random;

public class Passenger implements Runnable{
    private String name_;
    private static final Random random = new Random();
    private static final Logger logger = LogManager.getLogger(Passenger.class.getPackageName());
    private PassengerPosition position;
    private Train train;
    private Station station;
    private boolean finishThread = false;

    public Passenger(String name_, Train train, Station station) {
        this.name_ = name_;
        this.train = train;
        this.station = station;
        if (station == null){
            this.position = PassengerPosition.Train;
            this.station = null;
        }else{
            this.position = PassengerPosition.Station;
            this.train = null;
        }
    }

    /**
     * Specify if passenger want to change position
     * @return integer that specifies decision
     */
    public boolean wantToMove(){
        return random.nextInt(2) == 1;
    }

    /**
     * Move passenger from train to station
     * @param station target station
     * @throws InterruptedException exception
     */
    public synchronized void moveToStation(Station station) throws InterruptedException {
        if (wantToMove()){
            if (!this.train.isOnStation()){
                return;
            }
            logger.info(String.format("Passenger %s leaved train %s and now on station %s", this.name_, this.train.getName(), station.getName()));
            this.train.deletePassenger(this);
            this.train = null;
            this.position = PassengerPosition.Station;
            this.station = station;
            this.station.addPassenger(this);
            Thread.sleep(5000);
        }
    }

    /**
     * Move passenger to the train container
     * @param train target train
     * @throws InterruptedException exception
     */
    public synchronized void moveToTrain(Train train) throws InterruptedException {
        if (wantToMove()){
            if (!train.isOnStation()){
                return;
            }
            logger.info(String.format("Passenger %s leaved station %s and now in train %s", this.name_, station.getName(), train.getName()));
            this.station.deletePassenger(this);
            this.station = null;
            this.position = PassengerPosition.Train;
            this.train = train;
            this.train.addPassenger(this);
            Thread.sleep(3000);
        }
    }

    /**
     * Outer thread finish
     */
    public void finishThread(){
        finishThread = true;
    }

    /**
     * Override method to run thread
     */
    @Override
    public void run() {
        while (!finishThread){
            switch (position){
                case Train -> {
                    synchronized (this.train){
                        try {
                            this.moveToStation(train.getCurrentStation());
                        } catch (InterruptedException e) {
                            logger.info("Passenger interrupted exception", e);
                            throw new RuntimeException(e);
                        }
                    }
                }
                case Station -> {
                    synchronized (this.station){
                        Train trainOnStation = this.station.getSpareTrain();
                        if (trainOnStation == null){
                            continue;
                        }
                        try {
                            this.moveToTrain(trainOnStation);
                        } catch (InterruptedException e) {
                            logger.info("Passenger interrupted exception", e);
                            throw new RuntimeException(e);
                        }
                    }
                }
            }
        }
    }
}
