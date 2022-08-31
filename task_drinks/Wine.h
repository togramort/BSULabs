#ifndef DRINKS__WINE_H_
#define DRINKS__WINE_H_
#include "Booze.h"

enum class Color {
  red,
  white,
  pink
};

class Wine : public Booze {
 public:
  Wine(const std::string &name, double volume, double degree, Color color_);
  [[nodiscard]] std::string getColor() const;

 private:
  Color color_;
};

#endif //DRINKS__WINE_H_