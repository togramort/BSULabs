#include <fstream>
#include <deque>
#include <algorithm>
#include <set>

class functor {
 public:
  bool operator() (const std::string& first, const std::string& second) {
    std::set<char> one;
    std::set<char> two;
    for (char i : first) {
      one.insert(i);
    }
    for (char i : second) {
      two.insert(i);
    }
    int size_first = one.size();
    int size_second = two.size();
    return size_first >= size_second;
  }
};

int main() {

  std::ifstream in("in.txt");
  std::ofstream out("out.txt");

  if (!in.is_open()) {
    out << "input file doesn't exists";
    return 1;
  }

  int size;
  in >> size;
  in.ignore();

  if (in.eof() || size == 0) {
    out << "your file is empty or has no lines";
    return 1;
  }

  if (size < 30) {
    out << "you need more lines :(";
    return 1;
  }

  std::deque<std::string> deque;
  std::string line;
  for (int i = 0; i < size; ++i) {
    if (std::getline(in, line)) {
      if (line.length() > 100) {
        out << "line " << i + 2 << " is too big :(\nits size mustn't be more than 100";
        return 1;
      }
      deque.push_back(std::move(line));
    }
  }

  std::stable_sort(deque.begin(), deque.end(), functor());
  for (int i = 0; i < size; ++i) {
    out << deque[i] << "\n";
  }

  return 0;
}