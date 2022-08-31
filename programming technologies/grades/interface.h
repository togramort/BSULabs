//
// created by margot golubovich
//

#ifndef INTERFACE_H
#define INTERFACE_H

//function sortGrades is used in client file (main.c)
//implementation is in server file (interface.h)
//grades1 and grades2 are arrays
//function sorts this two arrays
//return: 1, 2 or 3 using function compareGrades in server file

int sortGrades (double *grades1, double *grades2);

#endif /*INTERFACE_H*/