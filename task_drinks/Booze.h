#ifndef DRINKS__BOOZE_H_
#define DRINKS__BOOZE_H_
#include "Bottled Drinks.h"

class Booze : public BottledDrinks {
 public:
  Booze(const std::string &name, double volume, double degree);
  [[nodiscard]] virtual double getDegree() const;
  virtual void setDegree(double degree);
  Booze(const Booze &drinks) = delete;
  Booze(Booze &&drink) = delete;
  Booze &operator=(const Booze &drink) = delete;
  Booze &operator=(Booze &&drink) = delete;
  ~Booze() override = default;

 private:
  double degree_;
};

#endif //DRINKS__BOOZE_H_
