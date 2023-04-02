package compositions.xml.parsers;

import compositions.records;
import compositions.disk;

import compositions.records_list;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

/**
 * StAX parser of XML
 */

public class StAXParser implements CompositionsParser {

    private static final Logger logger = LogManager.getLogger("Parser");


    /**
     * Parse XML file to collective using StAX parser
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public disk parse(String fileName) throws ParserException {
        logger.info("Starting StAX-parsing");
        disk disk = new disk();

        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader eventReader;
        try {
            eventReader = factory.createXMLEventReader(new FileReader(fileName));
        } catch (XMLStreamException | FileNotFoundException e) {
            logger.warn("Configuration StAX-parser error");
            throw new ParserException("Configuration StAX-parser error", e);
        }
        String currentElement = "";
        boolean parsed = true;
        String name = "";
        int duration = 0;
        String composer = "";
        ArrayList<String> performers = new ArrayList<>();
        String tonality = "";
        String textWriter = "";
        String genre = "";
        String instrument = "";


        while (eventReader.hasNext()) {
            XMLEvent event;
            try {
                event = eventReader.nextEvent();
            } catch (XMLStreamException e) {
                logger.warn("Fail to get eventReader");
                throw new ParserException("Fail to get eventReader", e);
            }
            String qName;

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT -> {
                    StartElement startElement = event.asStartElement();
                    qName = startElement.getName().getLocalPart();
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
                case XMLStreamConstants.CHARACTERS -> {
                    String value = event.asCharacters().getData();
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
                case XMLStreamConstants.END_ELEMENT -> {
                    EndElement endElement = event.asEndElement();
                    qName = endElement.getName().getLocalPart();
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
            }
        }

        logger.info("Finishing StAX-parsing");
        return disk;
    }
}