#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <random>

const int SIZE = 10000000;
const int THREAD_COUNT = 4;

template<typename RAIter>
int parallel_max(RAIter beg, RAIter end) {
  typename RAIter::difference_type len = end - beg;
  if (len < SIZE / THREAD_COUNT)
    return *(std::max_element(beg, end));

  RAIter mid = beg + len / 2;
  auto handle = std::async(std::launch::async,
                           parallel_max<RAIter>, mid, end);
  int max = parallel_max(beg, mid);
  return std::max(max, handle.get());
}

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

template<typename Iterator>

struct max_block {
  void operator()(Iterator first, Iterator last, int &result) {
    result = *(std::max_element(first, last));
  }
};

template<typename Iterator>
int parallel_max_uiliams(Iterator first, Iterator last) {
  unsigned long const length = std::distance(first, last);
  if (!length)
    return -1;
  unsigned long const num_threads = THREAD_COUNT;
  unsigned long const block_size = length / num_threads;
  std::vector<int> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);
  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(
        max_block<Iterator>(),
        block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  max_block<Iterator>()(
      block_start, last, results[num_threads - 1]);

  for (auto &entry: threads)
    entry.join();
  return *(std::max_element(results.begin(), results.end()));
}

int main() {
  const int generator_max = 100000000;
  RandomGenerator first_generator(-generator_max, generator_max);

  std::vector<int> v = generate_vector(SIZE, first_generator);
  auto startTime = std::chrono::high_resolution_clock::now(); // start;

  std::cout << "The max by Divide and Conquer is " << parallel_max(v.begin(), v.end()) << '\n';
  auto endTime = std::chrono::high_resolution_clock::now(); // end;

  std::cout << "Time by Divide and Conquer: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
            << " ms\n";

  startTime = std::chrono::high_resolution_clock::now();

  std::cout << "The max is " << *(std::max_element(v.begin(), v.end())) << '\n';
  endTime = std::chrono::high_resolution_clock::now(); // end;

  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
            << " ms\n";

  startTime = std::chrono::high_resolution_clock::now();

  std::cout << "The max by Uiliams is " << parallel_max_uiliams(v.begin(), v.end()) << '\n';
  endTime = std::chrono::high_resolution_clock::now(); // end;

  std::cout << "Time by Uiliams is: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
            << " ms\n";
}
