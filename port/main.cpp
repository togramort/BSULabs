#include <fstream>
#include <string>
#include <queue>

int main() {
  std::ifstream in("SHIPS.IN");
  std::ofstream out("SHIPS.OUT");

  if (in.eof()) {
    out << "input file is empty";
    return 0;
  }

  int n;
  in >> n;

  int condition;
  std::string name;
  std::deque<std::string> queue;
  int free_prier;
  std::vector<std::pair<std::string, int>> ship_prier (n, std::make_pair((""), 0));
  int c = 0;

  while (!in.eof()) {
    in >> condition;
    switch (condition) {
      case 1: {
        std::getline(in, name);
        queue.push_back(name);
        break;
      }
      case 2: {
        in >> free_prier;

          if (ship_prier[free_prier - 1].second == 0 && !queue.empty()){
            ship_prier[free_prier - 1].first = queue.front();
            ++c;
          } else {
            queue.push_back(name);
          }
        break;
      }
      case 3: {
        out << "in the reid " << queue.size() << " ship(s):\n";
        for (int i = 0; i < queue.size(); ++i) {
          out << queue[i] << "\n";
        }
        break;
      }
      case 4: {
        for (int i = 0; i < c; ++i) {
          out << "there is the ship" << ship_prier[i].first << " at the prier " << ship_prier[i].second << "\n";
        }
        break;
      }

    }

  }

  return 0;
}
