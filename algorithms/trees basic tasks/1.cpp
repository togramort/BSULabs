#include <iostream>
#include <fstream>
#include <set>

int main() {
  std::ifstream in ("input.txt");
  std::ofstream out ("output.txt");
  std::set <int> set;
  int x;

  while (!in.eof()) {
    in >> x;
    set.insert(x);
  }

  long long sum = 0;
  for(std::set<int>::const_iterator it = set.begin(); it != set.end(); ++it) { //range loop
    sum += (*it);
  }
  out << sum;

  return 0;
}