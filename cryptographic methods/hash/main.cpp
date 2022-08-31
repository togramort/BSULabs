#include <iostream>
#include <fstream>
#include <bitset>
#include "blockcryptosystemG.h"
#include <string>


void PrintResult(std::bitset<32> hash, std::ofstream& out, std::ofstream& bin) {
  bin << hash.to_string() << " ";
  std::vector<char> output(4);
  for (int i = 3; i >= 0; --i) {
    output[i] = static_cast<char>(((hash << 24) >> 24).to_ulong());
    hash >>= 8;
  }
  for (auto c: output) {
    out << c;
  }
}

std::bitset<32> GetCipher(std::bitset<32> block, const std::bitset<32>& key) {
  std::vector<std::bitset<8>> keys(4, std::bitset<8>(0));
  for (int i = 0; i < 32; ++i){
    keys[i / 8][i % 8] = key[i];
  }

  std::vector<std::bitset<8>> chars(4);

  for (int i = 3; i >= 0; --i) {
    chars[i] = std::bitset<8>(((block << i * 8) >> i * 8).to_ulong());
    block >>= 8;
  }
  for (int i = 0; i < 2; ++i) {
    std::pair<std::bitset<8>, std::bitset<8>> enc_result = CryptoSystem::CipherBlock(chars[2 * i], chars[2 * i + 1], keys, 8);
    block |= std::bitset<32>(enc_result.first.to_ulong());
    block <<= 8;
    block |= std::bitset<32>(enc_result.second.to_ulong());
    block <<= 8;
  }

  return block;
}

std::bitset<32> GetHash(const std::bitset<32>& X, const std::bitset<32>& Y) {
  return Y ^ GetCipher(Y, X);
}

void HashFile() {
  std::cout << "hash process start...\n";
  std::ifstream fin("input.txt", std::ifstream::binary | std::ifstream::in);
  std::ofstream fout("message.txt", std::ifstream::binary | std::ofstream::out);
  std::ofstream bin_hash("bin_message.txt", std::ifstream::binary | std::ofstream::out);

  fin >> std::noskipws;
  fout << std::noskipws;
  if (!fin.is_open()) {
    std::cerr << "file can't be opened\n";
    return;
  }
  char input;
  std::bitset<32> first_block, hash;
  hash = std::bitset<32>(93292932);
  bool file_ended = false;
  long long int counter = 0;
  while(fin >> input) {
    ++counter;
    first_block = std::bitset<32>(0);
    first_block |= std::bitset<32>(input);
    for (int i = 0; i < 3; ++i) {
      if (fin >> input) {
        ++counter;
        first_block <<= 8;
        first_block |= std::bitset<32>(input);
      } else {
        file_ended = true;
        break;
      }
    }
    hash = GetHash(first_block, hash);

    if (file_ended) {
      first_block = std::bitset<32>(counter);
      hash = GetHash(first_block, hash);
    }
  }

  if (!file_ended) {
    first_block = std::bitset<32>(counter);
    hash = GetHash(first_block, hash);
  }
  PrintResult(hash, fout, bin_hash);
  std::cout << "\nhash process finished. check out information in message.txt\n";
}

int main() {
  HashFile();
  return 0;
}