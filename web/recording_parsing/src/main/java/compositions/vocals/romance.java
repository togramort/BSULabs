package compositions.vocals;

import compositions.record_builder;

public class romance extends vocal_records {
    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public romance(record_builder builder) {
        super(builder);
    }

    @Override
    public String toString() {
        return String.format("""
                        \nromance info:
                        name: %s
                        duration: %d
                        composer: %s
                        performers: %s
                        text writer: %s""",
                this.getName(), this.getDuration(), this.getComposer(), this.getPerformers(),
                this.getTextWriter());
    }
}
