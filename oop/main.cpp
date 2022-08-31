#include <iostream>
//#define private public

#include "awesomepoint.h"

int main() {
  AwesomePoint point{};
  //AwesomePoint point = AwesomePoint();
  std::cout << point.x << " " << point.y << "\n";

  AwesomePoint point2(3, 18);
  point2.x = 15;
  std::cout << point2.x << " " << point2.y << "\n";


}
