#include <iostream>
#include <cmath>

double f1(double x) {
  return x * x * x * std::exp(2 * x);
}

double f2(double x) {
  return 1 / (1 + std::sqrt(x));
}

double f3(double x) {
  return 1 / ((1 + x) * std::sqrt(x * x + 1));
}

std::pair<double, int> integral(double f(double), double a, double b, double eps) {
  double s1 = 0, s2 = eps;
  int n = 1;
  while (std::abs(s1 - s2) >= eps) {
    double h = (b - a) / n;
    double sumf = 0;
    for (int i = 1; i <= n - 1; ++i) {
      sumf += f(a + i * h);
    }
    s1 = s2;
    s2 = h * (((f(a) + f(b)) / 2) + sumf);
    ++n;
  }
  return std::make_pair(s2, n);
}

int main() {
  double eps;
  std::cout << "enter the accuracy";
  std::cin >> eps;
  if (eps >= 0.1 || eps <= 0.00000001) {
    return 1;
  }

  std::pair<double, int> answer1 = integral(f1, 0, 0.8, eps);
  std::cout << "integral of the first function is " << answer1.first << "\n";
  std::cout << "the number of splits " << answer1.second << "\n";

  std::pair<double, int> answer2 = integral(f2, 0, 1.8, eps);
  std::cout << "integral of the second function is " << answer2.first << "\n";
  std::cout << "the number of splits " << answer2.second << "\n";

  std::pair<double, int> answer3 = integral(f3, 0, 0.3, eps);
  std::cout << "integral of the third function is " << answer3.first << "\n";
  std::cout << "the number of splits " << answer3.second << "\n";

  return 0;
}