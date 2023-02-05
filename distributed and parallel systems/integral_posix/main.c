#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define n 10000
#define buffer_size 33

bool done = false;

pthread_mutex_t mutex;
sem_t semFull;
sem_t semEmpty;

typedef struct func_info {
  char func[256];
  double a, b;
} func_info;

func_info overall_buffer[buffer_size];
int count = 0;

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

void *producer_f(void* param) {
  FILE *rfile = fopen("input.txt", "r");
  while (feof(rfile) == 0) {
    func_info input;
    fscanf(rfile, "%s %lf %lf\n", input.func, &input.a, &input.b);

    sem_wait(&semEmpty);
    pthread_mutex_lock(&mutex);
    overall_buffer[count] = input;
    count++;
    pthread_mutex_unlock(&mutex);
    sem_post(&semFull);
  }
  done = true;
}

void *consumer_f(void* param) {
  FILE *wfile = fopen("output.txt", "w");
  func_info output;
  while (1) {
    sem_wait(&semFull);
    pthread_mutex_lock(&mutex);
    output = overall_buffer[count - 1];
    count--;
    pthread_mutex_unlock(&mutex);
    sem_post(&semEmpty);

    double s = 0, h, x;
    h = (output.b - output.a) / n;
    x = output.a + h;
    while (x < output.b) {
      s = s + 4 * foo(x, output.func);
      x = x + h;
      if (x >= output.b) {
        break;
      }
      s = s + 2 * foo(x, output.func);
      x = x + h;
    }
    s = (h / 3) * (s + foo(output.a, output.func) + foo(output.b, output.func));
    //printf("%f\n", s);
    fprintf(wfile, "%f\n", s);

    if (done && count == 0) {
      break;
    }
  }
}

int main() {
  clock_t begin = clock();

  pthread_t producer, consumer;

  pthread_mutex_init(&mutex, NULL);
  sem_init(&semEmpty, 0, buffer_size);
  sem_init(&semFull, 0, 0);

  pthread_create(&producer, NULL, producer_f, NULL);
  pthread_create(&consumer, NULL, consumer_f, NULL);
  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);

  sem_destroy(&semEmpty);
  sem_destroy(&semFull);
  pthread_mutex_destroy(&mutex);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time = %.16f", time_spent);
  return 0;
}