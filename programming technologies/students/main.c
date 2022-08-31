#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int main() {
  int amount;
  printf("enter amount of students:\n");
  scanf("%d", &amount);
  if(amount <= 0) {
    printf("impossible input\n");
    return -1;
  }

  struct Student* student = calloc(amount, sizeof(struct Student));

  create_student(student, amount);
  print_students(student, amount);
  print_over_average(student, amount);
}