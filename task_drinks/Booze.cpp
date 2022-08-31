#include "Booze.h"

Booze::Booze(const std::string &name, double volume, double degree) : BottledDrinks(name, volume) {
  degree_ = degree;
}
double Booze::getDegree() const {
  return degree_;
}
void Booze::setDegree(double degree) {
  degree_ = degree;
}