package server;

import compositions.records;
import compositions.disk;
public class disk_util {
    /**
     * @param d -- the disk to calculate duration
     * @return the total duration of all compositions on the disk
     */
    public static int getDuration(disk d) {
        int sum = 0;
        for (var c : d) {
            sum += c.getDuration();
        }
        return sum;
    }

    /**
     * @param d -- the disk to search in
     * @param name -- the name to search
     * @param duration -- the duration to search
     * @param composer -- the composer to search
     * @return
     */
    public static records search(disk d, String name, Integer duration, String composer) {
        for (var c : d) {
            var cName = name == null ? null : c.getName();
            var cDuration = duration == 0 ? 0 : c.getDuration();
            var cComposer = composer == null ? null : c.getComposer();
            if ((cName == null || cName.equals(name)) &&
                    (cDuration == 0 || cDuration == duration) &&
                    (cComposer == null || cComposer.equals(composer))) {
                return c;
            }
        }
        return null;
    }
}
