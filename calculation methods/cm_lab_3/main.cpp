#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double function (double x, double y) {
  return (y / x) + x * (-0.35 * std::pow(exp(x), -1) - 0.65 * sin(x));
}

std::vector<double> getX() {
  std::vector<double> nodes(11);
  double h = 0.1;
  double x0 = 0.35;
  for (int i = 0; i < 11; ++i) {
    nodes[i] = x0;
    x0 += h;
  }
  return nodes;
}

std::vector<double> euler(std::vector<double> x) {
  double h = 0.1;
  std::vector<double> res (11);
  res[0] = 0.30003158316332;
  for (int i = 1; i < 11; ++i) {
    res[i] = res[i - 1] + h * function(x[i - 1], res[i - 1]);
  }
  return res;
}

double get_phi0(double x, double y) {
  double h = 0.1;
  return h * function(x, y);
}

double get_phi1(double x, double y) {
  double h = 0.1, alpha = 1.0, beta = 1.0;
  return h * function(x + alpha * h, y + beta * get_phi0(x, y));
}

std::vector<double> runge(std::vector<double> x) {
  double a1 = 1.0 / 2, a0 = 1.0 / 2;
  std::vector<double> res (11);
  res[0] = 0.30003158316332;
  for (int i = 1; i < 11; ++i) {
    res[i] = res[i - 1] + a0 * get_phi0(x[i - 1], res[i - 1]) + a1 * get_phi1(x[i - 1], res[i - 1]);
  }
  return res;
}

std::vector<double> koshi(std::vector<double> nodes) {
  std::vector<double> y (11);
  for (int i = 0; i < 11; ++i) {
    y[i] = nodes[i] * (0.35 * exp(-nodes[i]) + 0.65 * cos(nodes[i]) - 3.01346e-15);
  }
  return y;
}

int main() {
  std::vector<double> nodes = getX();
  for (int i = 0; i < 11; ++i) {
    std::cout << nodes[i] << " ";
  }
  std::cout << "\n";
  std::vector<double> y = euler(nodes);
  for (int i = 0; i < 11; ++i) {
    std::cout << std::setprecision(14) << y[i] << " ";
  }
  std::cout << "\n\n";
  std::vector<double> runges = runge(nodes);
  for (int i = 0; i < 11; ++i) {
    std::cout << runges[i] << " ";
  }
  std::cout << "\n\n";
  std::vector<double> exac = koshi(nodes);
  for (int i = 0; i < 11; ++i) {
    std::cout << exac[i] << " ";
  }
  return 0;
}