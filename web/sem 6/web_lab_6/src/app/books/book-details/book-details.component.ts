import { Component } from '@angular/core';
import { Book } from '../book.model';
import { ActivatedRoute, Router } from '@angular/router';
import { BooksService } from '../services/books.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-book-details',
  templateUrl: './book-details.component.html',
  styleUrls: ['./book-details.component.css']
})
export class BookDetailsComponent {
  book!: Observable<Book>;

    constructor(
      private route: ActivatedRoute, 
      private bookService: BooksService, 
      public router: Router
    ) {}

    ngOnInit(): void {
      const id = +this.route.snapshot.paramMap.get('id')!;
      this.book = this.bookService.getBook(id);
    }

    // ngOnInit(): void {
    //   const id = +this.route.snapshot.paramMap.get('id')!;
    //   this.bookService.getBook(id).subscribe(book => {
    //     this.book = book;
    //     }
    //   );
    // }

    goBack(): void {
      this.router.navigate(['/books/']);
    }

    delete(): void {
      const id = +this.route.snapshot.paramMap.get('id')!;
      // this.bookService.deleteBook(id);
      // this.goBack();
      this.bookService.deleteBook(id).subscribe(() => {
        this.goBack();
      });
    }
}