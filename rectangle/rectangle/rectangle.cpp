#include <iostream>
#include <algorithm>
int main() {
  long long x1, y1, x2, y2, x3, y3, x4, y4;
  std::cin >> x1 >> y1 >> x2 >> y2;
  std::cout << "\n";
  std::cin >> x3 >> y3 >> x4 >> y4;
  if (x1 > x2) {
    std::swap(x1, x2);
  }
  if (y1 < y2) {
    std::swap(y1, y2);
  }
  if (x3 > x4) {
    std::swap(x3, x4);
  }
  if (y3 < y4) {
    std::swap(y3, y4);
  }
  long long x5 = std::max(x1, x3),
            y5 = std::min(y1, y3), 
            x6 = std::min(x2, x4),
            y6 = std::max(y2, y4);
  long long s;
  s = (x6 - x5) * (y5 - y6);
  if ((x6 - x5) < 0 || (y5 - y6) < 0) {
    s = 0;
  }
  std::cout << abs(s);
}