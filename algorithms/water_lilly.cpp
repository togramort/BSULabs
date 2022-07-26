#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  std::cin >> n;

  std::vector<int> mosquito (n);
  for (int i = 0; i < n; ++i) {
    std::cin >> mosquito[i] ;
  }

  if (n == 1) {
    std::cout << mosquito[0];
    return 0;
  } else if (n == 2) {
    std::cout << -1;
    return 0;
  }

  std::vector<int> max_mosquito (n, 0);
  max_mosquito[0] = mosquito[0];
  max_mosquito[1] = INT32_MIN;
  max_mosquito[2] = mosquito[0] + mosquito[2];

  for (int i = 3; i < n; ++i) {
    max_mosquito[i] = mosquito[i] + std::max(max_mosquito[i - 2], max_mosquito[i - 3]);
  }

  if (max_mosquito[max_mosquito.size() - 1] == 0) {
    std::cout << -1;
  } else {
    std::cout << max_mosquito[max_mosquito.size() - 1];
  }

  return 0;
}