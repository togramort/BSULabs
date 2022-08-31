#include "blockcryptosystemG.h"

int pow(int x, int y, int mod) {
  int res = 1;
  x %= mod;
  if (!x)
    return 0;
  while (y > 0) {
    if (y & 1)
      res = (res * x) % mod;
    y >>= 1;
    x = (x * x) % mod;
  }
  return res;
}

std::vector<std::bitset<8>> CryptoSystem::GetRandomKeys() {
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> uint;

    std::bitset<32> result(uint(gen));
    auto result_keys = std::vector<std::bitset<8>>(4, std::bitset<8>());

    for (size_t i = 0; i < 32; ++i) {
      result_keys[i / 8][i % 8] = result[i];
    }

    return result_keys;
}

std::pair<char, char> CryptoSystem::Clock(char first, char second, const std::bitset<8>& k) {
  std::pair<char, char> result;
  result.first = second;

  std::bitset<8> second_block(second);
  second_block ^= k;

  std::bitset<4> z1, z2;

  for (size_t i = 0; i < z1.size(); ++i) {
    z1[i] = second_block[i];
    z2[i] = second_block[i + 4];
  }
  z1 = std::bitset<4>(S1(z1));
  z2 = std::bitset<4>(S2(z2));

  for (size_t i = 0; i < z1.size(); ++i) {
    second_block[i] = z1[i];
    second_block[i + 4] = z2[i];
  }

  second_block = ((second_block << 3) | (second_block >> 5)) ^ std::bitset<8>(first);

  result.second = second_block.to_ulong();

  return result;
}

std::pair<char, char> CryptoSystem::CipherBlock(char X1, char X2, const std::vector<std::bitset<8>>& key, size_t clocks) {
  for (size_t i = 0; i < clocks; ++i) {
    auto res = Clock(X1, X2, key[i % key.size()]);
    X1 = res.first;
    X2 = res.second;
  }

  return std::make_pair(X1, X2);
}
std::pair<char, char> CryptoSystem::DecipherBlock(char X1, char X2, const std::vector<std::bitset<8>>& key, size_t clocks) {
  for (size_t i = 0; i < clocks; ++i) {
    auto res = Clock(X2, X1, key[(clocks - 1 - i) % key.size()]);
    X1 = res.second;
    X2 = res.first;
  }

  return std::make_pair(X1, X2);
}

int CryptoSystem::S1(const std::bitset<4>& x) {
  return (pow(3, x.to_ulong(), 17) + 2) % 16;
}

int CryptoSystem::S2(const std::bitset<4>& x) {
  return (pow(5, x.to_ulong(), 17) + 7) % 16;
}