#include <iostream>

int main() {
  int N;
  std::cin >> N;

  int *a = new int[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> a[i];
  }
  std::cout << "\n";

  int res = 0;
  for (int i = 1; i < N; ++i) {
    if (a[i] == a[0]) {
      ++res;
    }
  }
  std::cout << res;

  delete[] a;
  return 0;
}