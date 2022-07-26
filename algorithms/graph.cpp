#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  bool isMulti = false, isPseudo = false;

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n + 1, std::vector<int>(n + 1));
  for (int i = 0; i < m; ++i) {
    int tmp1, tmp2;
    std::cin >> tmp1 >> tmp2;
    if (tmp1 == tmp2) {
      isPseudo = true;
    }

    if (tmp1 > tmp2) {
      ++graph[tmp2][tmp1];
      if (graph[tmp2][tmp1] > 1 && tmp1 != tmp2) {
        isMulti = true;
      }
    } else {
      ++graph[tmp1][tmp2];
      if (graph[tmp1][tmp2] > 1 && tmp1 != tmp2) {
        isMulti = true;
      }
    }
  }

  if (!isMulti && !isPseudo) {
    std::cout << "Yes\n" << "Yes\n" << "Yes";
    return 0;
  } else {
    std::cout << "No\n";
  }

  if (isPseudo) {
    std::cout << "No\n" << "Yes";
    return 0;
  }

  if (isMulti) {
    std::cout << "Yes\n" << "Yes";
  }

  return 0;
}