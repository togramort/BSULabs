#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

std::vector<int> dist;
std::vector<int> p;
void bfs(std::vector<std::vector<int>> g, int s) {
  dist[s] = 0;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < g[v].size(); ++i) {
      if (dist[i] > dist[v] + 1) {
        p[i] = v;
        dist[i] = dist[v] + 1;
        q.push(i);
      }
    }
  }
}

int main() {
  int k;
  std::string name;
  std::cin >> name >> k;
  int n, m;
  std::cin >> n >> m;
  dist.assign(n, m);
  p.assign(2 * n, -1); //////////
  if (m == 0) {
    std::cout << "0";
    return 0;
  }
  std::string aname;
  std::vector<std::string> names;
  int start = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> aname;
    std::transform(aname.begin(), aname.end(), aname.begin(), tolower);
    names.emplace_back(aname);
    if (aname == name) {
      start = i;
    }
  }
  std::vector<std::vector<int>> g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    std::string name1, name2;
    std::cin >> name1 >> name2;
    for (int r = 0; r < n; ++r) {
      if (name1 == names[r]) {
        for (int j = 0; j < n; ++j) {
          if (name2 == names[j]) {
            g[r].emplace_back(j);
            g[j].emplace_back(r);
          }
        }
      }
    }
  }

  bfs(g, start);
  int f = start + k; /////////

  if (dist[f] != n) {
    std::cout << "\n" << "0";
    return 0;
  }
  std::vector<int> path;
  while(f != -1) {
    std::cout << "f = " << f << "\n";
    path.emplace_back(f);
    f = p[f];
  }
  reverse(path.begin(), path.end());
  std::cout << path.size() << "\n";
  for (int kI = 0; kI < path.size(); ++kI) {
    std::cout << names[path[kI]] << " " << kI + 1 << "\n";
  }

  return 0;
}