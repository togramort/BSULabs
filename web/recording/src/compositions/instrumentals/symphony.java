package compositions.instrumentals;

import compositions.record_builder;

public class symphony extends instrumental_records {
    /**
     * @param builder -- the CompositionBuilder used to create new composition
     */
    public symphony(record_builder builder) {
        super(builder);
    }

    @Override
    public String toString() {
        return String.format("""
                        \nsymphony info:
                        name: %s
                        duration: %d
                        composer: %s
                        performers: %s
                        tonality: %s""",
                this.getName(), this.getDuration(), this.getComposer(), this.getPerformers(),
                this.getTonality());
    }
}
