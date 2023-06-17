import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { BookCenterComponent } from './book-center/book-center.component';
import { BookListComponent } from './book-list/book-list.component';
import { BookDetailsComponent } from './book-details/book-details.component';
import { BooksRoutingModule } from './books-routing.module';
import { BookFormComponent } from './book-form/book-form.component';
import { FormsModule } from '@angular/forms';



@NgModule({
  declarations: [
    BookCenterComponent,
    BookListComponent,
    BookDetailsComponent,
    BookFormComponent
  ],
  imports: [
    CommonModule,
    BooksRoutingModule,
    FormsModule
  ]
})
export class BooksModule { }
