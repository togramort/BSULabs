package Lexemes;

/**
 * Class for word storage
 */
public class Word implements Lexeme {
    private String word;

    public Word(String word) {
        this.word = word;
    }

    /**
     * Variant method for individual task(delete first letter repetition)
     */
    public void deleteFirstLetterRepetition(){
        word = word.charAt(0) + word.substring(1).replace(String.valueOf(word.charAt(0)), "");
    }

    @Override
    public String toString() {
        return word;
    }
}
