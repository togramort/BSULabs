package socket;

import java.io.*;

public class client {

    public static String ipAddr = "localhost";
    public static int port = 8080;

    public static void main(String[] args) throws IOException {
        File file = new File("index.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));

        String st;
        BufferedWriter bw = new BufferedWriter(new FileWriter(file, true));

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
        new client_helper(ipAddr, port);
    }
}