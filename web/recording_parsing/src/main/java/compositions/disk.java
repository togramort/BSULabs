package compositions;

import cmp.cmpComposer;
import cmp.cmpDuration;
import cmp.cmpName;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.function.Consumer;

public class disk implements Iterable<records> {
    List<records> compositions = new ArrayList<>();

    /**
     * @param composition -- the composition to be added to the disk
     */
    public void addNewComposition(records composition) {
        this.compositions.add(composition);
    }

    public void recordComposition(records_list compositions, String name, int duration, String composer,
                                  String performer, String tonality, String textWriter, String genre, String instrument) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        record_builder builder = new record_builder(name).setComposer(composer)
                .setDuration(duration).setPerformer(performer).setGenre(genre).setInstrument(instrument)
                .setTextWriter(textWriter).setTonality(tonality);
        this.addNewComposition((records) builder.getClass().getMethod("record" + compositions.name()).invoke(builder));
    }

    /**
     * @return iterator for the compositions on the disk
     */
    @Override
    public Iterator<records> iterator() {
        return this.compositions.iterator();
    }

    /**
     * @param action -- the action to do with each element of the disk
     */
    @Override
    public void forEach(Consumer<? super records> action) {
        this.compositions.forEach(action);
    }

    public void sortName() {
        compositions.sort(new cmpName());
        compositions.forEach(System.out::println);
    }

    public void sortDur() {
        compositions.sort(new cmpDuration());
        compositions.forEach(System.out::println);
    }

    public void sortComp() {
        compositions.sort(new cmpComposer());
        compositions.forEach(System.out::println);
    }
    public void interval (int min, int max) {
        for (int i = 0; i < compositions.size(); ++i) {
            if (compositions.get(i).getDuration() > min && compositions.get(i).getDuration() > min) {
                System.out.println(compositions.get(i));
            }
        }
    }
}