#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int m, c, n;
  std::cin >> m >> c >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  std::vector<int> hash(m, -1);
  for (int j = 0; j < n; ++j) {
    int i = 0;
    long long h = ((v[j] % m) + c * i) % m;
    while (hash[h] != -1) {
      if (hash[h] == v[j]) {
        break;
      }
      ++i;
      h = ((v[j] % m) + c * i) % m;
    }
    hash[h] = v[j];
  }

  for (int i = 0; i < m; ++i) {
    std::cout << hash[i] << " ";
  }
  return 0;
}