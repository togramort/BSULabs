package controller;

import model.dao.DAOBook;
import model.dao.DAOFormular;
import model.dao.DAOReader;
import model.entity.Book;
import model.entity.Formular;
import model.entity.Reader;

import java.sql.Date;
import java.util.List;

public class LibaContra {
    private final DAOReader readerDao;
    private final DAOBook bookDao;
    private final DAOFormular formularDao;


    public LibaContra() {
        readerDao = new DAOReader();
        bookDao = new DAOBook();
        formularDao = new DAOFormular();
    }

    public List<Book> GetBooksByAuthor(String author){
        return bookDao.getBooks(author);
    }

    public List<Book> GetBooks(){
        return bookDao.getAll();
    }

    public List<Formular> GetDebtors() {
        return formularDao.getDebtors();
    }

    public List<Reader> GetReaders() {
        return readerDao.getAll();
    }

    public void GiveBook(int book_id, int reader_id, Date start_date, Date end_date, Date return_date) {
        formularDao.save(new Formular(book_id, reader_id, start_date, end_date, return_date));
        bookDao.removeItemBook(book_id);
    }

    public List<Formular> GetFolrmular() {
        return formularDao.getAll();
    }
}
