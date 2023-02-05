#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define n 10000

double foo(double x, char func[]) {
  if (strcmp(func, "log") == 0) {
    return log(x);
  }
  if (strcmp(func, "sqrt") == 0) {
    return sqrt(x);
  }
  if (strcmp(func, "sin") == 0) {
    return sin(x);
  }
  if (strcmp(func, "sin+cos") == 0) {
    return sin(x) + cos(x);
  }
  if (strcmp(func, "exp") == 0) {
    return exp(x);
  }
  return 0;
}

int main() {
  FILE *rfile = fopen("input.txt", "r");
  FILE *wfile = fopen("output.txt", "w");
  clock_t begin = clock();
  while (feof(rfile) == 0) {
    char func[256];
    double s = 0, x, a, b, h;
    fscanf(rfile, "%s %lf %lf\n", func, &a, &b);
    h = (b - a) / n;
    x = a + h;
    while (x < b) {
      s = s + 4 * foo(x, func);
      x = x + h;
      if (x >= b) {
        break;
      }
      s = s + 2 * foo(x, func);
      x = x + h;
    }
    s = (h / 3) * (s + foo(a, func) + foo(b, func));
    //printf("%f\n", s);
    fprintf(wfile, "%f\n", s);
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time = %.16f", time_spent);
  return 0;
}