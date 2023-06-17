package com.example.lab8.entity;

import jakarta.persistence.*;

@Entity
@Table(name = Book.bookTable)
//@NamedQuery(name="getBooksByAuthor", query="SELECT b FROM Book b WHERE b.author = :author")
public class Book {

    public static final String bookTable = "books";
    private static final String bookId = "id_books";
    private static final String bookName = "name";
    private static final String bookAuthor = "author";
    private static final String bookNumberOfInstances = "number_of_instances";

    @Id
    @GeneratedValue
    @Column(name = bookId)
    private int id;

    @Column(name = bookName)
    private String name;

    @Column(name = bookAuthor)
    private String author;

    @Column(name = bookNumberOfInstances)
    private int number_of_instances;

    public Book(){}

    public Book(int id_books, String name, String author, int number_of_instances) {
        this.id = id_books;
        this.name = name;
        this.author = author;
        this.number_of_instances = number_of_instances;
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

    public int getNumber_of_instances() {
        return number_of_instances;
    }

    public void setId(int id) { this.id = id; }

    public void setName(String name) { this.name = name; }

    public void setAuthor(String author) { this.author = author; }

    public void setNumber_of_instances(int number_of_instances) { this.number_of_instances = number_of_instances; }

    @Override
    public String toString() {
        return "Book{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", number_of_instances=" + number_of_instances +
                '}';
    }
}