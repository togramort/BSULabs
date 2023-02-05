#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <vector>
#include <cstdio>

 struct pcout : public std::stringstream {
  static inline std::mutex cout_mutex;
  ~pcout() {
    std::lock_guard<std::mutex> l {cout_mutex};
    std::cout << rdbuf();
    std::cout.flush();
  }
};

void print_cout(int id) {
  std::cout << "cout hello from " << id << '\n';
}

void print_pcout(int id) {
  pcout{} << "pcout hello from " << id << '\n';
}

int main() {
  freopen("file.txt", "w", stdout);

  std::vector<std::thread> v;
  for (size_t i {0}; i < 50; ++i) {
    v.emplace_back(print_cout, i);
  }

  for (auto &t : v) {
    t.join();
  }

  std::cout << "=====================\n";
  v.clear();

  for (size_t i {0}; i < 50; ++i) {
    v.emplace_back(print_pcout, i);
  }

  for (auto &t : v) {
    t.join();
  }

  return 0;
}