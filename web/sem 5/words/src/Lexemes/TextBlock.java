package Lexemes;
import Parsers.TextBlockParser;


import java.util.ArrayList;

/**
 * Class for text block lexemes
 */
public class TextBlock implements Lexeme{
    private ArrayList<Lexeme> parsedTextBlock;
    private static TextBlockParser parser = new TextBlockParser();

    public TextBlock(String textBlock) {
        parsedTextBlock = parser.parse(textBlock);
    }


    /**
     * Variant method for individual task(delete first letter repetition in each word)
     */
    public void deleteFirstLetterRepetition(){
        for (Lexeme lexeme: parsedTextBlock) {
            if (lexeme instanceof Sentence){
                ((Sentence) lexeme).deleteFirstLetterRepetition();
            }
        }
    }

    @Override
    public String toString() {
        String[] text = new String[parsedTextBlock.size() / 2];
        for (int i = 0; i < text.length; ++i){
            text[i] = parsedTextBlock.get(2 * i).toString() + parsedTextBlock.get(2 * i + 1).toString();
        }
        return String.join("", text) + "\n";
    }
}
