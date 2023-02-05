#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<double> roots = {-0.7745966692, 0, 0.7745966692};
double a = 0.35, b = 1.35;

double get_integral() {
  double t1 = 0.65 * sin(b) - 0.35 * exp(-b);
  double t2 = 0.65 * sin(a) - 0.35 * exp(-a);
  return t1 - t2;
}

int getN () {
  return ceil(std::pow(((std::pow(b - a, 5) * 0.857233) / (180 * 0.00001)), 1 / 4.0));
}

double function(double x) {
  return (0.35 * exp(-x)) + (0.65 * cos(x));
}

std::vector<double> get_nodes_for_simpson(double h, int N) {
  std::vector<double> nodes(N + 1);
  nodes[0] = a;
  for (int i = 1; i <= N; ++i) {
    nodes[i] = nodes[i - 1] + h;
  }
  return nodes;
}

double simpson(double h, int N, std::vector<double> nodes) {
  double res = function(nodes[0]) + function(nodes[N]);
  double temp = 0;
  for (int i = 1; i <= N - 1; i += 2) {
    temp += function(nodes[i]);
  }
  temp = 4 * temp;
  res += temp;
  temp = 0;
  for (int i = 2; i <= N - 2; i += 2) {
    temp += function(nodes[i]);
  }
  temp = 2 * temp;
  res += temp;
  return res * h / 3;
}

double getR(double h, int N) {
  return (std::pow(b - a, 5) * 0.857233) / (180 * std::pow(N, 4));
}
////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double>getnodes() {
  std::vector<double> nodes2 (roots.size());
  for (int i = 0; i < nodes2.size(); ++i) {
    nodes2[i] = (roots[i] * (b - a) / 2) + ((b + a) / 2);
  }
  return nodes2;
}

double legendre_first_derivative(double x) {
  return ((15.0 * std::pow(x, 2.0)) - 3.0) / 2.0;
}

std::vector<double> find_c() {
  std::vector<double> Ck(3);
  for (int i = 0; i < Ck.size(); ++i) {
    Ck[i] = 2 / ((1 - std::pow(roots[i], 2)) * std::pow(legendre_first_derivative(roots[i]), 2));
  }
  return Ck;
}

double integral_gauss(std::vector<double> Ck, std::vector<double> nodes2) {
  double res = 0;
  for (int i = 0; i < 3; ++i) {
    res += Ck[i] * function(nodes2[i]);
  }
  return (b - a) / 2 * res;
}

int factorial(int i) {
  if (i == 0) return 1;
  else return i * factorial(i - 1);
}

double theoretical_remainder_gauss() {
  int n = 2;
  double max_derivative = 0.364282;
  //double max_derivative = 0.715819;
  double part_one = std::pow((b - a) / 2, 2 * n + 3);
  double part_two = std::pow(2, 2 * n + 3) / ((2 * n + 3) * factorial(2 * n + 2));
  double factorial1 = factorial(n + 1);
  double factorial2 = factorial(2 * n + 2);
  double part_three = std::pow(std::pow(factorial1, 2) / factorial2, 2);
  return part_one * part_two * part_three * max_derivative;
}

int main() {
  double integral = get_integral();
  std::cout << std::setprecision(16) << "\nsimple integral: " << integral;
  int N = getN();
  std::cout << "\nN = " << N;
  double h = 1.0 / N;
  //h = h - 0.0000000000000007;
  std::cout << "\nh = " << h;
  std::vector<double> nodes_simpson = get_nodes_for_simpson(h, N);
  std::cout << "\nnodes for simpson:\n";
  for (int i = 0; i < nodes_simpson.size(); ++i) {
    std::cout << nodes_simpson[i] << " ";
  }
  double integral_simpson = simpson(h, N, nodes_simpson);
  //integral_simpson = 0.5672434999483599;
  std::cout << std::setprecision(16) << "\nintegral simpson = " << integral_simpson;
  double R_sost = getR(h , N);
  std::cout << "\nR sost " << R_sost;
  std::cout << "\nhehe simpson: " << integral - integral_simpson;


  std::vector<double> nodes = getnodes();
  std::cout << "\nnewnodes ";
  for (int i = 0; i < 3; ++i) {
    std::cout << nodes[i] << " ";
  }
  std::vector<double> Ck = find_c();
  std::cout << "\nCkkkk ";
  for (int i = 0; i < Ck.size(); ++i) {
    std::cout << Ck[i] << " ";
  }
  double I = integral_gauss(Ck, nodes);
  double R = theoretical_remainder_gauss();
  std::cout << std::setprecision(15) << "\nintegral gauss: " << I;
  std::cout << "\nremainder gauss: " << R;
  std::cout << "\nhehe gauss: " << integral - I;
  std::cout << "\ntesstttt " << 0.323965382781506 - 0.323965382781506;
  return 0;
}
//0.5672434999483599