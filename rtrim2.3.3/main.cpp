#include <iostream>
#include <cstring>

int main() {
  char *str = new char[301];
  std::cout << "enter the string" << "\n";
  std::cin.getline(str, 301);

  char *latin = new char[301];
  char *other = new char[301];

  char *word = strtok(str, " ");
  while (word != nullptr) {
    bool flag = true;
    for (size_t i = 0; i < strlen(word); ++i) {
      if (!(word[i] >= 'a' && word[i] <= 'z' || word[i] >= 'A' && word[i] <= 'Z')) {
        flag = false;
      }
    }
    if (flag) {
      strcat(latin, word);
      strcat(latin, " ");
    } else {
      strcat(other, word);
      strcat(other, " ");

    }
    word = strtok(nullptr, " ");
  }
  strcat(latin, other);
  std::cout << latin;

  delete[] word;
  delete[] latin;
  delete[] other;

  return 0;
}