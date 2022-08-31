#include <iostream>
#include "Bottled Drinks.h"
#include "Beer.h"
#include "Cognac.h"
#include "Lemonade.h"
#include "Milk.h"
#include "Mineral water.h"
#include "Wine.h"

int main() {
  Cognac cognac("Jatone", 0.3, 40, Grade::XO);
  std::cout << cognac.getGrades() << "\n";

  Milk milk("savushkin", 0.99, 0, 12);
  std::cout << milk.getName() << "\n";

  Beer beer("Heineken", 0.5, 2.8, Raw::barley);
  std::cout << beer.getVolume() << "\n";

  Lemonade lemonade("Baikal", 2, 20, Syrup::herbal);
  std::cout << lemonade.getSugar() << "\n";

  Wine wine("Chardonnay", 0.9, 12, Color::white);
  wine.setVolume(0.5);
  std::cout << wine.getVolume() << "\n";

  MineralWater mineral_water("Bonaqua", 1, 0, Type::carbonated);
  mineral_water.setType(Type::semi_carbonated);
  std::cout << mineral_water.getType() << "\n";


  return 0;
}