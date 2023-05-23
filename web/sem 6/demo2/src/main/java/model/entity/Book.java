package model.entity;

import javax.persistence.*;

import static model.entity.Book.bookTable;

@Entity
@Table(name = bookTable)
@NamedQuery(name="getBooksByAuthor", query="SELECT b FROM Book b WHERE b.author = :author")
public class Book {

    public static final String bookTable = "books";
    private static final String bookId = "id_books";
    private static final String bookName = "name";
    private static final String bookAuthor = "author";
    private static final String bookNumberOfInstance = "number_of_instances";

    @Id
    @GeneratedValue
    @Column(name = bookId)
    private int id;

    @Column(name = bookName)
    private String name;

    @Column(name = bookAuthor)
    private String author;

    @Column(name = bookNumberOfInstance)
    private int number_of_instance;

    public Book(){}

    public Book(int id_books, String name, String author, int number_of_instance) {
        this.id = id_books;
        this.name = name;
        this.author = author;
        this.number_of_instance = number_of_instance;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getAuthor() {
        return author;
    }

    public int getNumber_of_instance() {
        return number_of_instance;
    }

    public void setId(int id) { this.id = id; }

    public void setName(String name) { this.name = name; }

    public void setAuthor(String author) { this.author = author; }

    public void setNumber_of_instance(int number_of_instance) { this.number_of_instance = number_of_instance; }

    @Override
    public String toString() {
        return "Book{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", number_of_instance=" + number_of_instance +
                '}';
    }
}