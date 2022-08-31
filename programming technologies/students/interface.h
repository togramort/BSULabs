#ifndef FOR_TP_LAB3_TASK3__INTERFACE_H_
#define FOR_TP_LAB3_TASK3__INTERFACE_H_

struct Student {
  char* surname;
  int course;
  int ses[5];
};
void create_student (struct Student *student, int amount);
void print_students(struct Student *student, int amount);
void print_over_average(struct Student* student, int amount);


#endif //FOR_TP_LAB3_TASK3__INTERFACE_H_
