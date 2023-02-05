package compositions.xml.parsers;

import compositions.records;
import compositions.disk;
import compositions.records_list;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.core.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;


/**
 * DOM parser of XML
 */

public class DOMParser implements CompositionsParser {

    private static final Logger logger = (Logger) LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     */
    @Override
    public disk parse(String fileName) throws ParserException {
        logger.info("Starting DOM-parsing");
        disk disk = new disk();

        File inputFile = new File(fileName);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder;
        Document doc;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            doc = dBuilder.parse(inputFile);
        } catch (SAXException | IOException | ParserConfigurationException e) {
            logger.warn("Configuration DOM-parser error");
            throw new ParserException("Configuration DOM-parser error", e);
        }
        doc.getDocumentElement().normalize();


        NodeList concertNodes = doc.getElementsByTagName("concert");
        NodeList sonataNodes = doc.getElementsByTagName("sonata");
        NodeList symphonyNodes = doc.getElementsByTagName("symphony");
        NodeList operaNodes = doc.getElementsByTagName("opera");
        NodeList romanceNodes = doc.getElementsByTagName("romance");
        NodeList songNodes = doc.getElementsByTagName("song");


        for (int i = 0; i < concertNodes.getLength(); i++) {
            Node node = concertNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String tonality = element.getElementsByTagName("tonality").item(0).getTextContent();
                String instrument = element.getElementsByTagName("instrument").item(0).getTextContent();


                disk.recordComposition(records_list.Concert, name, duration, composer, performers.get(0),
                        tonality, null, null, instrument);
            }
        }

        for (int i = 0; i < sonataNodes.getLength(); i++) {
            Node node = sonataNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String tonality = element.getElementsByTagName("tonality").item(0).getTextContent();

                disk.recordComposition(records_list.Sonata, name, duration, composer, performers.get(0),
                        tonality, null, null, null);
            }
        }

        for (int i = 0; i < symphonyNodes.getLength(); ++i) {
            Node node = symphonyNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String tonality = element.getElementsByTagName("tonality").item(0).getTextContent();

                disk.recordComposition(records_list.Symphony, name, duration, composer, performers.get(0),
                        tonality, null, null, null);
            }
        }

        for (int i = 0; i < operaNodes.getLength(); ++i) {
            Node node = operaNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String textWriter = element.getElementsByTagName("textWriter").item(0).getTextContent();

                disk.recordComposition(records_list.Opera, name, duration, composer, performers.get(0),
                        null, textWriter, null, null);
            }
        }

        for (int i = 0; i < romanceNodes.getLength(); ++i) {
            Node node = romanceNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String textWriter = element.getElementsByTagName("textWriter").item(0).getTextContent();

                disk.recordComposition(records_list.Romance, name, duration, composer, performers.get(0),
                        null, textWriter, null, null);
            }
        }

        for (int i = 0; i < songNodes.getLength(); ++i) {
            Node node = songNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                int duration = Integer.parseInt(element.getElementsByTagName("duration").item(0).getTextContent());
                String composer = element.getElementsByTagName("composer").item(0).getTextContent();
                var performers = new ArrayList<String>();
                for (int j = 0; j < element.getElementsByTagName("performers").getLength(); j++) {
                    performers.add(element.getElementsByTagName("performers").item(0).getTextContent());
                }
                String textWriter = element.getElementsByTagName("textWriter").item(0).getTextContent();
                String genre = element.getElementsByTagName("genre").item(0).getTextContent();

                disk.recordComposition(records_list.Song, name, duration, composer, performers.get(0),
                        null, textWriter, genre, null);
            }
        }

        logger.info("Finishing DOM-parsing");
        return disk;
    }

}