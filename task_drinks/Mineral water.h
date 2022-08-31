#ifndef DRINKS__MINERAL_WATER_H_
#define DRINKS__MINERAL_WATER_H_
#include "Soft.h"

enum class Type {
  carbonated,
  non_carbonated,
  semi_carbonated
};

class MineralWater : public Soft {
 public:
  MineralWater(const std::string& name, double volume, double sugar, Type type);
  std::string getType();
  void setType(Type type);

 private:
  Type type_;
};

#endif //DRINKS__MINERAL_WATER_H_