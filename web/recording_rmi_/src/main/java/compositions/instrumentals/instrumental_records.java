package compositions.instrumentals;

import compositions.*;

import java.util.Objects;

public abstract class instrumental_records extends records {

    private String tonality;
    public String getTonality() {
        return tonality;
    }
    public void setTonality(String tonality) {
        this.tonality = tonality;
    }


    /**
     * @param builder -- the record_builder used to create new composition
     */
    public instrumental_records(record_builder builder) {
        super(builder);
        this.tonality = builder.getTonality();
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
        instrumental_records ic = (instrumental_records) o;
        return Objects.equals(tonality, ic.tonality);
    }

    /**
     * @return hash of the composition
     */
    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), tonality);
    }
}
