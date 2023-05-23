package model.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.sql.Date;

import static model.entity.Formular.formularTable;

@Entity
@Table(name = formularTable)
public class Formular implements Serializable {

    public static final String formularTable = "formular";

    private static final String formularId = "id_formular";

    private static final String book_id = "books_id_books";

    private static final String reader_id = "reader_id_reader";

    private static final String start_date = "start_date";

    private static final String end_date = "end_date";

    private static final String return_date = "return_date";

    @Id
    @GeneratedValue
    @Column(name = formularId)
    private int id;

    @Column(name = reader_id)
    private int reader_id_reader;

    @Column(name = book_id)
    private int books_id_book;

    @Column(name = start_date)
    private Date start_day;

    @Column(name = end_date)
    private Date end_day;

    @Column(name = return_date)
    private Date return_day;


    public Formular(){}

    public Formular(int id){
        this.id = id;
    }

    public Formular(int book_id, int reader_id, Date start_day, Date end_day, Date return_day){
        this.books_id_book = book_id;
        this.reader_id_reader = reader_id;
        this.start_day = start_day;
        this.end_day = end_day;
        this.return_day = return_day;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public Date getStart_day() { return start_day; }

    public Date getEnd_day() { return end_day; }

    public Date getReturn_day() { return return_day; }

    public int getReader() {
        return reader_id_reader;
    }

    public void setReader(int reader) {
        this.reader_id_reader = reader;
    }

    public int getBook() {
        return books_id_book;
    }

    public void setBook(int book) {
        this.books_id_book = book;
    }

    public void setStart_day(Date start_day) { this.start_day = start_day; }

    public void setEnd_day(Date end_day) { this.end_day = end_day; }

    public void setReturn_day(Date return_day) { this.return_day = return_day; }

    @Override
    public String toString() {

        return "Formular{" +
                "book_id=" + books_id_book +
                ", reader_id=" + reader_id_reader +
                ", start_day='" + start_day +
                ", end_day='" + end_day +
                ", return_day='" + return_day +
                '}';
    }
}