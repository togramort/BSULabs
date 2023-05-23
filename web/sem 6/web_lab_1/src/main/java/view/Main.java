package view;

import controller.LibaContra;
import model.DaoException;

import java.sql.Date;
import java.util.List;

public class Main
{
    public static void main( String[] args )
    {
        LibaContra controller = null;
        try {
            controller = new LibaContra();
        } catch (DaoException e) {
            System.out.println(e.getMessage());
            return;
        }

        List allBooks = null;
        allBooks = controller.GetBooks();
        for (Object b: allBooks) {
            System.out.println(b);
        }

        System.out.println("=========================================================");

        List books = null;
        books = controller.GetBooksByAuthor("J.K. Rowling");
        for (Object b: books) {
            System.out.println(b);
        }

        System.out.println("=========================================================");

        List debtors = null;
        debtors = controller.GetDebtors();
        for (Object d: debtors) {
            System.out.println(d);
        }

        System.out.println("=========================================================");

        List readers = null;
        readers = controller.GetReaders();
        for (Object r: readers) {
            System.out.println(r);
        }

        controller.GiveBook(3, 5, Date.valueOf("2023-05-03"), Date.valueOf("2023-06-03"), Date.valueOf("2023-05-05"));

        System.out.println("=========================================================");

        List formular = null;
        formular = controller.GetFolrmular();
        for (Object r: formular) {
            System.out.println(r);
        }

        System.out.println("=========================================================");

        List allBooks2 = null;
        allBooks2 = controller.GetBooks();
        for (Object b: allBooks2) {
            System.out.println(b);
        }
    }
}
