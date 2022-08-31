//
// created by margot golubovich
//

//compareGrades compares numbers on third position in two arrays
//return: 1, 2 or 3
//compare is comparator for implementation of sorting
//sortGrades sorts two arrays
//return: result of compareGrades

#include <stdlib.h>
#include "interface.h"

int compareGrades (double grades1, double grades2) {
  if (grades1 > grades2) {
    return 1;
  } else if (grades1 < grades2) {
  return 2;
  } else if (grades1 == grades2) {
  return 3;
  }
}

static int compare (const void * a, const void * b) {
  if (*(double*)a > *(double*)b) {
    return 1;
    } else if (*(double*)a < *(double*)b) {
    return -1;
    } else {
    return 0;
    }
}

int sortGrades (double *grades1, double *grades2) {
  int size1 = sizeof(&grades1) / sizeof(double);
  qsort(grades1, size1, sizeof(double), compare);

  int size2 = sizeof(*grades2) / sizeof(double);
  qsort(grades2, size2, sizeof(double), compare);

  return compareGrades (grades1[2], grades2[2]);
}