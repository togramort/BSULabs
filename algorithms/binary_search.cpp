#include <iostream>
#include <vector>
#include <cmath>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }

  int m;
  std::cin >> m;
  std::vector<int> req(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> req[i];
  }

  bool b = false;
  int l = 0, r = 0;
  double w = vec.size();

  for (int i: req) {
    int x = 0;
    while (x < w) {
      int k = floor((x + w) / 2);
      if (i == vec[k]) {
        b = true;
      } else if (vec[k] > i) {
        w = k;
      } else {
        x = k + 1;
      }
    }
    while (l < w && r < w) {
      int k = floor((l + w) / 2);
      int c = floor((k + w) / 2);
      if (i <= vec[k]) {
        w = k;
      } else if (i < vec[k]) {
        w = c;
      } else {
        l = k + 1;
        r = c + 1;
      }
    }
    std::cout << b << " " << l << " " << r << "\n";
  }

  return 0;
}