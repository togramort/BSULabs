package Lexemes;

import Parsers.SentenceParser;


import java.util.ArrayList;

/**
 * Class for parsing and storage of sentence lexemes
 */
public class Sentence implements Lexeme {
    private ArrayList<Lexeme> parsedSentence;
    private static SentenceParser parser = new SentenceParser();

    public Sentence(String sentence) {
        this.parsedSentence = parser.parse(sentence);
    }

    public void deleteFirstLetterRepetition(){
        for (Lexeme lexeme: parsedSentence){
            if (lexeme instanceof Word){
                ((Word) lexeme).deleteFirstLetterRepetition();
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < parsedSentence.size(); ++i){
            if (i != 0){
                if (parsedSentence.get(i - 1) instanceof PunctuationMark){
                    if (parsedSentence.get(i) instanceof Word){
                        if (!parsedSentence.get(i - 1).toString().equals("(")){
                            builder.append(" ");
                        }
                    }
                }else{
                    if (parsedSentence.get(i) instanceof Word){
                        builder.append(" ");
                    }
                    if (parsedSentence.get(i) instanceof PunctuationMark){
                        if (parsedSentence.get(i).toString().equals("\"") || parsedSentence.get(i).toString().equals("-") || parsedSentence.get(i).toString().equals("(")){
                            builder.append(" ");
                        }
                    }
                }
            }
            builder.append(parsedSentence.get(i));
        }

        return builder.toString();
    }
}