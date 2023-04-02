package cmp;

import compositions.records;

import java.util.Comparator;

public class cmpName implements Comparator<records> {
    @Override
    public int compare(records r1, records r2) {
        String r1Name = r1.getName();
        String r2Name = r2.getName();
        return r1Name.compareTo(r2Name);
    }
}
