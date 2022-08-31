#include <iostream>
#include <vector>
#include <queue>

std::deque <int> st;
void euler(int u, std::vector<bool> &vis, std::vector<int> &first, std::vector<std::vector<std::pair<int, int>>> &g) {
  while (first[u] < g[u].size()) {
    auto p = g[u][first[u]];
    ++first[u];
    auto i = p.first, v = p.second;
    if (!vis[i]) {
      vis[i] = true;
      euler(v, vis, first, g);
      st.emplace_back(u);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  if (m == 0) {
    std::cout << "NO";
    return 0;
  }
  int u, v;
  std::vector<std::vector<std::pair<int, int>>> g(n, std::vector<std::pair<int, int>>());
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    g[u].emplace_back(std::make_pair(i, v));
    g[v].emplace_back(std::make_pair(i, u));
  }
  std::vector<int> deg(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < g[i].size(); ++j) {
      if (g[i][j].second >= 0) {
        ++deg[i];
      }
    }
  }
  for (int i = 0; i < deg.size(); ++i) {
    if (deg[i] % 2 != 0) {
      std::cout << "NO";
      return 0;
    }
  }
  std::vector<bool> vis(m);
  std::vector<int> first(n);
  for (int i = 0; i < g.size(); ++i) {
    euler(i, vis, first, g);
  }

  std::cout << st.back() << " ";
  for (int j = 0; j < st.size(); ++j) {
    std::cout << st[j] << " ";
  }

  return 0;
}