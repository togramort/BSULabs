#include <iostream>
#include "Fraction.h"

int main() {
  long numerator1, denominator1, numerator2, denominator2;
  std::cout << "enter the first and the second fraction" << "\n";
  std::cin >> numerator1 >> denominator1 >> numerator2 >> denominator2;
  Fraction fraction1(numerator1, denominator1);
  Fraction fraction2(numerator2, denominator2);
  std::cout << "the first fraction = " << fraction1.getNumerator() << "\\" << fraction1.getDenominator() << "\n";
  std::cout << "the second fraction = " << fraction2.getNumerator() << "\\" << fraction2.getDenominator() << "\n";
  int number;
  std::cout << "enter the integer number" << "\n";
  std::cin >> number;

  std::cout << "-fraction 1 = " << -fraction1 << "\n";
  std::cout << "fraction 1 + fraction 2 = " << fraction1 + fraction2 << "\n";
  std::cout << "fraction 1 * fraction 2 = " << fraction1 * fraction2 << "\n";
  std::cout << "fraction 1 - fraction 2 = " << fraction1 - fraction2 << "\n";
  std::cout << "fraction 1 / fraction 2 = " << fraction1 / fraction2 << "\n";

  std::cout << "fraction 1 = fraction 2 - " << (fraction1 == fraction2) << "\n";
  std::cout << "fraction 1 > fraction 2 - " << (fraction1 > fraction2) << "\n";
  std::cout << "fraction 1 >= fraction 2 - " << (fraction1 >= fraction2) << "\n";
  std::cout << "fraction 1 < fraction 2 - " << (fraction1 < fraction2) << "\n";
  std::cout << "fraction 1 <= fraction 2 - " << (fraction1 <= fraction2) << "\n";
  std::cout << "fraction 1 != fraction 2 - " << (fraction1 != fraction2) << "\n";

  std::cout << "number + fraction 1 = " << number + fraction1 << "\n";
  std::cout << "number * fraction 1 = " << number * fraction1 << "\n";
  std::cout << "number - fraction 1 = " << number - fraction1 << "\n";
  std::cout << "number / fraction 1 = " << number / fraction1 << "\n";

  std::cout << "number = fraction 1 - " << (number == fraction1) << "\n";
  std::cout << "number > fraction 1 - " << (number > fraction1) << "\n";
  std::cout << "number >= fraction 1 - " << (number >= fraction1) << "\n";
  std::cout << "number < fraction 1 - " << (number < fraction1) << "\n";
  std::cout << "number <= fraction 1 - " << (number <= fraction1) << "\n";
  std::cout << "number != fraction 1 - " << (number != fraction1) << "\n";

  std::cout << "fraction 1 + number = " << fraction1 + number << "\n";
  std::cout << "fraction 1 * number = " << fraction1 + number << "\n";
  std::cout << "fraction 1 - number = " << fraction1 + number << "\n";
  std::cout << "fraction 1 / number = " << fraction1 + number << "\n";

  std::cout << "fraction 1 = number - " << (fraction1 == number) << "\n";
  std::cout << "fraction 1 > number - " << (fraction1 > number) << "\n";
  std::cout << "fraction 1 >= number - " << (fraction1 >= number) << "\n";
  std::cout << "fraction 1 < number - " << (fraction1 < number) << "\n";
  std::cout << "fraction 1 <= number - " << (fraction1 <= number) << "\n";
  std::cout << "fraction 1 != number - " << (fraction1 != number) << "\n";

  std::cout << "simplified fraction 1 = " << fraction1.doubleFraction();
  return 0;
}