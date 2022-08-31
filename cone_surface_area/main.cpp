#include <iostream>
#include <cmath>

int main() {
  int r, h;
  std::cin >> r >> h;

  double l = std::sqrt(r * r + h * h);
  double s = M_PI * r * l;

  std::cout << s << "\n";

  return 0;
}
