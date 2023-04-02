package compositions;

import compositions.disk;
import compositions.xml.parsers.DOMParser;
import compositions.xml.parsers.ParserException;
import compositions.xml.parsers.SAXParser;
import compositions.xml.parsers.StAXParser;

public class controller {
    /**
     * @param filePath path to the file to read
     * @param parserType type of the parser to parse with
     * @return parsing disk
     * @throws ParserException
     */
    public static disk parse(String filePath, parser_type parserType) throws ParserException {
        disk disk;
        switch (parserType){
            case DOM -> disk = (new DOMParser()).parse(filePath);
            case SAX -> disk = (new SAXParser()).parse(filePath);
            case StAX -> disk = (new StAXParser()).parse(filePath);
            default -> throw new ParserException("Something wrong while parsing");
        }
        return disk;
    }
}