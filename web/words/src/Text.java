import Lexemes.Lexeme;
import Lexemes.TextBlock;
import Parsers.TextParser;


import java.util.ArrayList;

public class Text {
    private ArrayList<Lexeme> parsedText;
    private TextParser parser;

    public Text(String text) {
        parser = new TextParser();
        parser.parseText(text);
        parsedText = parser.getParsedText();
    }

    public void deleteFirstLetterRepetition(){
        for (Lexeme lexeme: parsedText) {
            if (lexeme instanceof TextBlock){
                ((TextBlock) lexeme).deleteFirstLetterRepetition();
            }
        }
    }

    @Override
    public String toString(){
        StringBuilder result = new StringBuilder();
        for (Lexeme lexeme: parsedText){
            result.append(lexeme.toString()).append("\n");
        }

        return result.toString();
    }
}
