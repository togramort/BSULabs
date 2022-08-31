#include  <stdexcept>
#include "Bottled Drinks.h"

BottledDrinks::BottledDrinks(const std::string &name, double volume) {
  name_ = name;
  volume_ = volume;
}
std::string BottledDrinks::getName() const {
  return name_;
}
double BottledDrinks::getVolume() const {
  return volume_;
}
void BottledDrinks::setVolume(double volume) {
  if (volume < 0) {
    throw std::runtime_error("volume cant be negative!");
  }
  volume_ = volume;
}