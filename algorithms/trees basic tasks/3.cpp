#include <iostream>
#include <vector>

int main() {
  FILE *fin, *fout;
  fin = fopen("bst.in", "r");
  fout = fopen("bst.out", "w");

  int amount = 0;
  fscanf(fin, "%i /n", &amount);

  int root = 0;
  fscanf(fin, "%i /n", &root);

  int v = 0, line = 0;
  char where;
  std::vector<int> vertex(amount + 1);
  std::vector<std::pair<int, char>> pair(amount + 1);

  vertex[1] = root;

  for (int i = 2; i <= amount; ++i) {
    fscanf(fin, "%i %i %c /n", &v, &line, &where);
    vertex[i] = v;
    pair[i] = std::make_pair(line, where);
  }

  bool flag = true;
  for (int i = 1; i < vertex.size(); ++i) {
    for (int j = 2; j < pair.size(); ++j) {
      if (pair[j].second == 'R' && vertex[j] < vertex[pair[j].first] ||
          pair[j].second == 'L' && vertex[j] >= vertex[pair[j].first]) {
        flag = false;
        break;
      }
      if (pair[j].first == i &&
          (pair[j].second == 'L' && vertex[j] >= vertex[i] ||
          pair[j].second == 'R' && vertex[j] < vertex[i])) {
        flag = false;
        break;
      }
    }
  }
  if (flag) {
    fprintf(fout, "%s", "YES");
  } else {
    fprintf(fout, "%s", "NO");
  }

  return 0;
}