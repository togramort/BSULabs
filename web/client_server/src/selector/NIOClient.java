package selector;

import java.util.logging.Logger;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

/**
 * Class represents nio client
 */
public class NIOClient {

    /**
     * Main method to do all the work.
     * @param args - com line params
     * @throws IOException - except
     */
    public static void main(String[] args) throws IOException {

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        final Logger logger = Logger.getLogger(NIOClient.class.getName() );

        InetSocketAddress addr = new InetSocketAddress("localhost", 1111);
        SocketChannel client = SocketChannel.open(addr);

        File file = new File("index.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));

        String st;
        FileWriter fr = new FileWriter(file, true);
        BufferedWriter bw = new BufferedWriter(fr);
        int i = 0;
        //depends on emptiness or fullness of index.txt
        if (br.readLine() != null) {
            while ((st = br.readLine()) != null) {
                i = Integer.parseInt(st.trim());
            }

            i++;
            bw.newLine();
            bw.write(String.valueOf(i));
        } else {
            bw.write(String.valueOf(i));
        }

        bw.close();
        br.close();
        fr.close();

        logger.info("Connecting to Server on port 1111...");
        String name;
        System.out.println("Enter your name:");
        name = reader.readLine();

        while (true) {
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            client.read(buffer);
            String data = new String(buffer.array()).trim();
            if (data.length() > 0) {
                logger.info(name + " received message: " + data);
                if (data.equalsIgnoreCase("exit")) {
                    client.close();
                    logger.info(name + "connection closed...");
                }
            }
        }
    }
}
