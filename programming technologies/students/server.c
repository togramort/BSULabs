#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void create_student(struct Student *student, int amount) {
  for (int i = 0; i < amount; ++i) {
    printf("\nenter surname for the %d student:\n", i + 1);
    student[i].surname = (char *) calloc(20, sizeof(char));
    scanf("%s", student[i].surname);
    printf("\nenter student's course:\n");
    scanf("%d", &student[i].course);
    printf("\nenter five student's marks:\n");
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &student[i].ses[j]);
    }
    printf("\n");
  }
}

/*int cst_cmp(const void *one, const void *two) {
  char a = *((char*)one);
  char b = *((char*)two);
  return strcmp(&a, &b);
}

int cmp(const void* a, const void* b) {
  if (*(char *) a > *(char *)b) {
    return 1;
  } else {
    return 0;
  }
}*/

// Defining comparator function as per the requirement
static int myCompare(const void* a, const void* b) {
  // setting up rules for comparison
  return strcmp(*(const char**)a, *(const char**)b);
}

// Function to sort the array
void sort(const char* arr[], int n) {
  // calling qsort function to sort the array
  // with the help of Comparator
  qsort(arr, n, sizeof(const char*), myCompare);
}

void print_students(struct Student *student, int amount) {
  char **names = (char **) calloc(amount, sizeof(char*));
  for (int i = 0; i < amount; ++i) {
    names[i] = (char *) calloc(20, sizeof(char));
    names[i] = student[i].surname;
  }
  printf("names before sorting\n");
  for (int i = 0; i < amount; ++i) {
    printf("%s", names[i]);
    printf("\n");
  }

  sort((const char **) names, amount);

  //qsort(*names, amount, sizeof(char*), (int (*)(const void*, const void*))strcmp);
  printf("students in alphabetical order:\n");

  for (int i = 0; i < amount; ++i) {
    printf("%s", names[i]);
    printf("\n");
  }
}

double count_average(struct Student *student, int amount) {
  double avg = 0;
  for (int i = 0; i < amount; ++i) {
    for (int j = 0; j < 5; ++j) {
      avg += student[i].ses[j];
    }
  }
  avg /= 5 * amount;
  return avg;
}

void print_over_average(struct Student *student, int amount) {
  int check = 0;
  double avg = count_average(student, amount);
  printf("student(s) who have average mark above common average: %f\n", avg);
  for (int i = 0; i < amount; ++i) {
    double st_avg = 0;
    for (int j = 0; j < 5; ++j) {
      st_avg += student[i].ses[j];
    }
    st_avg /= 5;
    if (st_avg > avg) {
      printf("%s", student[i].surname);
      printf("\n");
      ++check;
    }
  }
  if (check == 0) {
    printf("oopsie there is no such student(s)\n");
  }
}