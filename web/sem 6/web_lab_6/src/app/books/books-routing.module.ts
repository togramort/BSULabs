import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router';
import { BookCenterComponent } from './book-center/book-center.component';
import { BookListComponent } from './book-list/book-list.component';
import { BookDetailsComponent } from './book-details/book-details.component';
import { BookFormComponent } from './book-form/book-form.component';

const routes: Routes = [
  {
      path: 'books', component: BookCenterComponent, children: [
          { path: '', component: BookListComponent },
          { path: ':id', component: BookDetailsComponent },
          { path: '', component: BookFormComponent }
      ]
  }
]

@NgModule({
  declarations: [],
  imports: [
    CommonModule,
    RouterModule.forChild(routes)
  ],
  exports: [RouterModule]
})
export class BooksRoutingModule { }
