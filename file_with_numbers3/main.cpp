#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
  std::ifstream in("in.txt");
  std::ofstream out("out.txt");

  if(in.peek() == in.eof()) {
    std::ofstream in2("in2.txt");
  }

  std::vector<int> sort;
  int ort;
  while (!in.eof()) {
    in >> ort;
    sort.push_back(ort);

    std::sort(sort.begin(), sort.end());
    for (int i = 0; i < sort.size() - 1; ++i) {
      if (sort[i] == sort[i + 1]) {
        sort.erase(sort.begin() + i);
      }
    }
  }
  for (int p : sort) {
    std::vector<int> num;
    int line;
    line = p;
    int answer = line;
    while (line != 0) {
      num.push_back(line % 10);
      line /= 10;
    }
    int imax = 0, max = 0;
    for (int i = 0; i < num.size(); ++i) {
      int same = 0;
      for (int j = i; j < num.size(); ++j) {
        if (num[i] == num[j]) {
          ++same;
          if (same > max || same == max && num[i] > num[imax]) {
            max = same;
            imax = i;
          }
        }
      }
    }
    out << answer << ":" << num[imax] << "\n";
  }

  return 0;
}
