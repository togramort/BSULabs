#ifndef DRINKS__LEMONADE_H_
#define DRINKS__LEMONADE_H_
#include "Soft.h"

enum class Syrup {
  orange,
  lemon,
  vanilla,
  pear,
  herbal
};

class Lemonade : public Soft {
 public:
  Lemonade(const std::string &name, double volume, double sugar, Syrup syrup);
  [[nodiscard]] std::string getSyrup() const;

 private:
  Syrup syrup_;
};

#endif //DRINKS__LEMONADE_H_