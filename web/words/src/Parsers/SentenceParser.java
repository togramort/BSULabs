package Parsers;

import Lexemes.Lexeme;
import Lexemes.PunctuationMark;
import Lexemes.Word;


import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Class to parse sentence to lexemes
 */
public class SentenceParser {
    /**
     * Split string with words without punctuation mark to word list
     * @param sentence_part part of the sentence
     * @return list of words
     */
    private ArrayList<Lexeme> splitForWords(String sentence_part){
        String[] words_str = sentence_part.trim().split(" ");
        ArrayList<Lexeme> result = new ArrayList<>();
        for (String s : words_str) {
            result.add(new Word(s));
        }

        return result;
    }

    /**
     * Parse sentence for punctuation marks and words
     * @param sentence sentence
     * @return list of lexemes
     */
    public ArrayList<Lexeme> parse(String sentence){
        ArrayList<Lexeme> result = new ArrayList<>();
        String[] sentence_parts = sentence.split("\\p{Punct}");
        ArrayList<String> punctuationMarks = new ArrayList<String>();
        Matcher m = Pattern.compile("\\p{Punct}").matcher(sentence);
        while (m.find()) {
            punctuationMarks.add(m.group());
        }
        for (int i = 0; i < sentence_parts.length; ++i){
            result.addAll(splitForWords(sentence_parts[i]));
            if (i < punctuationMarks.size()){
                result.add(new PunctuationMark(punctuationMarks.get(i)));
            }
        }

        return result;
    }
}
