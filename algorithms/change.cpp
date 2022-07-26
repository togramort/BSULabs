#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> allMoney(n + m);

  int customerAmount = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> allMoney[i]; // in theory seller can use customer's money to give a change
    customerAmount += allMoney[i];
  }

  for (int i = n; i < n + m; ++i) {
    std::cin >> allMoney[i];
  }

  std::sort(allMoney.begin(), allMoney.end());

  int change = 1;
  for (int i = 0; i < n + m; ++i) { // find min change that seller cannot return!!!
    if (change >= allMoney[i]) {
      change += allMoney[i];
    }
  }

  if (change >= customerAmount) {
    std::cout << "YES";
  } else {
    std::cout << "NO\n" << customerAmount - change;
  }

  return 0;
}