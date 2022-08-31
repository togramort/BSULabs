#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

void output(std::vector<std::pair<char, char>> &alphabet_key, std::string &text, std::string &encrypted) {
  std::string key;
  for (auto & i : alphabet_key) {
    key.push_back(i.second);
  }

  int choice;
  std::cout << "do you want to see the key? \n1 - yes\n2 - no\n";
  std::cin >> choice;

  if (choice == 1) {
    std::cout << "tss.. your key is: " << key << "\n";
  } else {
    std::cout << "okay byee\n";
  }

  freopen("text.txt", "a", stdout);
  std::cout << text << "\n";

  freopen("key.txt", "a", stdout);
  std::cout << key << "\n";

  freopen("encrypted.txt", "a", stdout);
  std::cout << encrypted << "\n";
}

std::vector<std::pair<char, char>> generate_key(std::vector<std::pair<char, char>> &alphabet_key) {
  std::mt19937 gen(time(nullptr));
  std::uniform_int_distribution<int> uid(0, 25);

  for (int i = 0; i < alphabet_key.size(); ++i) {
    for (int j = 0; j < alphabet_key.size(); ++j) {
      std::swap(alphabet_key.at(j).second, alphabet_key.at(uid(gen)).second);
    }
  }

  for (auto & i : alphabet_key) {
    std::cout << "(" << i.first << ", " << i.second << ")\n";
  }
  return alphabet_key;
}

void encrypt(std::string &text, std::vector<std::pair<char, char>> &alphabet_key) {
  generate_key(alphabet_key);
  std::string encrypted;

  for (char i : text) {
    for (auto & j : alphabet_key) {
      if (j.first == i) {
        encrypted.push_back(j.second);
        break;
      }
    }
  }

  std::cout << "here we go! encrypted text: " << encrypted << "\n";
  output(alphabet_key, text, encrypted);
}

void decrypt_with_key(std::string &encrypted, std::vector<std::pair<char, char>> &alphabet_key) {
  std::string key;
  std::cout << "and the last one (i hope) give me the key!\n";
  std::cin >> key;

  for (int i = 0; i < alphabet_key.size(); ++i) {
    alphabet_key.at(i).second = (char) key[i];
  }

  std::string text;
  for (char i : encrypted) {
    for (auto & j : alphabet_key) {
      if (i == j.second) {
        text.push_back(j.first);
        break;
      }
    }
  }

  std::cout << "oh look at this decrypted text: " << text << "\n";
  output(alphabet_key, text, encrypted);
}

void decrypt(std::string &text, std::vector<std::pair<char, char>> &alphabet_key) {
  std::cout << "oopsie-daisy... its too hard to do it with such type of encryption!\n"
               "but! there are plenty of examples in 3 files.\n"
               "go check them out!!\n";
}

int main() {
  int choice;
  std::cout << "oh hi what do you want to do? please choose only one number :P\n"
               "1)encrypt\n2)decrypt(i mean with key)\n3)decrypt (you know what i mean hehe)\n";
  std::cin >> choice;

  std::string text;
  std::cout << "interesting choice.. so now enter your text\n";
  std::cin >> text;

  std::vector<std::pair<char, char>> alphabet_key(26);
  int ascii = 97;
  for (auto & i : alphabet_key) {
    i.first = (char) ascii;
    i.second = (char) ascii;
    ++ascii;
  }

  switch (choice) {
    case 1:encrypt(text, alphabet_key);
      break;
    case 2:decrypt_with_key(text, alphabet_key);
      break;
    case 3:decrypt(text, alphabet_key);
      break;
    default:break;
  }
  return 0;
}