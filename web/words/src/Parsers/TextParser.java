package Parsers;

import Lexemes.CodeListing;
import Lexemes.Lexeme;
import Lexemes.TextBlock;

import java.util.ArrayList;

/**
 * Class to parse text for text blocks and code listings
 */
public class TextParser {
    private ArrayList<Lexeme> parsedText;
    private static SentenceParser sentenceParser = new SentenceParser();
    public TextParser() {
        parsedText = new ArrayList<>();
    }

    /**
     * Delete system symbols that fits \\s
     * @param text text
     * @return cleaned text
     */
    private String cleanText(String text){
        return text.trim().replaceAll("\\s+", " ").trim();
    }

    /**
     * Parse text for code listings and text blocks
     * @param initialText text
     */
    public void parseText(String initialText){
        String text = new String(initialText);
        String[] splitByCodeBlock = text.split("<code>");
        String[] splitBuffer;
        String cleanedText;
        for (String block : splitByCodeBlock) {
            if (block.contains("</code>")) {
                splitBuffer = block.split("</code>");
                parsedText.add(new CodeListing(splitBuffer[0]));
                cleanedText = cleanText(splitBuffer[1]);
            }else{
                cleanedText = cleanText(block);
            }
            if (!cleanedText.isEmpty()){
                parsedText.add(new TextBlock(cleanedText));
            }
        }
    }

    /**
     * Get parsed text
     * @return parsed text
     */
    public ArrayList<Lexeme> getParsedText(){
        return parsedText;
    }
}
