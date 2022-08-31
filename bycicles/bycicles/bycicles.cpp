#include <iomanip>
#include <iostream>

int main() {
  double L, v1, v2, N;
  std::cin >> L >> v1 >> v2 >> N;
  double r;
  r = ((N * L * abs(v1 - v2)) / std::min(v1, v2));
  while (r > (L / 2)) {
    r -= L;
  }
  std::cout << std::fixed << std::setprecision(4) << abs(r);
  return 0;
}
