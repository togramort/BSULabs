#ifndef DRINKS__BOTTLED_DRINKS_H_
#define DRINKS__BOTTLED_DRINKS_H_
#include <string>

class BottledDrinks {
 public:
  BottledDrinks(const std::string &name, double volume);
  [[nodiscard]] virtual std::string getName() const;
  [[nodiscard]] virtual double getVolume() const;
  virtual void setVolume(double volume);
  BottledDrinks(const BottledDrinks &drinks) = delete;
  BottledDrinks(BottledDrinks &&drink) = delete;
  BottledDrinks &operator=(const BottledDrinks &drink) = delete;
  BottledDrinks &operator=(BottledDrinks &&drink) = delete;
  virtual ~BottledDrinks() = default;

 private:
  std::string name_;
  double volume_;
};
#endif //DRINKS__BOTTLED_DRINKS_H_