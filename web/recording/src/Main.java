import cmp.fields;
import compositions.*;
import compositions.instrumentals.concert;
import compositions.vocals.opera;
import compositions.vocals.song;

public class Main {
    public static void main(String[] args) {
        record_builder builder1 = new record_builder("hb");
        builder1.setDuration(113);
        builder1.setComposer("comp11");
        builder1.setPerformer("perf1");
        builder1.setPerformer("perfffff1");
        builder1.setGenre("pop");

        records rec1;
        records rec2;
        records rec3;

        rec1 = new song(builder1);

        record_builder builder2 = new record_builder("your name");
        builder2.setDuration(158);
        builder2.setComposer("comp222");
        builder2.setPerformer("perf2");
        builder2.setInstrument("piano");

        rec2 = new concert(builder2);

        record_builder builder3 = new record_builder("hahahehe");
        builder3.setDuration(99);
        builder3.setComposer("comp3");
        builder3.setPerformer("perf3");
        builder3.setTextWriter("dumet");

        rec3 = new opera(builder3);

        disk disk = new disk();
        disk.addNewComposition(rec1);
        disk.addNewComposition(rec2);
        disk.addNewComposition(rec3);
        disk.forEach(System.out::println);
        System.out.println("sort\n");
        disk.sortComp();
        System.out.println("interval\n");
        disk.interval(100, 160);
        
    }
}
