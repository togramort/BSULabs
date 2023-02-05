package compositions.vocals;

import compositions.records;
import compositions.record_builder;
import java.util.ArrayList;
import java.util.Objects;

public abstract class vocal_records extends records{
    private final String textWriter;
    public String getTextWriter() {
        return textWriter;
    }

    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public vocal_records(record_builder builder) {
        super(builder);
        this.textWriter = builder.getTextWriter();
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
        if (!super.equals(o)) {
            return false;
        }
        vocal_records vc = (vocal_records) o;
        return Objects.equals(textWriter, vc.textWriter);
    }

    /**
     * @return hash of the composition
     */
    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), textWriter);
    }

}
