package compositions;

import java.util.ArrayList;
import java.util.Objects;

public abstract class records {
    private final String name;
    private final int duration;
    private final String composer;
    private final ArrayList<String> performers;

    public String getName() {
        return name;
    }
    public int getDuration() {
        return duration;
    }
    public String getComposer() {
        return composer;
    }
    public ArrayList<String> getPerformers() {
        return performers;
    }

    /**
     * @param builder -- the record_builder used to create new record
     */
    public records(record_builder builder) {
        this.name = builder.getName();
        this.composer = builder.getComposer();
        this.performers = builder.getPerformers();
        this.duration = builder.getDuration();
    }

    /**
     * @param o -- the object to compare to
     * @return true if the objects to compare are equals, else false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        records plane = (records) o;
        return Objects.equals(name, plane.name) && duration == plane.duration
                && Objects.equals(composer, plane.composer) && performers == plane.performers;
    }

    /**
     * @return hash of the composition
     */
    @Override
    public int hashCode() {
        return Objects.hash(name, duration, composer, performers);
    }

}
