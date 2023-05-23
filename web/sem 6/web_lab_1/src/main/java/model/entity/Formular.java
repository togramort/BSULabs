package model.entity;

import java.sql.Date;

public class Formular {
    private int id;
    private int reader_id;
    private int book_id;
    private Date start_day;
    private Date end_day;
    private Date return_day;

    public Formular(){}

    public Formular(int book_id, int reader_id, Date start_day, Date end_day, Date return_day){
        this.book_id = book_id;
        this.reader_id = reader_id;
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
        return reader_id;
    }

    public int getBook() {
        return book_id;
    }

    public void setStart_day(Date start_day) { this.start_day = start_day; }

    public void setEnd_day(Date end_day) { this.end_day = end_day; }

    public void setReturn_day(Date return_day) { this.return_day = return_day; }

    public void setReader(int reader_id) {
        this.reader_id = reader_id;
    }

    public void setBook(int book_id) {
        this.book_id = book_id;
    }

    @Override
    public String toString() {

        return "Formular{" +
                "book_id=" + book_id +
                ", reader_id=" + reader_id +
                ", start_day='" + start_day +
                ", end_day='" + end_day +
                ", return_day='" + return_day +
                '}';
    }
}