#include <cmath>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

class RandomGenerator {

 private:
  std::random_device device_;
  std::mt19937 rng_;
  std::uniform_real_distribution<double> dist_;

 public:
  RandomGenerator(double min, double max) {
    rng_ = std::mt19937(device_());
    dist_ = std::uniform_real_distribution<double>(min, max);
  }
  double rand() {
    return dist_(rng_);
  }
};

class Timer {
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
 public:
  void start() {
    begin_ = std::chrono::high_resolution_clock::now();
  }
  long long int get_time_in_milliseconds() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - begin_).count();
  }
};

double polynomial_func(double x) {
  return std::pow(x, 3) + 4 * std::pow(x, 2) - 4 * x + 7;
}

double sin_cos_func(double x) {
  return std::sin(x) * std::cos(x);
}

double exp_x(double x) {
  return exp(x);
}

class IntegralCountPart {
 public:
  void operator()(double a, double b, double(*func)(double), int partitions, double &result) const {
    double step = (b - a) / partitions;
    for (int i = 0; i < partitions; ++i) {
      result += step * func(a + i * step);
    }
  }
};

int main() {
  int p = 4;
  int n = 1000000000;
  double integral = 0.;
  double thread_step = 1. / p;
  IntegralCountPart count_part;
  Timer timer;
  timer.start();
  std::vector<std::thread> threads;
  threads.reserve(p);
  std::vector<double> integral_parts(p);

  for (int i = 0; i < p; i++) {
    threads.emplace_back(count_part, thread_step * i, thread_step * (i + 1),
                         exp_x, (n / p) + 1, std::ref(integral_parts[i]));
  }

  for_each(threads.begin(), threads.end(), [](std::thread &t) { t.join(); });
  integral = std::accumulate(integral_parts.begin(), integral_parts.end(), 0.);
  auto time_result = timer.get_time_in_milliseconds();
  std::cout << "Result time: " << (time_result * 1.0) / 1000 << " ms\n";
  return 0;
}

std::vector<std::vector<double>> generate_matrix(int rows, int columns, RandomGenerator &generator) {
  std::vector<std::vector<double>> result(rows, std::vector<double>(columns, 0));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      result[i][j] = generator.rand();
    }
  }

  return result;
}

std::vector<double> generate_vector(int size, RandomGenerator &generator) {
  std::vector<double> result(size, 0);
  for (int i = 0; i < size; ++i) {
    result[i] = generator.rand();
  }

  return result;
}

void print_vector(std::vector<double> &vector, const std::string &message = "") {
  if (!message.empty()) {
    std::cout << message << "\n";
  }
  for (double i: vector) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

void print_matrix(std::vector<std::vector<double>> &matrix, const std::string &message = "") {
  if (!message.empty()) {
    std::cout << message << "\n";
  }
  for (auto &i: matrix) {
    print_vector(i);
  }
}

struct MatrixMultiplicationPart {
 public:
  void operator()(std::vector<std::vector<double>> &matrix,
                  std::vector<double> &vector,
                  std::vector<double> &result,
                  int start_row,
                  int task_size) const {
    double temp;
    for (int i = start_row; i < start_row + task_size; ++i) {
      temp = 0;
      for (int j = 0; j < vector.size(); ++j) {
        temp += matrix[i][j] * vector[j];
      }
      result[i] = temp;
    }
  }
};

/*
int main() {
  const double generator_max = 100;
  const double generator_min = -100;

  RandomGenerator generator(generator_min, generator_max);
  Timer timer;

  int rows, columns;
  std::cout << "Enter matrix number of rows:\n";
  std::cin >> rows;
  std::cout << "Enter matrix number of columns:\n";
  std::cin >> columns;

  if (columns <= 0 || rows <= 0) {
    std::cerr << "Number of rows and columns cannot be negative or equal to 0\n";
    return 1;
  }

  int amount_of_threads = 0;
  std::cout << "Enter amount of threads\n";
  std::cin >> amount_of_threads;

  int task_size = rows / amount_of_threads, remainder = rows % amount_of_threads;
  int current_task;

  std::vector<std::vector<double>> matrix = generate_matrix(rows, columns, generator);
  std::vector<double> vector = generate_vector(columns, generator);
  std::vector<double> multiplication(rows, 0);
  timer.start();
  std::vector<std::thread> threads(0);
  MatrixMultiplicationPart part_task;
  for (int i = 0; i < rows;) {
    current_task = task_size;
    if (remainder > 0) {
      --remainder;
      current_task = task_size + 1;
    }
    threads.emplace_back(MatrixMultiplicationPart(),
                         std::ref(matrix),
                         std::ref(vector),
                         std::ref(multiplication),
                         i,
                         current_task);
    i += current_task;
  }

  std::for_each(threads.begin(), threads.end(), [](std::thread &t) { t.join(); });

  auto time = timer.get_time_in_milliseconds();

  std::cout << "Result time: " << (1.0 * time) / 1000 << " ms" << "\n";

  return 0;
}*/
