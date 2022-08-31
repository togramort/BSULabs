#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

int main() {
  int n, r;
  std::cout << "choose the size of array: "
            << "\n";
  std::cin >> n;
  if (n <= 0) {
    std::cout << "error"
              << "\n";
    return 0;
  }

  std::cout << "choose the type of input:\n1 - random\n2 - from keyboard"
            << "\n";
  std::cin >> r;

  std::mt19937 gen((unsigned int)time(nullptr));
  std::uniform_int_distribution<int> urd(-100, 100);

  int *a = new int[n];
  int f = -1, l = -1;

  if (r == 1) {
    std::cout << "array: ";
    for (int i = 0; i < n; ++i) {
      a[i] = urd(gen);
      std::cout << " " << a[i];
    }
    std::cout << "\n";
  } else if (r == 2) {
    std::cout << "enter numbers of array: ";
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
  } else {
    std::cout << "enter only 1 or 2!"
              << "\n";
    return 0;
  }

  long long p = 1;
  if (n == 1) {
    std::cout << "not enought numbers"
              << "\n";
  } else {
    for (int j = 1; j < n; j += 2) {
      p *= a[j];
    }
    std::cout << "composition = " << p << "\n";
  }

  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      l = i;
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    if (i != l && a[i] == 0) {
      f = i;
    }
  }
  int sum = 0;
  if (f == -1 || l == -1) {
    std::cout << "we dont have enough zeros"
              << "\n";
  } else {
    for (int i = f; i <= l; ++i) {
      sum += a[i];
    }
    std::cout << "sum = " << sum << "\n";
  }

  for (int i = 0; i < n; ++i) {
    if (a[i] < 0) {
      for (int j = i + 1; j < n; ++j) {
        if (a[j] >= 0) {
          std::swap(a[j], a[i]);
          break;
        }
      }
    }
  }
  std::cout << "reformed array: ";
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }
  delete[] a;
  return 0;
}