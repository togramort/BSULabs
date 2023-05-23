package model.entity;

import java.sql.Date;

public class Reader {
    private int id;
    private String name;
    private Date birth_date;

    public Reader() {}

    public Reader(int id, String name, Date birth_date) {
        this.id = id;
        this.name = name;
        this.birth_date = birth_date;
    }

    public int getId() { return id; }

    public String getName() { return name; }

    public Date getBirth_date() { return birth_date; }

    public void setId(int id) { this.id = id; }

    public void setName(String name) { this.name = name; }

    public void setBirth_date(Date birth_date) { this.birth_date = birth_date; }

    @Override
    public String toString() {

        return "Reader{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", birth_date='" + birth_date +
                '}';
    }
}