package compositions.xml.parsers;

import compositions.disk;
/**
 * Parsing interface
 */

public interface CompositionsParser {
    disk parse(String fileName) throws ParserException;
}