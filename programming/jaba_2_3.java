import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNextLine()) {
            String s = in.nextLine();
            StringBuilder bul = new StringBuilder(s);

            for (int i = 0; i < bul.length(); ) {
                if (bul.charAt(i) == '.') {
                    boolean check = false;
                    for (int j = i + 1; j < i + 3 && j < bul.length(); ++j) {
                        if (!Character.isDigit(bul.charAt(j))) {
                            ++i;
                            check = true;
                            break;
                        }
                    }
                    if (check) {
                        continue;
                    }
                    i = i + 3;
                    while (i < bul.length() && Character.isDigit(bul.charAt(i))) {
                        bul.deleteCharAt(i);
                    }

                } else {
                    ++i;
                }
            }
            System.out.println(bul);
        }
        in.close();
        System.exit(0);
    }
}
/* abufbu.1463ogtko - abufbu.14ogtko
.123456q - .12q
ifman.13245 - ifman.13
000.0328abc.123456.789100
*/