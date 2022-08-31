#ifndef MODELG__BLOCKCRYPTOSYSTEMG_H_
#define MODELG__BLOCKCRYPTOSYSTEMG_H_

#include <bitset>
#include <random>
#include <ctime>
#include <vector>

class CryptoSystem {
 private:
  static int S1(const std::bitset<4>& x);
  static int S2(const std::bitset<4>& x);

 public:
  static std::vector<std::bitset<8>> GetRandomKeys();
  static std::pair<char, char> Clock(char first, char second, const std::bitset<8>& k);
  static std::pair<char, char> CipherBlock(char X1, char X2, const std::vector<std::bitset<8>>& keys, size_t tacts_amount);
  static std::pair<char, char> DecipherBlock(char X1, char X2, const std::vector<std::bitset<8>>& keys, size_t tacts_amount);
};

#endif //MODELG__BLOCKCRYPTOSYSTEMG_H_
