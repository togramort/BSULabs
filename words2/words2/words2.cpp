#include <iostream>
#include <string>

int main() {
  int N, c = 0;
  std::string s;
  std::getline(std::cin, s);
  std::cout << "\n";
  std::cin >> N;
  std::cout << "\n";
  int i = 0;
  while (s[i] != ' ') {
    ++c;
    ++i;
  }

  std::cout << c;
}
