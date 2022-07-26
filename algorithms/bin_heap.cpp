#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  long long n;
  std::cin >> n;

  std::vector<long long> check;
  while (n / 2 != 0) {
    check.push_back(n % 2);
    n /= 2;
  }
  if (n % 2 == 0) {
    check.push_back(0);
  } else if (n % 2 == 1) {
    check.push_back(1);
  }

  for (int i = 0; i < check.size(); ++i) {
    if (check[i] == 1) {
      std::cout << i << "\n";
    }
  }

  return 0;
}