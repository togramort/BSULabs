#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

int n = 10;
int my_number = 5;
double h = 1.0 / 10.0;
double alpha = 0.1 + 0.05 * my_number;
int degree = 5;

std::vector<double> calculate_nodes() {
  std::vector<double> nodes (11);
  for (int i = 0; i <= n; ++i) {
    nodes[i] = alpha + i * h;
  }

  std::cout << "\nnodes";
  for (double i : nodes) {
    std::cout << std::setprecision(18) << i << " ";
  }
  return nodes;
}

std::vector<double> calculate_functions(std::vector<double>& nodes) {
  std::vector<double> function(11);
  for (int i = 0; i <= n; ++i) {
    function[i] = alpha * exp(-nodes[i]) + (1 - alpha) * cos(nodes[i]);
  }

  std::cout << "\nfunc: ";
  for (double i : function) {
    std::cout << std::setprecision(18) << i << " ";
  }
  return function;
}

std::vector<double> calculate_restore_nodes(std::vector<double>& nodes) {
  std::vector<double> restore_nodes(3);
  restore_nodes[0] = nodes[0] + 2.0 / 3.0 * h;
  restore_nodes[1] = nodes[n / 2] + 1.0 / 2.0 * h;
  restore_nodes[2] = nodes[n] - 1.0 / 3.0 * h;

  std::cout << "\nrestore nodes: ";
  for (double i : restore_nodes) {
    std::cout << std::setprecision(18) << i << " ";
  }
  return restore_nodes;
}

std::vector<double> calculate_restore_functions(std::vector<double>& restore_nodes) {
  std::vector<double> restore_functions(3);
  for (int i = 0; i < restore_functions.size(); ++i) {
    restore_functions[i] = alpha * exp(-restore_nodes[i]) + (1 - alpha) * cos(restore_nodes[i]);
  }

  std::cout << "\nrestore func: ";
  for (double i : restore_functions) {
    std::cout << std::setprecision(18) << i << " ";
  }
  return restore_functions;
}

double calculate_lagrange(std::vector<double>& functions, std::vector<double>& nodes, double x) {
  double lagrange = 0;
  double temp = 1;
  for (int i = 0; i <= n; ++i) {
    temp *= functions[i];
    for (int j = 0; j <= n; ++j) {
      if (j != i) {
        temp *= (x - nodes[j]) / (nodes[i] - nodes[j]);
      }
    }
    lagrange += temp;
    temp = 1;
  }
  std::cout << "\nlagrange: " << lagrange;
  return lagrange;
}

double calculate_omega(double x, std::vector<double>& nodes) {
  double omega = 1;
  for (int i = 0; i <= n; ++i) {
    omega *= x - nodes[i];
  }
  std::cout << "\nomega: " << omega;
  return omega;
}

std::vector<std::vector<double>> calculate_table_of_differences(std::vector<double>& functions, std::vector<double>& nodes) {
  std::vector<std::vector<double>> table(11, std::vector<double>(12,0));
  for (int i = 0; i < table.size(); ++i) {
    table[i][0] = nodes[i];
    table[i][1] = functions[i];
  }

  for (int i = 0; i < table.size(); ++i) {
    table[i].resize(table.size() + 1 - i);
  }

  for (int j = 2; j < table[0].size(); ++j) {
    for (int i = 0; i < table.size() - j + 1; ++i) {
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (nodes[j - 1 + i] - nodes[i]);
    }
  }

  std::cout << "\ntable of diff 1\n";
  for (int i = 0; i < table.size(); ++i) {
    for (int j = 0; j < table[i].size(); ++j) {
      std::cout << table[i][j] << "\t";
    }
    std::cout << "\n";
  }
  return table;
}

double calculate_error(double x, double function, std::vector<std::vector<double>>& table, std::vector<double>& nodes) {
  double last_difference = function;
  for (int i = table.size() - 1; i >= 0; --i) {
    last_difference = (last_difference - table[i][table.size() - i]) / (x - nodes[i]);
  }
  std::cout << "\nlast diff: " << last_difference;
  return calculate_omega(x, nodes) * last_difference;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<double>> build_table_of_differences(std::vector<double>& functions) {
  int number_of_nodes = 4;
  std::vector<std::vector<double>> table(number_of_nodes, std::vector<double>(number_of_nodes,0));
  for (int i = 0; i < table.size(); ++i) {
    table[i].resize(table.size() - i);
    table[i][0] = functions[i];
  }

  for (int j = 1; j < table[0].size(); ++j) {
    for (int i = 0; i < table.size() - j; ++i) {
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]);
    }
  }

  std::cout << "\ntable of diff 2:\n";
  for (int i = 0; i < table.size(); ++i) {
    for (int j = 0; j < table[i].size(); ++j) {
      std::cout << table[i][j] << "\t";
    }
    std::cout << "\n";
  }
  return table;
}

double calculate_newton(std::vector<std::vector<double>>& table, std::vector<double>& nodes, double x) {
  double result = table[0][0];
  double t = (x - nodes[0]) / h;
  int number_of_nodes = 4;
  double temp = 1;
  for (int i = 0; i < number_of_nodes - 1; ++i) {
    temp *= (t - i) / (i + 1);
    result += temp * table[0][i + 1];
  }
  return result;
}

int factorial(const int p) {
  int f = 1;
  for (int i = 1; i <= p; ++i) {
    f *= i;
  }
  return f;
}

double calculate_remainder(std::vector<double>& functions, std::vector<double>& nodes, double x) {
  int number_of_nodes = 4;
  int denominator = factorial(number_of_nodes);
  double t = (x - nodes[0]) / h;
  h = std::pow(h, 4);
  double result = 1;
  for (int i = 0; i < number_of_nodes; ++i) {
    result *= t - i;
  }
  return h * result / denominator * functions[0];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> calculate_chebyshev() {
  double a = alpha, b = alpha + 1;
  std::vector<double> chebyshev_nodes(n + 1);
  for (int i = 0; i <= n; ++i) {
    chebyshev_nodes[i] = ((a + b) / 2) + ((b - a) / 2 * cos(((2.0 * (double)i + 1.0) / (2.0 * (double)n + 2.0)) * M_PI));
  }
  std::cout << "\ncheb: ";
  for(double i: chebyshev_nodes) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  return chebyshev_nodes;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> build_and_solve_matrix(std::vector<double>& functions, std::vector<double>& nodes) {
  int m = 10;
  n = 5;
  std::vector<std::vector<double>> matrix (degree + 1, std::vector<double>(degree + 1, 0));
  std::vector<double>f(degree + 1, 0);
  for (int j = 0; j <= degree; ++j) {
    for (int k = 0; k <= degree; ++k) {
      for (int i = 0; i <= m; ++i) {
        matrix[j][k] += std::pow(nodes[i], j) * std::pow(nodes[i], k);
      }
    }
  }

  for (int j = 0; j <= degree; ++j) {
    for (int i = 0; i <= m; ++i) {
      f[j] += std::pow(nodes[i], j) * functions[i];
    }
  }

  Eigen::MatrixXd a(degree + 1, degree + 1);

  for (int i = 0; i < degree + 1; ++i) {
    for (int j = 0; j < degree + 1; ++j) {
      a(i, j) = matrix[i][j];
    }
  }

  Eigen::VectorXd b = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(f.data(), f.size());
  Eigen::VectorXd x = a.colPivHouseholderQr().solve(b);
  std::cout << "The solution is:\n" << x << std::endl;

  std::vector<double> answer(degree + 1);
  for (int i = 0; i <= degree; ++i) {
    answer[i] = x(i);
  }
  return answer;
}

double calculate_phi(double x, std::vector<double>& alphas) {
  double result = 0;
  for (int i = 0; i <= degree; ++i) {
    result += alphas[i] * std::pow(x, i);
  }
  std::cout << "\nphi: " << result;
  return result;
}

double calculate_phi_error(std::vector<double>& alphas, std::vector<double>& functions, std::vector<double>& nodes) {
  double error = 0;
  int m = 10;
  for (int i = 0; i <= m; ++i) {
    error += std::pow(calculate_phi(nodes[i], alphas) - functions[i], 2);
  }
  return sqrt(error);
}

int main() {
  std::vector<double> nodes;
  std::vector<double> restore_nodes;
  std::vector<double> functions;
  std::vector<double> restore_functions;
  double lagrange;
  double omega;
  nodes = calculate_nodes();
  functions = calculate_functions(nodes);
  restore_nodes = calculate_restore_nodes(nodes);
  //0.416666666666666667 0.9 1.3166666666666667
  restore_functions = calculate_restore_functions(restore_nodes);
  //0.825122213856145148 0.546345860285141538 0.2572215597635669

/*  //for task 1
  //omega = calculate_omega(0.41666666666666667, nodes);
  lagrange = calculate_lagrange(functions, nodes, 0.416666666666666667);

  std::vector<std::vector<double>> table;
  table = calculate_table_of_differences(functions, nodes);
  double error = calculate_error(0.416666666666666667, 0.825122213856145148, table, nodes);
  std::cout << "\nerror: " << error;
  std::cout << "\nhehe: " << 0.825122213856145148 - lagrange;*/

  //for task 2
/*  std::vector<std::vector<double>> table2;
  table2 = build_table_of_differences(functions);
  double newton = calculate_newton(table2, nodes, 0.41666666666666667);
  double remainder = calculate_remainder(functions, nodes, 0.41666666666666667);
  std::cout << "\n\nnewton: " << newton << "\nerror: " << remainder;
  std::cout << "\nhehe: " << 0.825122213856145148 - 0.825124492641398533;*/

/*  //for task 3
  std::vector<double> cheb_nodes;
  std::vector<double> cheb_funcs;

  cheb_nodes = calculate_chebyshev();
  cheb_funcs = calculate_functions(cheb_nodes);

  std::cout << "\ncheb_func";
  for (int i = 0; i < cheb_funcs.size(); ++ i) {
    std::cout << cheb_funcs[i] << " ";
  }
  std::cout << "\n";

  lagrange = calculate_lagrange(cheb_funcs, cheb_nodes, 0.416666666666666667);
  std::vector<std::vector<double>> table;
  table = calculate_table_of_differences(cheb_funcs, cheb_nodes);
  double error = calculate_error(0.416666666666666667, 0.825122213856145148, table, cheb_nodes);
  std::cout << "\nerror: " << error;
  std::cout << "\nhehe: " << 0.825122213856145148 - lagrange;*/

  //for task 4
/*  std::vector<double> alphas;
  alphas = build_and_solve_matrix(functions, nodes);
  calculate_phi(1.31666666666666667, alphas);
  double error = calculate_phi_error(alphas, functions, nodes);*/
  return 0;
}