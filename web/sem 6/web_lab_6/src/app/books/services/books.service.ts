import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Book } from '../book.model';
import { Books } from '../mock-book-list';
import { Observable, of } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class BooksService {

  // constructor() { }
  
  // getBooks(): Observable<Book[]> {
  //   return of(Books);
  // }

  // getBook(id: number): Observable<Book | undefined> {
  //   const book = Books.find(b => b.id === id);
  //   return of(book);
  // }

  // updateBook(book: Book): Observable<Book | undefined> {
  //   const index = Books.findIndex(b => b.id === book.id);
  //   if (index === -1) {
  //     return of(undefined);
  //   }
  //   Books[index] = book;
  //   return of(book);
  // }

  private bookUrl: string;

  constructor(private http: HttpClient) {
    this.bookUrl = 'http://localhost:8080/books';
  }

  getBooks(): Observable<Book[]> {
    return this.http.get<Book[]>(this.bookUrl);  
  }

  getBook(id: number): Observable<Book> {
    const url = `${this.bookUrl}/${id}`;
    return this.http.get<Book>(url);
  }

  addBook(book: Book): Observable<Book> {
    return this.http.post<Book>(this.bookUrl, book);
  }

  deleteBook(id: number): Observable<void> {
    const url = `${this.bookUrl}/${id}`;
    return this.http.delete<void>(url);
  }
}