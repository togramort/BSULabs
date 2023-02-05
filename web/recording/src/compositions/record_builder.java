package compositions;

import compositions.instrumentals.*;
import compositions.vocals.*;
import java.util.ArrayList;

public class record_builder {

    private final String name;

    private int duration;

    private String composer;

    private final ArrayList<String> performers = new ArrayList<>();

    private String tonality;

    private String textWriter;

    private String genre;

    private String instrument;

    public String getName() {
        return name;
    }
    public int getDuration() {
        return duration;
    }
    public String getComposer() {
        return composer;
    }
    public ArrayList<String> getPerformers() {
        return performers;
    }
    public String getTonality() {
        return tonality;
    }
    public String getTextWriter() {
        return textWriter;
    }
    public String getGenre() {
        return genre;
    }
    public String getInstrument() {
        return instrument;
    }

    /**
     * @param name -- the name of the composition to build
     */
    public record_builder(String name) {
        this.name = name;
    }

    /**
     * @param duration -- the duration of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setDuration(int duration){
        this.duration = duration;
        return this;
    }

    /**
     * @param composer -- the composer of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setComposer(String composer){
        this.composer = composer;
        return this;
    }

    /**
     * @param performer -- the performer of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setPerformer(String performer){
        this.performers.add(performer);
        return this;
    }

    /**
     * @param tonality -- the tonality of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setTonality(String tonality){
        this.tonality = tonality;
        return this;
    }

    /**
     * @param textWriter -- the text writer of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setTextWriter(String textWriter){
        this.textWriter = textWriter;
        return this;
    }

    /**
     * @param genre -- the genre of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setGenre(String genre){
        this.genre = genre;
        return this;
    }

    /**
     * @param instrument -- the instrument of the composition to set
     * @return this CompositionBuilder
     */
    public record_builder setInstrument(String instrument){
        this.instrument = instrument;
        return this;
    }

    /**
     * @return the object Opera created with this builder
     */
    public opera recordOpera(){
        return new opera(this);
    }

    /**
     * @return the object Romance created with this builder
     */
    public romance recordRomance(){
        return new romance(this);
    }

    /**
     * @return the object Song created with this builder
     */
    public song recordSong(){
        return new song(this);
    }

    /**
     * @return the object Concert created with this builder
     */
    public concert recordConcert(){
        return new concert(this);
    }

    /**
     * @return the object Sonata created with this builder
     */
    public sonata recordSonata(){
        return new sonata(this);
    }

    /**
     * @return the object Symphony created with this builder
     */
    public symphony recordSymphony(){
        return new symphony(this);
    }
}
