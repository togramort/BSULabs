package selector;

import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.logging.Logger;

/**
 * Class represents Nio server
 */
public class NIOServer {

    /**
     * Main method to do the task.
     * @param args - command line args.
     * @throws IOException - exception
     */
    @SuppressWarnings("unused")
    public static void main(String[] args) throws IOException {

        final Logger logger = Logger.getLogger( NIOServer.class.getName() );
        //final Random random = new Random();
        ArrayList<SocketChannel> clients = new ArrayList<>();
        //create selector
        Selector selector = Selector.open();
        //канал сервера сокетов
        ServerSocketChannel servSocket = ServerSocketChannel.open();
        InetSocketAddress addr = new InetSocketAddress("localhost", 1111);
        //привязка сокета к каналу
        servSocket.bind(addr);
        servSocket.configureBlocking(false);
        //(возвр операции которые поддерживаются каналом)
        //каналы сервера сокетов поддерживают только принятие соединений
        int ops = servSocket.validOps();
        SelectionKey selectKy = servSocket.register(selector, ops, null);

        while (true) {
            logger.info("i'm a server and i'm waiting for new connection and buffer select...");
            //ожидание поступления данных для обработки
            selector.select();
            //получаем набор ключей которые готовы для обработки (зарегестрировано и ждет данных)
            Set<SelectionKey> keys = selector.selectedKeys();

            for (SelectionKey myKey : keys) {
                if (myKey.isAcceptable()) {
                    SocketChannel client = servSocket.accept();
                    client.configureBlocking(false);
                    client.register(selector, SelectionKey.OP_READ);
                    logger.info("Connection Accepted: " + client.getLocalAddress() + "\n");
                    clients.add(client);
                }

                Scanner sc = new Scanner(new File("index.txt"));
                while (sc.hasNext()) {
                    System.out.println(sc.nextLine());
                }
                System.out.println("Choose client index");
                sc = new Scanner(System.in);
                int clientIndex = sc.nextInt();

                byte[] message = "New message from server!".getBytes();
                ByteBuffer buffer = ByteBuffer.wrap(message);
                clients.get(clientIndex).write(buffer);
                buffer.clear();
            }
        }
    }

}