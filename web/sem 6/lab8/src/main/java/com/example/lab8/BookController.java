package com.example.lab8;

import com.example.lab8.entity.Book;
import com.example.lab8.entity.BookRepository;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@CrossOrigin(origins = "http://localhost:4200")
public class BookController {
    //private List<Book> books = new ArrayList<>();
    private final BookRepository bookRepository;

    public BookController(BookRepository bookRepository) {
        this.bookRepository = bookRepository;
    }

    @GetMapping("/books")
    public List<Book> getBooks() {
        return (List<Book>)bookRepository.findAll();
    }

    @GetMapping("/books/{id}")
    public Optional<Book> getBook(@PathVariable int id) {
        return bookRepository.findById(id);
    }

    @PostMapping("/books")
    public Book addBook(@RequestBody Book newBook) {
        return bookRepository.save(newBook);
    }

    @DeleteMapping("/books/{id}")
    public void deleteBook(@PathVariable int id) {
        bookRepository.deleteById(id);
    }
}