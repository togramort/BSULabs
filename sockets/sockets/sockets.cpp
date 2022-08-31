#include <iostream>

int main() {
  int N;
  std::cin >> N;
  std::cout << "\n";

  int *arr = new int[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> arr[i];
  }
  std::cout << "\n";

  long long sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += arr[i];
  }
  sum -= (N - 1);
  std::cout << sum;

  delete[] arr;
}