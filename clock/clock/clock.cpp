#include <iomanip>
#include <iostream>

int main() {
  double h, m;
  char c;
  std::cin >> h >> c >> m;
  double r = 0;
  if (c == ':') {
    if (h >= 12) {
      h -= 12;
    }

    h = (m / 2) + (30 * h);
    r = abs(h - (6 * m));

    if (r > 180) {
      r = 360 - r;
    }
  }

  std::cout << std::fixed << std::setprecision(4) << r;
  return 0;
}
