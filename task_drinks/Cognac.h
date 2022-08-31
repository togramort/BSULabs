#ifndef DRINKS__COGNAC_H_
#define DRINKS__COGNAC_H_
#include "Booze.h"

enum class Grade{
  VS,
  Superior,
  VSOP,
  VVSOP,
  XO
};

class Cognac : public Booze {
 public:
  Cognac(const std::string &name, double volume, double degree, Grade grades);
  [[nodiscard]] std::string getGrades() const;

 private:
  Grade grades_;
};

#endif //DRINKS__COGNAC_H_