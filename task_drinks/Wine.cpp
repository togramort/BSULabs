#include "Wine.h"

Wine::Wine(const std::string &name, double volume, double degree, Color color) : Booze(name, volume, degree) {
  color_ = color;
}

std::string Wine::getColor() const {
  switch (color_) {
    case Color::red:return "red";
    case Color::white:return "white";
    case Color::pink:return "pink";
  }
}
