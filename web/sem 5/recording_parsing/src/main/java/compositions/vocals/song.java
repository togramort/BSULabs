package compositions.vocals;

import compositions.record_builder;

import java.util.Objects;

;

public class song extends vocal_records {

    private final String genre;
    public String getGenre() {
        return genre;
    }

    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public song(record_builder builder) {
        super(builder);
        this.genre = builder.getGenre();
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
        song song = (song) o;
        return Objects.equals(genre, song.genre);
    }

    /**
     * @return hash of the composition
     */
    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), genre);
    }

    @Override
    public String toString() {
        return String.format("""
                        \nsong info:
                        name: %s
                        duration: %d
                        composer: %s
                        performers: %s
                        text writer: %s
                        genre: %s""",
                this.getName(), this.getDuration(), this.getComposer(), this.getPerformers(),
                this.getTextWriter(), this.getGenre());
    }
}