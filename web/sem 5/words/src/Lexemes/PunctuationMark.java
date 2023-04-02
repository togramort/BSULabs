package Lexemes;

/**
 * Class for punctuation mark storage
 */
public class PunctuationMark implements Lexeme{
    private String mark;

    public PunctuationMark(String mark) {
        this.mark = mark;
    }

    @Override
    public String toString() {
        return mark;
    }
}
