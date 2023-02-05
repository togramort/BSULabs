#include <iostream>
#include <omp.h>
#include <random>
#include <chrono>

using namespace std;

int find_min_in_row(int* row, int size) {
  int min = row[0];
  for (int i = 1; i < size; i++) {
    if (row[i] < min) {
      min = row[i];
    }
  }
  return min;
}

int find_max(int* mins, int count) {
  int max = mins[0];
  for (int i = 1; i < count; i++) {
    if (mins[i] > max) {
      max = mins[i];
    }
  }
  return max;
}

int main() {
  int x = 10000;
  int x2 = 10000;
  int thread_count = 4;

  srand(time(NULL));
  int** matrix = new int* [x];
  for (int i = 0; i < x; i++) {
    matrix[i] = new int[x2];
    for (int j = 0; j < x2; j++) {
      matrix[i][j] = rand() % x;
    }
  }
  int* mins = new int[x];
  auto start = chrono::high_resolution_clock::now();
  {
    for (int i = 0; i < x; i++) {
      mins[i] = find_min_in_row(matrix[i], x2);
    }
  }
  int max = find_max(mins, x);
  auto end = chrono::high_resolution_clock::now();

  cout << "Max value: " << max << endl;
  cout << "Time of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
}

////////////////////////////////////////////////////////////////////
#include <iostream>
#include <omp.h>
#include <random>
#include <chrono>

using namespace std;

int find_min_in_row(int* row, int size) {
  int min = row[0];
  for (int i = 1; i < size; i++) {
    if (row[i] < min) {
      min = row[i];
    }
  }
  return min;
}

int find_max(int* mins, int count) {
  int max = mins[0];
  for (int i = 1; i < count; i++) {
    if (mins[i] > max) {
      max = mins[i];
    }
  }
  return max;
}

int main() {
  int x = 10000;
  int x2 = 10000;
  int thread_count = 4;

  srand(time(NULL));
  int** matrix = new int* [x];
  for (int i = 0; i < x; i++) {
    matrix[i] = new int[x2];
    for (int j = 0; j < x2; j++) {
      matrix[i][j] = rand() % x;
    }
  }
  int* mins = new int[x];
  auto start = chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(thread_count)
  {
#pragma omp for
    for (int i = 0; i < x; i++) {
      mins[i] = find_min_in_row(matrix[i], x2);
    }
  }
  int max = find_max(mins, x);
  auto end = chrono::high_resolution_clock::now();

  cout << "Max value: " << max << endl;
  cout << "Time of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
}
//////////////////////////////////////////////////
Использование циклов разного уровня вложенности
#include <iostream>
#include <omp.h>
#include <random>
#include <chrono>

using namespace std;

int find_min_in_row(int* row, int size, int thread_count) {
  {
    int min_val = row[0];
#pragma omp parallel for reduction(min:min_val) num_threads(thread_count)
    for (int i = 1; i < size; i++) {
      min_val = std::min(min_val, row[i]);
    }
    return min_val;
  }
}


int find_max(int* mins, int count, int thread_count) {
  int max_val = mins[0];
#pragma omp parallel for reduction(max:max_val) num_threads(thread_count)
  for (int i = 1; i < count; i++) {
    max_val = std::max(max_val, mins[i]);
  }
  return max_val;
}



int main() {
  int x = 10000;
  int x2 = 10000;
  int thread_count = 4;

  srand(time(NULL));
  int** matrix = new int* [x];
  for (int i = 0; i < x; i++) {
    matrix[i] = new int[x2];
    for (int j = 0; j < x2; j++) {
      matrix[i][j] = rand() % x;
    }
  }
  int* mins = new int[x];
  auto start = chrono::high_resolution_clock::now();

  {
    for (int i = 0; i < x; i++) {
      mins[i] = find_min_in_row(matrix[i], x2, thread_count);
    }
  }
  int max = find_max(mins, x, thread_count);
  auto end = chrono::high_resolution_clock::now();

  cout << "Max value: " << max << endl;
  cout << "Time of execution: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
}
