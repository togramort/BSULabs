package model.entity;

public class Book {
    private int id;
    private String name;
    private String author;
    private int number_of_instance;

    public Book(){}

    public Book(int id, String name, String author, int number_of_instance) {
        this.id = id;
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