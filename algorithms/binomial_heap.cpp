#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  std::cin >> n;

  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  bool check = true;
  for (int i = 0; i < n / 2; ++i) {
    if ((2 * i + 1 < n) && v[2 * i + 1] < v[i] || v[2 * i + 2] < v[i] && (2 * i + 2 < n)) {
      check = false;
      break;
    }
  }

  if (!check) {
    std::cout << "No";
  } else {
    std::cout << "Yes";
  }
  return 0;
}