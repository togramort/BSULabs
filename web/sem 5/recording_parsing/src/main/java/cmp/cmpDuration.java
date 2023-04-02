package cmp;

import compositions.records;

import java.util.Comparator;

public class cmpDuration implements Comparator<records> {
    @Override
    public int compare(records r1, records r2) {
        return Integer.compare(r1.getDuration(), r2.getDuration());
    }
}