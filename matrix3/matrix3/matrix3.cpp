#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

int main() {
  int rows, cols;
  std::cout << "enter the amount of rows"
            << "\n";
  std::cin >> rows;
  std::cout << "enter the amount of columns"
            << "\n";
  std::cin >> cols;
  if (rows <= 0 || rows > 20 || cols <= 0 || cols > 20) {
    return 1;
  }

  int r = 0;
  std::cout << "choose the type if enter:\n 1 - random\n 2 - keyboard"
            << "\n";
  std::cin >> r;

  long long **a = new long long *[rows];
  for (int i = 0; i < rows; ++i) {
    a[i] = new long long[cols];
  }
  if (r == 1) {
    std::mt19937 gen((unsigned int)time(nullptr));
    std::uniform_int_distribution<int> urd(-100, 100);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        a[i][j] = urd(gen);
        std::cout << std::setw(4) << a[i][j] << "\t";
      }
      std::cout << "\n";
    }
  } else if (r == 2) {
    std::cout << "enter numbers"
              << "\n";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::cin >> a[i][j];
        std::cout << std::setw(4) << a[i][j] << "\t";
      }
      std::cout << "\n";
    }
  } else {
    return 1;
  }

  int sum = 0, check = 1;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (a[i][j] == 0) {
        std::cout << "sum of elements in a row with zero = ";
        for (int k = 0; k < cols; ++k) {
          sum += a[i][k];
          check = 0;
        }
        std::cout << sum << "\n";
        break;
      }
    }
  }
  if (check == 1) {
    std::cout << "no zeros in rows"
              << "\n";
  }

  int res = 0;
  for (int i = 0; i < rows; ++i) {
    int min = a[i][0];
    for (int j = 0; j < cols; ++j) {
      if (a[i][j] < min) {
        min = a[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      if (a[i][j] == min) {
        for (int k = 0; k < rows; ++k) {
          if (min < a[k][j]) {
            break;
          }
          if (k == rows - 1) {
            ++res;
          }
        }
      }
    }
  }
  std::cout << "the number of saddle point(s): " << res << "\n";

  int *s = new int[rows];
  for (int i = 0; i < rows; ++i) {
    s[i] = 0;
    for (int j = 0; j < cols; ++j) {
      if (a[i][j] >= 0) {
        s[i] += a[i][j];
      }
    }
  }
  for (int i = 0; i < rows - 1; ++i) {
    for (int k = 0; k < rows - i - 1; ++k) {
      if (s[k] > s[k + 1]) {
        std::swap(s[k], s[k + 1]);
        for (int j = 0; j < cols; ++j) {
          std::swap(a[k][j], a[k + 1][j]);
        }
      }
    }
  }
  std::cout << "new matrix: "
            << "\n";
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << std::setw(4) << a[i][j] << "\t";
    }
    std::cout << "\n";
  }

  int count = 0;
  for (int i = 0; i < cols; ++i) {
    int c = 0;
    for (int j = 0; j < rows; ++j) {
      if (a[j][i] == 0) {
        c = 1;
        break;
      }
    }
    if (c == 0) {
      ++count;
    }
  }
  std::cout << "the number of columns without zero(s): " << count << "\n";

  for (int i = 0; i < rows; ++i) {
    delete[] a[i];
  }
  delete[] a;
  return 0;
}