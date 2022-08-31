#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  std::ifstream in("in.txt");
  std::ofstream out("out.txt");

  int n;
  in >> n;
  if (n == 0) {
    std::ofstream out2("out2.txt");
  }
  std::vector<int> nums;
  int number;
  while (!in.eof()) {
    in >> number;
    nums.push_back(number);
  }
  std::sort(nums.rbegin(), nums.rend());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());
  bool prime;
  for (int num : nums) {
    prime = true;
    for (int j = 2; j <= sqrt(num); ++j) {
      if (num % j == 0) {
        prime = false;
        out << num << ":" << "composite" << "\n";
        break;
      }
    }
    if (prime) {
      out << num << ":" << "prime" << "\n";
    }
  }

  return 0;
}
