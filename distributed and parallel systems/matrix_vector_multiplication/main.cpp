#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <thread>
#include <mutex>

std::vector<std::vector<int>> generate_matrix(int rows, int columns) {
  std::mt19937 rng(time(nullptr));
  std::uniform_int_distribution<int> dist(0,9);
  std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix[i][j] = dist(rng);
    }
  }

  std::cout << "\n";

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << "\n";

  }

  return matrix;
}

std::vector<int> generate_vector(int size) {
  std::mt19937 rng(time(nullptr));
  std::uniform_int_distribution<int> dist(0,9);
  std::vector<int> vector(size);
  for (int i = 0; i < size; ++i) {
    vector[i] = dist(rng);
  }
  std::cout << "\n";

  for (int i : vector) {
    std::cout << i << "\t";
  }
  return vector;
}

/*void multiplication_1(std::vector<std::vector<int>>& matrix, std::vector<int>& vector, std::vector<int>& result, int start_row, int task_size) {
  double temp;
  for (int i = start_row; i < start_row + task_size; ++i){
    temp = 0;
    for (int j = 0; j < vector.size(); ++j){
      temp += matrix[i][j] * vector[j];
    }
    result[i] = temp;
  }
}*/
void thread_matrix_multiplication(std::vector<std::vector<int>>& matrix,
                                  std::vector<int>& vector,
                                  std::vector<int>& multiplication,
                                  int& current_row,
                                  std::mutex& mutex) {
  double result;
  int index;
  std::pair<int, std::vector<double>> request;
  while (true) {
    {
      std::lock_guard<std::mutex> guard(mutex);
      if (current_row < 0){
        break;
      }
      index = current_row;
      --current_row;
    }

    result = 0;
    for (int i = 0; i < vector.size(); ++i) {
      result += matrix[index][i] * vector[i];
    }
    multiplication[index] = result;
  }
}

int main() {
  std::vector<std::vector<int>> matrix;
  std::vector<int> vector;
  int number_of_threads = 5;
  matrix = generate_matrix(3,2);
  vector = generate_vector(2);
  std::vector<int> multiplication(3, 0);

/*  int task_size = matrix.size() / number_of_threads,
  remainder = matrix.size() % number_of_threads,
  current_task;*/


  /*std::vector<std::thread> threads(0);
  auto startTime = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 3;){
    current_task = task_size;
    if (remainder > 0){
      --remainder;
      current_task = task_size + 1;
    }
    threads.emplace_back(multiplication_1, std::ref(matrix), std::ref(vector), std::ref(multiplication), i, current_task);
    i += current_task;
  }
  for (auto & thread : threads){
    thread.join();
  }
  auto endTime = std::chrono::high_resolution_clock::now(); // end

  std::cout << "Result time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
*/

  std::vector<std::thread> threads(0);
  threads.reserve(number_of_threads);
  int current_row = 3 - 1;
  std::mutex mutex;

  auto startTime = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < number_of_threads; ++i) {
    threads.emplace_back(thread_matrix_multiplication,
                         std::ref(matrix),
                         std::ref(vector),
                         std::ref(multiplication),
                         std::ref(current_row),
                         std::ref(mutex));
  }


  for (int i = 0; i < number_of_threads; ++i) {
    if (threads[i].joinable()){
      threads[i].join();
    }
  }
  auto endTime = std::chrono::high_resolution_clock::now(); // end

  std::cout << "Result time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";

  return 0;
}
