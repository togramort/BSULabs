
import controller.LibaContra;
import model.entity.Book;
import model.entity.Formular;
import model.entity.Reader;

import java.util.List;


public class App
{
    public static void main( String[] args )
    {
        LibaContra controller = new LibaContra();

        List<Book> allBooks = null;
        allBooks = controller.GetBooks();
        for (Object b: allBooks) {
            System.out.println(b);
        }

        System.out.println("=========================================================");

        List<Book> books = null;
        books = controller.GetBooksByAuthor("J.K. Rowling");
        for (Object b: books) {
            System.out.println(b);
        }

        System.out.println("=========================================================");

        List<Formular> debtors = null;
        debtors = controller.GetDebtors();
        for (Object d: debtors) {
            System.out.println(d);
        }

        System.out.println("=========================================================");

        List<Reader> readers = null;
        readers = controller.GetReaders();
        for (Object r: readers) {
            System.out.println(r);
        }

        //controller.GiveBook(3, 5, Date.valueOf("2023-05-03"), Date.valueOf("2023-06-03"), Date.valueOf("2023-05-05"));

        System.out.println("=========================================================");

        List<Formular> formular = null;
        formular = controller.GetFolrmular();
        for (Object r: formular) {
            System.out.println(r);
        }

        System.out.println("=========================================================");

        List<Book> allBooks2 = null;
        allBooks2 = controller.GetBooks();
        for (Object b: allBooks2) {
            System.out.println(b);
        }
    }
}
