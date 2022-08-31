#include "Lemonade.h"

Lemonade::Lemonade(const std::string &name, double volume, double sugar, Syrup syrup) : Soft(name, volume, sugar){
  syrup_ = syrup;
}

std::string Lemonade::getSyrup() const {
  switch(syrup_) {
    case Syrup::orange:return "orange";
    case Syrup::lemon:return "lemon";
    case Syrup::vanilla:return "vanilla";
    case Syrup::pear:return "pear";
    case Syrup::herbal:return "herbal";
  }
}
