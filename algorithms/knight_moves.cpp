#include <iostream>
#include <vector>
#include <queue>

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;

  std::queue<std::pair<int, int>> q;
  q.push(std::make_pair(x1, y1));
  std::pair<int, int> tmp;
  matrix[x1][y1] = 1;

  std::vector<int> moveI = {-1, -1, 1, 1, -2, -2, 2, 2};
  std::vector<int> moveJ = {-2, 2, 2, -2, -1, 1, 1, -1};
  while (!q.empty()) {
    tmp = q.front();
    q.pop();
    for (int k = 0; k < 8; ++k) {
      int i = tmp.first + moveI[k];
      int j = tmp.second + moveJ[k];
      if (i > 0 && i <= n && j > 0 && j <= m && matrix[i][j] == 0) {
        matrix[i][j] += matrix[tmp.first][tmp.second] + 1;
        q.push(std::make_pair(i, j));
      }
    }
  }

  if (matrix[x2][y2] <= 0) {
    std::cout << "No";
  } else {
    std::cout << matrix[x2][y2] - 1;
  }
  return 0;
}