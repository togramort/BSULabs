package socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

class server_helper extends Thread {
    private final Socket socket;

    private final BufferedReader in;

    private final BufferedWriter out;

    public server_helper(Socket socket) throws IOException {
        this.socket = socket;
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        start();
    }

    @Override
    public void run() {
        String word;
        try {
            word = in.readLine();
            out.write(word + "\n");
            out.flush();

            while (true) {
                Scanner sc = new Scanner(new File("index.txt"));
                while (sc.hasNext()) {
                    System.out.println(sc.nextLine());
                }
                System.out.println("Choose client index");
                sc = new Scanner(System.in);
                int clientIndex = sc.nextInt();
                server.serverList.get(clientIndex).send();
            }
        } catch (IOException e) {
            try {
                this.downService();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
    }

    private void send() throws IOException {
        out.write("New message from server!" + "\n");
        out.flush();
    }

    private void downService() throws IOException {
        if (!socket.isClosed()) {
            socket.close();
            in.close();
            out.close();
            for (server_helper vr : server.serverList) {
                if (vr.equals(this)) vr.interrupt();
                server.serverList.remove(this);
            }
        }
    }
}