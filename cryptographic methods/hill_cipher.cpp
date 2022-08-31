#include <iostream>
#include <vector>

void encrypt (std::vector<std::vector<int>>& text, std::vector<std::vector<int>>& key) {
  if (text.size() % 2 != 0) {
    text[0].push_back(122);
  }

  std::vector<std::vector<int>> encrypted (text.size(), std::vector<int>(1));
  for (int i = 0; i < key.size(); ++i) {
    for (int j = 0; j < 1; ++j) {
      for (int k = 0; k < text.size(); ++k) {
        encrypted[i][j] = encrypted[i][j] + key[i][k] * text[k][j];
      }
    }
  }

  for (int i = 0; i < encrypted.size(); ++i) {
    std::cout << "encrypted text: " << (char)(encrypted[i][0] % 26 + 97) << "\n";
  }
}

int main() {
  int n;
  std::cout << "enter the dimension of matrix aka key\n";
  std::cin >> n;

  std::vector<std::vector<int>> key (n, std::vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> key[i][j];
    }
  }

  std::string temp;
  std::cout << "enter your input\n";
  std::cin >> temp;

  std::vector<std::vector<int>> input (temp.size(), std::vector<int>(1));
  for (int i = 0; i < input.size(); ++i) {
    input[i][0] = (int)temp[i] - 97;
  }

  encrypt(input, key);
  return 0;
}