#ifndef FRACTION__FRACTION_H_
#define FRACTION__FRACTION_H_
#include <numeric>
#include <iostream>
#endif

class Fraction {
 public:
  Fraction();
  explicit Fraction(long numerator);
  Fraction(long numerator, long denominator);

  Fraction(const Fraction &);
  Fraction(Fraction &&) noexcept;
  Fraction &operator=(const Fraction &);
  Fraction &operator=(Fraction &&) noexcept;
  ~Fraction();

  Fraction operator-() const;

  Fraction operator+(const Fraction &fraction) const;
  Fraction operator-(const Fraction &fraction) const;
  Fraction operator*(const Fraction &fraction) const;
  Fraction operator/(const Fraction &fraction) const;

  friend Fraction operator+(int number, const Fraction &fraction);
  friend Fraction operator-(int number, const Fraction &fraction);
  friend Fraction operator*(int number, const Fraction &fraction);
  friend Fraction operator/(int number, const Fraction &fraction);

  friend Fraction operator+(const Fraction &fraction, int number);
  friend Fraction operator*(const Fraction &fraction, int number);
  friend Fraction operator-(const Fraction &fraction, int number);
  friend Fraction operator/(const Fraction &fraction, int number);

  bool operator==(const Fraction &fraction) const;
  bool operator!=(const Fraction &fraction) const;
  bool operator>(const Fraction &fraction) const;
  bool operator>=(const Fraction &fraction) const;
  bool operator<(const Fraction &fraction) const;
  bool operator<=(const Fraction &fraction) const;

  friend bool operator==(int number, const Fraction &fraction);
  friend bool operator!=(int number, const Fraction &fraction);
  friend bool operator>(int number, const Fraction &fraction);
  friend bool operator>=(int number, const Fraction &fraction);
  friend bool operator<(int number, const Fraction &fraction);
  friend bool operator<=(int number, const Fraction &fraction);

  friend bool operator==(const Fraction &fraction, int number);
  friend bool operator>(const Fraction &fraction, int number);
  friend bool operator>=(const Fraction &fraction, int number);
  friend bool operator<(const Fraction &fraction, int number);
  friend bool operator<=(const Fraction &fraction, int number);
  friend bool operator!=(const Fraction &fraction, int number);

  double doubleFraction() const;

  friend std::ostream &operator<<(std::ostream &, const Fraction &fraction);

  long getNumerator() const;
  void setNumerator(long numerator);
  long getDenominator() const;
  void setDenominator(long denominator);

 private:
  long numerator_, denominator_;
  void Switch();
};