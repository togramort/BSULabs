package WaitNotifyVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Railway route for trains
 */
public class Route {
    static Logger logger = LogManager.getLogger(Route.class.getPackageName());
    private List<Station> stations;
    private String routeName;
    private RouteDirection direction;

    public Route(String name, RouteDirection direction) {
        this.stations = Collections.synchronizedList(new ArrayList<Station>());
        this.routeName = name;
        this.direction = direction;
    }

    /**
     * Get station of the route by index
     * @param index index
     * @return index of station
     */
    public Station getStation(int index){
        return stations.get(index);
    }

    /**
     * Get route length
     * @return size of stations
     */
    public int getRouteLength(){
        return stations.size();
    }

    /**
     * Get route direction
     * @return direction
     */
    public RouteDirection getDirection(){
        return this.direction;
    }
}
