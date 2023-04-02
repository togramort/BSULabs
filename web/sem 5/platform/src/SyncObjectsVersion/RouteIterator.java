package SyncObjectsVersion;

import java.util.concurrent.locks.ReentrantLock;

/**
 * Iterator for the railway route
 */
public class RouteIterator {
    private int currentIndex;
    private Route route;
    private int routeLength;
    private ReentrantLock locker;

    public RouteIterator(Route route) {
        this.currentIndex = -1;
        this.route = route;
        this.routeLength = route.getRouteLength();
        this.locker = new ReentrantLock();
        if (routeLength == 0){
            throw new IllegalArgumentException("Empty root in root iterator");
        }
    }

    /**
     * Get next station of the route
     * @return next station
     */
    public Station next(){
        locker.lock();
        ++currentIndex;
        if (currentIndex == routeLength){
            currentIndex = 0;
        }
        Station station = route.getStation(currentIndex);
        locker.unlock();
        return station;
    }

    /**
     * Get current station of the route
     * @return current station
     */
    public Station current(){
        locker.lock();
        Station station = route.getStation(currentIndex);
        locker.unlock();
        return station;
    }
}
