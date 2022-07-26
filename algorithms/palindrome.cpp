#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  std::string s;
  std::cin >> s;
  if (s.length() == 1) {
    std::cout << 1 << "\n" << s;
    return 0;
  }

  std::vector<std::vector<int>> v(s.length(), std::vector<int>(s.length()));
  for (int i = 0; i < s.length(); ++i) {
    v[i][i] = 1;
  }

  for (int i = 0; i < s.length() - 1; ++i) {
    if (s[i] == s[i + 1]) {
      v[i][i + 1] = 2;
    } else {
      v[i][i + 1] = 1;
    }
  }

  int n = 2;
  for (int i = 0; i < s.length() - n;) {
    for (int j = n; j < s.length();) {
      if (s[i] == s[j]) {
        v[i][j] = v[i + 1][j - 1] + 2;
      } else {
        v[i][j] = std::max(v[i + 1][j], v[i][j - 1]);
      }
      ++i;
      ++j;
    }
    ++n;
    i = 0;
  }

  std::cout << v[0][s.length() - 1] << "\n";

  std::string ans1;
  int i = 0, j = s.length() - 1;
  while (j > i) {
    if (v[i][j] == v[i + 1][j]) {
      ++i;
    } else if (v[i][j] == v[i][j - 1]) {
      --j;
    } else if (v[i][j] == v[i + 1][j - 1] + 2) {
      ans1 += s[i];
      ++i;
      --j;
    }
  }
  if (i == j) {
    ans1 += s[i];
  }

  std::string ans2 = ans1;
  if (v[0][s.length() - 1] % 2 != 0) {
    ans2.erase(ans2.length() - 1);
  }

  std::reverse(ans2.begin(), ans2.end());
  std::cout << ans1 << ans2;

  return 0;
}