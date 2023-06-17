import { Component } from '@angular/core';
import { Book } from '../book.model';
import { Router } from '@angular/router';
import { BooksService } from '../services/books.service';
import { Observable, of } from 'rxjs';

@Component({
  selector: 'app-book-list',
  templateUrl: './book-list.component.html',
  styleUrls: ['./book-list.component.css']
})
export class BookListComponent {
  books: Observable<Book[]>;

  constructor(private bookService: BooksService, public router: Router) {
    this.books = this.bookService.getBooks();
  }

  // constructor(private bookService: BooksService, public router: Router) {
  //   this.bookService.getBooks().subscribe(books => {
  //     this.books = books;
  //   });
  // }

  onSelect(book: Book): void {
    const id = book.id;
    this.router.navigate(['/books/', id]);
  }
}
