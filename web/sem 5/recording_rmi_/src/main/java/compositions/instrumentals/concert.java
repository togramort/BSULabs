package compositions.instrumentals;

import compositions.*;

import java.util.Objects;

public class concert extends instrumental_records {
    private String instrument;
    public String getInstrument() {
        return instrument;
    }
    public void setInstrument(String instrument) {
        this.instrument = instrument;
    }

    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public concert(record_builder builder) {
        super(builder);
        this.instrument = builder.getInstrument();
    }

    /**
     * @param o -- the object to compare to
     * @return true if the objects to compare are equals, else false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        if (!super.equals(o))
            return false;
        concert concert = (concert) o;
        return Objects.equals(instrument, concert.instrument);
    }

    /**
     * @return hash of the composition
     */
    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), instrument);
    }

    @Override
    public String toString() {
        return String.format("""
                        \nconcert info:
                        name: %s
                        duration: %d
                        composer: %s
                        performers: %s
                        tonality: %s
                        instrument: %s""",
                this.getName(), this.getDuration(), this.getComposer(), this.getPerformers(),
                this.getTonality(), this.getInstrument());
    }
}
