package socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;

public class server {
    public static final int PORT = 8080;
    public static LinkedList<server_helper> serverList = new LinkedList<>();

    public static void main(String[] args) throws IOException {
        try (ServerSocket server = new ServerSocket(PORT)) {
            while (true) {
                Socket socket = server.accept();
                try {
                    serverList.add(new server_helper(socket));
                } catch (IOException e) {
                    socket.close();
                }
            }
        }
    }
}