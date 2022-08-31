#ifndef DRINKS__BEER_H_
#define DRINKS__BEER_H_
#include "Booze.h"

enum class Raw {
  barley,
  wheat,
  ginger
};

class Beer : public Booze {
 public:
  Beer(const std::string &name, double volume, double degree, Raw raw);
  [[nodiscard]] std::string getRaw() const;

 private:
  Raw raw_;
};
#endif //DRINKS__BEER_H_
