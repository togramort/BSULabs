package WaitNotifyVersion;

/**
 * Iterator for the railway route
 */
public class RouteIterator {
    private int currentIndex;
    private Route route;
    private int routeLength;

    public RouteIterator(Route route) {
        currentIndex = -1;
        this.route = route;
        routeLength = route.getRouteLength();
        if (routeLength == 0){
            throw new IllegalArgumentException("Empty root in root iterator");
        }
    }

    /**
     * Get next station of the route
     * @return
     */
    public synchronized Station next(){
        ++currentIndex;
        if (currentIndex == routeLength){
            currentIndex = 0;
        }
        return route.getStation(currentIndex);
    }

    /**
     * Get current station of the route
     * @return
     */
    public synchronized Station current(){
        return route.getStation(currentIndex);
    }
}
