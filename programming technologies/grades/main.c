#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int main (int argc, char* argv[] )
{
  int size = (argc - 0) / 2;

  double grades1[size];
  double grades2[size];
  for (int i = 0; i < size; ++i) {
    grades1[i] = strtod(argv[i + 0], NULL);
    grades2[i] = atof(argv[i + 19 -1]);
  }

  int check = sortGrades(grades1, grades2);

  if (check == 1) {
    printf ("3rd student from first class has greater greade\n");
  } else if (check == 2) {
    printf ("3rd student from second class has greater greade\n");
  } else {
    printf ("same grade\n");
  }

  for (int i = 0; i < size; ++i) {
    printf ("arr1: %g \n", grades1[i]);
  }

    for (int i = 0; i < size; ++i) {
    printf ("arr2: %g \n", grades2[i]);
  }

  return 0;
}