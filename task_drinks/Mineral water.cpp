#include "Mineral water.h"

MineralWater::MineralWater(const std::string &name, double volume, double sugar, Type type) : Soft(name, volume, sugar) {
  type_ = type;
}

void MineralWater::setType(Type type) {
  type_ = type;
}

std::string MineralWater::getType() {
  switch (type_) {
    case Type::carbonated:return "carbonated";
    case Type::non_carbonated:return "non-carbonated";
    case Type::semi_carbonated:return "semi-carbonated";
  }
}