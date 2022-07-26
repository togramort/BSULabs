#include <iostream>
#include <vector>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int s;
  std::cin >> s;

  std::vector<std::pair<int, int>> num(s);
  for (int i = 0; i < num.size(); ++i) {
    std::cin >> num[i].first >> num[i].second;
  }

  std::vector<std::vector<int>> v(s, std::vector<int>(s));

  for (int i = 0; i < v.size(); ++i) {
    for (int j = 0; j < v[i].size(); ++j) {
      v[i][j] = 0;
    }
  }

  for (int i = 0; i < v.size() - 1;) {
    for (int j = 1; j < v[i].size();) {
      v[i][j] = num[i].first * num[i].second * num[i + 1].second;
      ++i;
      ++j;
    }
  }


  for (int i = 0; i < v.size();) {
    for (int j = v[i].size() - 1; j > -1;) {
      for (int k = 0; k < v.size() - 1;) {
        v[i][j] = std::min(v[i][j], v[i][k] + v[k + 1][j] + num[i].first * num[k].second * num[j].second);
        ++i;
        --j;
        ++k;
      }
    }
  }


  std::cout << v[0][s - 1] << "\n";

  for (int i = 0; i < v.size(); ++i) {
    for (int j = 0; j < v[i].size(); ++j) {
      std::cout << v[i][j] << "\t";
    }
    std::cout << "\n";
  }

  return 0;
}
