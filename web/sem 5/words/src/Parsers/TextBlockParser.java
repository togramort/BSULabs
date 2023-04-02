package Parsers;

import Lexemes.Lexeme;
import Lexemes.PunctuationMark;
import Lexemes.Sentence;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Class to parse text block for sentences and punctuation marks
 */
public class TextBlockParser {

    /**
     * Parse text block for sentences and punctuation marks
     * @param textBlock part of text
     * @return list of lexemes
     */
    public ArrayList<Lexeme> parse(String textBlock){
        String regex = "(\\.{3} |\\.{3}$)|(\\. |\\.$)|(! |!$)|(\\? |\\?$)";
        ArrayList<Lexeme> result = new ArrayList<>();
        String[] sentences = textBlock.split(regex);
        ArrayList<String> punctuationMarks = new ArrayList<String>();
        Matcher m = Pattern.compile(regex).matcher(textBlock);
        while (m.find()) {
            punctuationMarks.add(m.group());
        }
        for (int i = 0; i < sentences.length; ++i){
            result.add(new Sentence(sentences[i]));
            result.add(new PunctuationMark(punctuationMarks.get(i)));
        }
        return result;
    }
}

