#ifndef CM_LAB4__BLOCKCRYPTOSYSTEMG_H_
#define CM_LAB4__BLOCKCRYPTOSYSTEMG_H_


#include <bitset>
#include <random>
#include <ctime>
#include <vector>

class CryptoSystem {
 private:
  static int S1(const std::bitset<4>& x);
  static int S2(const std::bitset<4>& x);

 public:
  static std::pair<std::bitset<8>, std::bitset<8>> Clock(std::bitset<8> first, std::bitset<8> second, const std::bitset<8>& k);
  static std::pair<std::bitset<8>, std::bitset<8>> CipherBlock(std::bitset<8> X1, std::bitset<8> X2, const std::vector<std::bitset<8>>& keys, size_t tacts_amount);
};

#endif //CM_LAB4__BLOCKCRYPTOSYSTEMG_H_
