import { ChangeDetectorRef, Component, Input } from '@angular/core';
import { Books } from '../mock-book-list';
import { Book } from '../book.model';
import { BooksService } from '../services/books.service';
import { ActivatedRoute, Router } from '@angular/router';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-book-form',
  templateUrl: './book-form.component.html',
  styleUrls: ['./book-form.component.css']
})
export class BookFormComponent {
  @Input() name: string | undefined;
  @Input() author: string | undefined;
  @Input() instances: number | undefined;
  books!: Observable<Book[]>;

  constructor(private bookService: BooksService) {
  }
  
  onSubmit(contactForm: { value: any; }) {
    const index = Books.at(-1)?.id;
    const newBook: Book = {
      id: index! + 1,
      name: contactForm.value.name,
      author: contactForm.value.author,
      number_of_instances: contactForm.value.instances
    };

    this.bookService.addBook(newBook).subscribe((book: Book) => {
        console.log('Book added successfully', book);
        this.books = this.bookService.getBooks();
        console.log('tring to show', this.books);
    });

    // Books.push({
    //   id: index! + 1,
    //   name: contactForm.value.name,
    //   author: contactForm.value.author,
    //   instances: contactForm.value.instances
    // })
  }
}