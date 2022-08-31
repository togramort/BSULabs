#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <windows.h>

void output(std::string &text, std::string &key, std::string &encrypted) {
  freopen("text.txt", "a", stdout);
  std::cout << text << "\n";

  freopen("key.txt", "a", stdout);
  std::cout << key << "\n";

  freopen("encrypted.txt", "a", stdout);
  std::cout << encrypted << "\n";
}

std::string generate_key() {
  std::string key;
  std::mt19937 gen(time(nullptr));
  std::uniform_int_distribution<> uid1(3, 10);
  for (int i = 0; i < uid1(gen); ++i) {
    std::uniform_int_distribution<> uid2(97, 122);
    key.push_back((char) uid2(gen));
  }
  char choice;
  std::cout << "want to see your key?\ny \\ n\n";
  std::cin >> choice;
  if (choice == 'y') {
    std::cout << "your key: " << key << "\n";
  } else {
    std::cout << "life goes on and on and on and on...\n";
  }
  return key;
}

std::string refactor_key(std::string &text, std::string &key) {
  if (key.size() < text.size()) {
    int counter = 0;
    for (int i = key.size(); i < text.size(); ++i) {
      key.push_back(key[counter]);
      ++counter;
    }
  } else if (key.size() > text.size()) {
    key.erase(key[text.size()], key[key.size()]);
  }
  return key;
}

void encrypt(std::string &alphabet, std::string &text) {
  int temp;
  std::cout << "and the last one (i hope) do you want to enter or generate key?\n"
               "1 - enter key\n"
               "2 - generate key\n";
  std::cin >> temp;
  std::string key;
  if (temp == 1) {
    std::cin >> key;
  } else {
    key = generate_key();
  }

  refactor_key(text, key);

  std::string encrypted;
  for (int i = 0; i < text.size(); ++i) {
    auto find_text = alphabet.find(text[i]);
    auto find_key = alphabet.find(key[i]);

    encrypted.push_back(alphabet[(find_text + find_key) % 26]);
  }
  std::cout << "here is encrypted text\n" << encrypted << "\n";
  output(text, key, encrypted);
}

void decrypt_with_key(std::string &alphabet, std::string &encrypted) {
  std::string key;
  std::cout << "and the last one (i hope) please enter the key!\n";
  std::cin >> key;

  refactor_key(encrypted, key);

  std::string text;
  for (int i = 0; i < encrypted.size(); ++i) {
    auto find_encrypted = alphabet.find(encrypted[i]);
    auto find_key = alphabet.find(key[i]);

    auto answer = alphabet[(find_encrypted - find_key + 26) % 26];
    text.push_back(answer);
  }
  std::cout << "here is your text\n" << text << "\n";
  output(text, key, encrypted);
}

void decrypt(std::string &alphabet) {
  std::cout << "oopsie-daisy... its too hard to do it with such type of encryption!\n"
               "but! there are plenty of examples in 3 files.\n"
               "go check them out!!\n";

  std::chrono::milliseconds timespan(3000);
  std::this_thread::sleep_for(timespan);
  char* link_char="https://planetcalc.ru/2468/";
  ShellExecute(nullptr, nullptr, link_char, nullptr, nullptr , SW_SHOWNORMAL);
}

int main() {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

  int choice;
  std::cout << "oh hi what do you want to do? please choose only one number :P\n"
               "1)encrypt\n2)decrypt(i mean with key)\n3)decrypt (you know what i mean hehe)\n";
  std::cin >> choice;

  std::string text;
  std::cout << "interesting choice.. so now enter your text\n";
  std::cin >> text;

  switch (choice) {
    case 1:encrypt(alphabet, text);
      break;
    case 2:decrypt_with_key(alphabet, text);
      break;
    case 3:decrypt(alphabet);
      break;
    default:break;
  }
  return 0;
}