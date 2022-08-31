#ifndef DRINKS__MILK_H_
#define DRINKS__MILK_H_
#include "Soft.h"

class Milk : public Soft {
 public:
  Milk (const std::string& name, double volume, double sugar, double fattiness);
  [[nodiscard]] double getFattiness() const;

 private:
  double fattiness_;
};

#endif //DRINKS__MILK_H_