package cmp;

import compositions.records;
import java.util.Comparator;

public class comparator implements Comparator<records> {
    private final fields field;

    /**
     * @param field -- the field to compare to with
     */
    public comparator(fields field) {
        this.field = field;
    }

    /**
     * @param o1 -- the composition to compare
     * @param o2 -- the composition to compare
     * @return true if compositions are equals, else false
     */

    @Override
    public int compare(records o1, records o2) {
        if (field == fields.name) {
            if (o1.getName().equals(o2.getName())) {
                return 0;
            } else {
                return -1;
            }
        } else if (field == fields.duration) {
            if (o1.getDuration() == o2.getDuration()) {
                return 0;
            } else {
                return -1;
            }
        }  else if (field == fields.composer) {
            if (o1.getComposer().equals(o2.getComposer())) {
                return 0;
            } else {
                return -1;
            }
        }
        return 0;
    }
}
