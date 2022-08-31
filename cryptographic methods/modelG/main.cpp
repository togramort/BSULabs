#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <chrono>
#include "blockcryptosystemG.h"
#include <string>

std::vector<std::bitset<8>> ReadKey(std::string&& filename) {
  std::ifstream keys_file(filename, std::ios::in | std::ios::binary);

  std::vector<std::bitset<8>> keys(4, std::bitset<8>());
  for (size_t i = 0; i < 4; ++i) {
    keys_file >> keys[i];
  }
  keys_file.close();
  return keys;
}

void Encrypt() {
  std::string temp;
  std::cout << "enter file name: ";
  std::cin >> temp;

  std::ifstream fin;
  std::ofstream fout;

  fin.open(temp, std::ifstream::binary | std::ifstream::in);
  fout.open("encrypted", std::ifstream::binary | std::ofstream::out);

  if (!fin.is_open()) {
    std::cerr << "file can't be opened\n";
    return;
  }

  std::cout << "enter amount of clocks: ";
  int clocks{};
  std::cin >> clocks;

  auto keys = ReadKey("keys.txt");
  std::cout << "current key: ";
  for (const auto& key : keys) {
    std::cout << key;
  }
  std::cout << "\n";
  std::cout << "encryption is in process. wait...\n";
  fin >> std::noskipws;

  char x1, x2;
  auto start = std::chrono::high_resolution_clock::now();
  while (fin >> x1) {
    if (!(fin >> x2)){
      x2 = ' ';
    }
    auto res = CryptoSystem::CipherBlock(x1, x2, keys, clocks);
    fout << res.first << res.second;
  }
  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "yay time: " << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 1000 << " s\n";

  fin.close();
  fout.close();
}

void Decrypt() {
  std::string path;
  std::cout << "enter destination file name: ";
  std::cin >> path;

  std::ifstream fin;
  std::ofstream fout;

  fin.open("encrypted", std::ifstream::binary | std::ifstream::in);
  fout.open(path, std::ifstream::binary | std::ofstream::out);

  if (!fin.is_open()) {
    std::cerr << "encrypted file can't be opened\n";
    return;
  }

  std::cout << "enter amount of clocks: ";
  int clocks{};
  std::cin >> clocks;

  auto keys = ReadKey("keys.txt");
  std::cout << "current key: ";
  for (const auto& key : keys)
    std::cout << key;
  std::cout << "\n";
  std::cout << "decryption is in process. wait about 30 seconds...\n";
  fin >> std::noskipws;

  char x1, x2;
  auto start = std::chrono::high_resolution_clock::now();
  while (fin >> x1 >> x2) {
    auto res = CryptoSystem::DecipherBlock(x1, x2, keys, clocks);
    fout << res.first << res.second;
  }
  auto finish = std::chrono::high_resolution_clock::now();

  std::cout << "success. decryption time: " << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 1000 << " seconds\n";

  fin.close();
  fout.close();
}

void GenerateKey() {
  std::ofstream fout("keys.txt", std::ofstream::out);

  auto keys = CryptoSystem::GetRandomKeys();

  std::cout << "done! your key: ";
  for (const auto& key : keys) {
    fout << key;
    std::cout << key;
  }

  std::cout << "\nsaved to \"keys.txt\"\n";

  fout.close();
}

void SerialTest() {
  std::ifstream in("encrypted", std::ios::binary | std::ifstream::in);
  std::ofstream out("bin_cipher.txt");
  in >> std::noskipws;
  char c;
  std::bitset<8> temp;
  while (in >> c) {
    temp = std::bitset<8>(c);
    out << temp.to_string();
  }
  in.close();
  out.close();
  system("python ..\\sttest.py");
}

int main() {
  int choice;
  while (true) {
    std::cout << "choose the action:\n"
              << "\t1 - encrypt file;\n"
              << "\t2 - decrypt file;\n"
              << "\t3 - generate key;\n"
              << "\t4 - serial test;\n"
              << "\t5 - exit\n"
              << ">>> ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        Encrypt();
        break;
      case 2:
        Decrypt();
        break;
      case 3:
        GenerateKey();
        break;
      case 4:
        SerialTest();
      case 5:
        return 0;
      default:
        std::cerr << "try again\n";

    }
  }
}