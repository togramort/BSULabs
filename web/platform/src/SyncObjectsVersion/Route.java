package SyncObjectsVersion;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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
     * Add one more station to the route
     * @param station
     */
    public void addNewRouteNode(Station station){
        this.stations.add(station);
        logger.info(String.format("Station %s added to the route %s", station.getName(), this.routeName));
    }

    /**
     * Get station of the route by index
     * @param index
     * @return
     */
    public Station getStation(int index){
        return stations.get(index);
    }

    /**
     * Get route length
     * @return
     */
    public int getRouteLength(){
        return stations.size();
    }

    /**
     * Get route direction
     * @return
     */
    public RouteDirection getDirection(){
        return this.direction;
    }
}
