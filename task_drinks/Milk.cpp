#include "Milk.h"

Milk::Milk(const std::string &name, double volume, double sugar, double fattiness) : Soft(name, volume, sugar) {
  fattiness_ = fattiness;
}
double Milk::getFattiness() const {
  return fattiness_;
}