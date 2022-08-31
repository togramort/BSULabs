#include "Fraction.h"
#include <ostream>

Fraction::Fraction() : numerator_(0), denominator_(1) {}
Fraction::Fraction(long numerator) : numerator_(numerator), denominator_(1) {}
Fraction::Fraction(long numerator, long denominator) : numerator_(numerator) {
  if (denominator == 0) {
    std::cerr << "division by zero" << "\n";
    exit(-1);
  } else {
    denominator_ = denominator;
  }
  Switch();
}

Fraction::Fraction(const Fraction &) = default;
Fraction::Fraction(Fraction &&) noexcept = default;
Fraction &Fraction::operator=(const Fraction &) = default;
Fraction &Fraction::operator=(Fraction &&) noexcept = default;
Fraction::~Fraction() = default;

Fraction Fraction::operator-() const {
  return Fraction(-numerator_, denominator_);
}

Fraction Fraction::operator+(const Fraction &fraction) const {
  long lcm = std::lcm(denominator_, fraction.denominator_);
  long newNumerator = numerator_ * (lcm / denominator_) + fraction.numerator_ * (lcm / fraction.denominator_);
  return Fraction(newNumerator, lcm);
}
Fraction Fraction::operator-(const Fraction &fraction) const {
  long lcm = std::lcm(denominator_, fraction.denominator_);
  long newNumerator = numerator_ * (lcm / denominator_) - fraction.numerator_ * (lcm / fraction.denominator_);
  return Fraction(newNumerator, lcm);
}
Fraction Fraction::operator*(const Fraction &fraction) const {
  long newNumerator = numerator_ * fraction.numerator_;
  long newDenominator = denominator_ * fraction.denominator_;
  return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::operator/(const Fraction &fraction) const {
  long newNumerator = numerator_ * fraction.denominator_;
  long newDenominator = denominator_ * fraction.numerator_;
  return Fraction(newNumerator, newDenominator);
}

Fraction operator+(int number, const Fraction &fraction) {
  return Fraction(number) + fraction;
}
Fraction operator-(int number, const Fraction &fraction) {
  return Fraction(number) - fraction;
}
Fraction operator*(int number, const Fraction &fraction) {
  return Fraction(number) * fraction;
}
Fraction operator/(int number, const Fraction &fraction) {
  return Fraction(number) / fraction;
}

Fraction operator+(const Fraction &fraction, int number) {
  return Fraction(number) + fraction;
}
Fraction operator*(const Fraction &fraction, int number) {
  return Fraction(number) * fraction;
}
Fraction operator-(const Fraction &fraction, int number) {
  return Fraction(number) - fraction;
}
Fraction operator/(const Fraction &fraction, int number) {
  return Fraction(number) / fraction;
}

bool Fraction::operator==(const Fraction &fraction) const {
  return numerator_ == fraction.numerator_ && denominator_ == fraction.denominator_;
}
bool Fraction::operator!=(const Fraction &fraction) const {
  return numerator_ != fraction.numerator_ || denominator_ != fraction.denominator_;
}
bool Fraction::operator>(const Fraction &fraction) const {
  return doubleFraction() > fraction.doubleFraction();
}
bool Fraction::operator>=(const Fraction &fraction) const {
  return doubleFraction() >= fraction.doubleFraction();
}
bool Fraction::operator<(const Fraction &fraction) const {
  return doubleFraction() < fraction.doubleFraction();
}
bool Fraction::operator<=(const Fraction &fraction) const {
  return doubleFraction() <= fraction.doubleFraction();
}

bool operator==(int number, const Fraction &fraction) {
  return double(number) == fraction.doubleFraction();
}
bool operator!=(int number, const Fraction &fraction) {
  return double(number) != fraction.doubleFraction();
}
bool operator>(int number, const Fraction &fraction) {
  return double(number) > fraction.doubleFraction();
}
bool operator>=(int number, const Fraction &fraction) {
  return double(number) >= fraction.doubleFraction();
}
bool operator<(int number, const Fraction &fraction) {
  return double(number) < fraction.doubleFraction();
}
bool operator<=(int number, const Fraction &fraction) {
  return double(number) <= fraction.doubleFraction();
}

bool operator==(const Fraction &fraction, int number) {
  return double(number) == fraction.doubleFraction();
}
bool operator>(const Fraction &fraction, int number) {
  return double(number) > fraction.doubleFraction();
}
bool operator>=(const Fraction &fraction, int number) {
  return double(number) >= fraction.doubleFraction();
}
bool operator<(const Fraction &fraction, int number) {
  return double(number) < fraction.doubleFraction();
}
bool operator<=(const Fraction &fraction, int number) {
  return double(number) <= fraction.doubleFraction();
}
bool operator!=(const Fraction &fraction, int number) {
  return double(number) != fraction.doubleFraction();
}

double Fraction::doubleFraction() const {
  return double(numerator_) / double(denominator_);
}
std::ostream &operator<<(std::ostream &ofs, const Fraction &fraction) {
  ofs << fraction.numerator_ << "\\" << fraction.denominator_;
  return ofs;
}
long Fraction::getNumerator() const {
  return numerator_;
}
void Fraction::setNumerator(long numerator) {
  numerator_ = numerator;
}
long Fraction::getDenominator() const {
  return denominator_;
}
void Fraction::setDenominator(long denominator) {
  denominator_ = denominator;
}
void Fraction::Switch() {
  if (denominator_ < 0) {
    denominator_ *= -1;
    numerator_ *= -1;
  }
  if (numerator_ == 0) {
    denominator_ = 1;
  }
  long gcd = std::gcd(numerator_, denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;
}