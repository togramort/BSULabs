package compositions.vocals;

import compositions.record_builder;

public class opera extends vocal_records {
    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public opera(record_builder builder) {
        super(builder);
    }

    @Override
    public String toString() {
        return String.format("""
                        \nopera info:
                        name: %s
                        duration: %d
                        composer: %s
                        performers: %s
                        text writer: %s""",
                this.getName(), this.getDuration(), this.getComposer(), this.getPerformers(),
                this.getTextWriter());
    }
}
