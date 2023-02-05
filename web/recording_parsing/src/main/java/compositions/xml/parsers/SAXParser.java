package compositions.xml.parsers;

import compositions.records;
import compositions.disk;

import compositions.records_list;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * SAX parser of XML
 */

public class SAXParser implements CompositionsParser {

    private static final Logger logger = LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using SAX parser
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public disk parse(String fileName) throws ParserException {
        logger.info("Starting SAX-parsing");
        disk disk;

        try {
            File inputFile = new File(fileName);
            SAXParserFactory factory = SAXParserFactory.newInstance();
            javax.xml.parsers.SAXParser saxParser = factory.newSAXParser();
            Handler handler = new Handler();
            saxParser.parse(inputFile, handler);
            disk = handler.getDisk();
        } catch (IOException | SAXException | ParserConfigurationException e) {
            logger.warn("Configuration SAX-parser error");
            throw new ParserException("Configuration SAX-parser error", e);
        }

        logger.info("Finishing SAX-parsing");
        return disk;
    }

    /**
     * Tags handler
     */
    private class Handler extends DefaultHandler {

        private disk disk = new disk();
        public disk getDisk() {
            return disk;
        }

        private boolean parsed = true;
        private String currentElement;

        private String name;
        private int duration;
        private String composer;
        private final ArrayList<String> performers = new ArrayList<>();
        private String tonality;
        private String textWriter;
        private String genre;
        private String instrument;

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) {
            currentElement = qName;
            if (qName.equals("name") ||
                    qName.equals("duration") ||
                    qName.equals("composer") ||
                    qName.equals("performers") ||
                    qName.equals("tonality") ||
                    qName.equals("textWriter") ||
                    qName.equals("genre") ||
                    qName.equals("instrument")) {
                parsed = false;
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) {
            switch (qName) {
                case "concert" -> disk.recordComposition(records_list.Concert, name, duration, composer,
                        performers.get(0), tonality, null, null, instrument);
                case "sonata" -> disk.recordComposition(records_list.Sonata, name, duration, composer,
                        performers.get(0), tonality, null, null, null);
                case "symphony" -> disk.recordComposition(records_list.Symphony, name, duration, composer,
                        performers.get(0), tonality, null, null, null);
                case "opera" -> disk.recordComposition(records_list.Opera, name, duration, composer, performers.get(0),
                        null, textWriter, null, null);
                case "romance" -> disk.recordComposition(records_list.Romance, name, duration, composer,
                        performers.get(0), null, textWriter, null, null);
                case "song" -> disk.recordComposition(records_list.Song, name, duration, composer, performers.get(0),
                        null, textWriter, genre, null);
            }
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            String value = new String(ch, start, length);
            if (!parsed) {
                switch (currentElement) {
                    case "name" -> name = value;
                    case "duration" -> duration = Integer.parseInt(value);
                    case "composer" -> composer = value;
                    case "performers" -> performers.add(value);
                    case "tonality" -> tonality = value;
                    case "textWriter" -> textWriter = value;
                    case "genre" -> genre = value;
                    case "instrument" -> instrument = value;
                }

                parsed = true;
            }
        }
    }
}