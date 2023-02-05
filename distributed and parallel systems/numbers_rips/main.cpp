#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <cmath>

void find_prime_numbers(int a, int b, std::vector<bool>& numbers)
{
  std::vector<int> prime_numbers;
  for (int i = a; i <= b; ++i)
  {
    bool add = true;
    for (int j = 2; j <= sqrt(i); ++j)
    {
      if (!(i % j))
      {
        add = false;
        break;
      }
    }

    if (add)
    {
      numbers[i] = true;
      prime_numbers.push_back(i);
    }
  }
}

void print_prime_numbers(const std::vector<bool>& numbers)
{
  for (size_t i = 2; i < numbers.size(); ++i)
  {
    if (numbers[i])
      std::cout << i << std::endl;
  }
}


int main()
{
  int a = 2,
      b = 100000,
      p = 1;

  int default_size = (b - a + 2) / p,
      remainder = (b - a + 2) % p;

  std::vector<bool> numbers(b + 1, false);
  std::vector<std::future<void>> futures;

  int temp_a = a;
  auto startTime = std::chrono::high_resolution_clock::now(); // start;
  for (size_t i = 1; i <= p; ++i)
  {
    int temp_b = temp_a + default_size;
    if (remainder > 0)
    {
      remainder--;
      temp_b++;
    }

    futures.push_back(std::async(find_prime_numbers,
                                 temp_a, temp_b , std::ref(numbers)));
  }

  for (size_t i = 0; i < futures.size(); ++i)
  {
    futures[i].get();
  }
  auto endTime = std::chrono::high_resolution_clock::now(); // end;

  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
  //print_prime_numbers(numbers);
}