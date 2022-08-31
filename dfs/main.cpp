#include <iostream>
#include <vector>

void dfs(int v, std::vector<std::vector<int>> &g, std::vector<bool> &used, std::vector<int> &prev) {
  used[v] = true;
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (!used[u]) {
      prev[u] = v;
      dfs(u, g, used, prev);
    } else if (used[u] && prev[u] != v) {
      std::cout << "NO";
      exit(0);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n, std::vector<int>());
  std::vector<bool> used(n, false);
  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    g[a].emplace_back(b);
  }
  std::vector<int> prev(n, -1);
  dfs(0, g, used, prev);

  bool check = true;
  for (int i = 0; i < used.size(); ++i) {
    if (!used[i]) {
      check = false;
    }
  }
  if (check) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
