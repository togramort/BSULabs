#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iterator>

auto print = [](auto const rem, auto const &v) {
  std::cout << rem;
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
};

class RandomGenerator {
 private:
  std::random_device device_;
  std::mt19937 rng_;
  std::uniform_int_distribution<int> dist_;

 public:
  RandomGenerator(int min, int max) {
    rng_ = std::mt19937(device_());
    dist_ = std::uniform_int_distribution<int>(min, max);
  }

  int rand() {
    return dist_(rng_);
  }
};

std::vector<int> generate_vector(int size, RandomGenerator &generator) {
  std::vector<int> result(size, 0);
  for (int i = 0; i < size; ++i) {
    result[i] = generator.rand();
  }

  return result;
}

int main() {
  const int SIZE = 10000000;

  const int first_generator_min = 1;
  const int first_generator_max = 100000000;
  RandomGenerator first_generator(first_generator_min, first_generator_max);

  const int second_generator_min = first_generator_max + 1;
  const int second_generator_max = second_generator_min + first_generator_max - first_generator_min;
  RandomGenerator second_generator(second_generator_min, second_generator_max);

  std::vector<int> vec1 = generate_vector(SIZE, first_generator);
  std::vector<int> vec2 = generate_vector(SIZE, first_generator);

  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());

  auto begint = std::chrono::high_resolution_clock::now();

  std::vector<int> dst(SIZE * 2);
  std::merge(/*std::execution::par,*/ vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dst.begin());
  //3146
  //1024

  //122
  //55
  auto endt = std::chrono::high_resolution_clock::now();

  long long int time = std::chrono::duration_cast<std::chrono::milliseconds>(endt - begint).count();

  std::cout << "\nResult time: " << time << " ms" << "\n";

  return 0;
}
