package controller;

import model.dao.DAOReader;
import model.dao.DAOBook;
import model.dao.DAOFormular;
import model.entity.Formular;
import model.DaoException;

import java.sql.Date;
import java.util.List;

public class LibaContra {
    private final DAOReader readerDao;
    private final DAOBook bookDao;
    private final DAOFormular formularDao;


    public LibaContra() throws DaoException {
        readerDao = new DAOReader();
        bookDao = new DAOBook();
        formularDao = new DAOFormular();
    }

    public List GetBooksByAuthor(String author){
        try {
            return bookDao.getBooks(author);
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }

    public List GetBooks(){
        try {
            return bookDao.getAll();
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }

    public List GetDebtors() {
        try {
            return formularDao.getDebtors();
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }

    public List GetReaders() {
        try {
            return readerDao.getAll();
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }

    public void GiveBook(int book_id, int reader_id, Date start_date, Date end_date, Date return_date) {
        try {
            formularDao.save(new Formular(book_id, reader_id, start_date, end_date, return_date));
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
        try {
            bookDao.removeItemBook(book_id);
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }

    public List GetFolrmular() {
        try {
            return formularDao.getAll();
        } catch (DaoException e) {
            throw new RuntimeException(e);
        }
    }
}
