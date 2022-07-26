#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> v(n + 1, std::vector<int>(k + 1));

  for (int i = 0; i < n + 1; ++i) {
    v[i][0] = 1;
  }
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < k + 1; ++j) {
      v[i][j] = 1;
    }
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < i && j < k + 1; ++j) {
      v[i][j] = (v[i - 1][j - 1] + v[i - 1][j]) % 1000000007;
    }
  }

  std::cout << v[n][k];

  return 0;
}