package cmp;

import compositions.records;

import java.util.Comparator;

public class cmpComposer implements Comparator<records>{
    @Override
    public int compare(records r1, records r2) {
        String r1comp = r1.getComposer();
        String r2comp = r2.getComposer();
        return r1comp.compareTo(r2comp);
    }
}
