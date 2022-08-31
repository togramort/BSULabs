#include "Soft.h"

Soft::Soft(const std::string &name, double volume, double sugar) : BottledDrinks(name, volume) {
  sugar_ = sugar;
}
double Soft::getSugar() const {
  return sugar_;
}