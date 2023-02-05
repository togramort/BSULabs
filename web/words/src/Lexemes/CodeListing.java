package Lexemes;

/**
 * Class to for code listing storage
 */
public class CodeListing implements Lexeme {
    private String code;

    public CodeListing(String code) {
        this.code = code;
    }

    @Override
    public String toString() {
        return "<code>\n" + code + "\n</code>";
    }
}
