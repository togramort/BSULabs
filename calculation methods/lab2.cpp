#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iomanip>

std::chrono::duration<double, std::milli> duration;
std::chrono::high_resolution_clock::time_point start;

std::vector<std::vector<int>> generateMatrix(int n, int a, int b) {
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  std::mt19937 gen(time(nullptr));
  std::uniform_int_distribution<int> distribution(a, b);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrix[i][j] = distribution(gen);
    }
  }
  return matrix;
}

std::vector<double> generateVector(int n, int a, int b) {
  std::vector<double> matrix(n);
  std::mt19937 gen(time(nullptr));
  std::uniform_int_distribution<int> distribution(a, b);
  for (int i = 0; i < n; ++i) {
    matrix[i] = distribution(gen);

  }
  return matrix;
}

std::vector<double> multiplicationVector(std::vector<std::vector<int>> &matrix, std::vector<double> vector) {
  if (matrix[0].size() != vector.size()) {
    std::cerr << "cant multiply this\n";
    exit(-666);
  }
  std::vector<double> result(matrix.size());
  for (int i = 0; i < result.size(); ++i) {
    for (int k = 0; k < matrix[i].size(); ++k) {
      result[i] += matrix[i][k] * vector[k];
    }
  }
  return result;
}


//=========================TASK 1 START=========================
double norm(std::vector<double> vector) {
  double result = 0;
  for (int i = 0; i < vector.size(); ++i) {
    result += std::pow(vector[i], 2);
  }
  return sqrt(result);
}

double findResidual(std::vector<std::vector<int>> &matrix, std::vector<double> vector, double eigenvalue) {
  std::vector<double> diff(vector.size());
  std::vector<double> temp(vector.size());

  temp = multiplicationVector(matrix, vector);

  for (int i = 0; i < diff.size(); ++i) {
    diff[i] = temp[i] - (vector[i] * eigenvalue);
  }

  double result = 0;
  for (int i = 0; i < diff.size(); ++i) {
    result += std::pow(diff[i], 2);
  }
  return sqrt(result);
}

void complexMethod(std::vector<std::vector<int>> &matrix, std::vector<double> vector) {
  std::cout << "lord have mercy, we dont do this reallysuperimpossible stuff\n";
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  duration = end - start;
}

void secondMethod(std::vector<std::vector<int>> &matrix, std::vector<double> vector) {
  int n = 100;
  std::vector<double> originVector = vector;
  std::vector<double> nextVector(vector.size());
  std::vector<double> nextPlusPlusVector(vector.size()); //:)
  std::vector<double> allEigenvalues(n);
  bool secondMethodWork = false;

  int i = 0;
  while (i < 100) {
    nextVector = multiplicationVector(matrix, vector);
    nextPlusPlusVector = multiplicationVector(matrix, nextVector);

    int maxIndex = 0;
    for (int j = 0; j < vector.size() - 1; ++j) {
      if (std::abs(vector[j + 1]) > std::abs(vector[j])) {
        maxIndex = j + 1;
      }
    }

    allEigenvalues[i] = sqrt(std::abs(nextPlusPlusVector[maxIndex] / vector[maxIndex]));

    double euclidNorm;
    euclidNorm = norm(nextPlusPlusVector);
    for (int j = 0; j < vector.size(); ++j) {
      vector[j] = nextPlusPlusVector[j] / euclidNorm;
    }

    std::vector<double> v1(vector.size());
    std::vector<double> v2(vector.size());
    for (int j = 0; j < v1.size(); ++j) {
      v1[j] = nextVector[j] + (vector[j] * allEigenvalues[i]);
      v2[j] = nextVector[j] - (vector[j] * allEigenvalues[i]);
    }

    if (findResidual(matrix, v1, allEigenvalues[i]) < 1e-6) {
      secondMethodWork = true;
      std::cout << "SECOND METHOD WORKED\n";
      std::cout << "iteration: " << i + 1 << "\n";
      std::cout << "eigenvalue: " << allEigenvalues[i] << "\n";
      std::cout << "eigenvector: ( ";
      for (int j = 0; j < v1.size(); ++j) {
        std::cout << v1[j] << " ";
      }
      std::cout << ")\n";

      std::cout << "eigenvalue: " << -allEigenvalues[i] << "\n";
      std::cout << "eigenvector: ( ";
      for (int j = 0; j < v2.size(); ++j) {
        std::cout << v2[j] << " ";
      }
      std::cout << ")\n";
      break;
    }
    ++i;
  }

  if (!secondMethodWork) {
    complexMethod(matrix, originVector);
  } else {
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    duration = end - start;
  }
}

void basicPowerMethod(std::vector<std::vector<int>> &matrix, std::vector<double> vector) {
  start = std::chrono::high_resolution_clock::now();
  int n = 100;
  std::vector<double> originVector = vector;
  std::vector<double> nextVector(vector.size());
  std::vector<double> allEigenvalues(n);
  bool firstMethodWork = false;

  int i = 0;
  while (i < 100) {
    nextVector = multiplicationVector(matrix, vector);
    int maxIndex = 0;
    for (int j = 0; j < vector.size() - 1; ++j) {
      if (std::abs(vector[j + 1]) > std::abs(vector[j])) {
        maxIndex = j + 1;
      }
    }

    allEigenvalues[i] = nextVector[maxIndex] / vector[maxIndex];

    double euclidNorm;
    euclidNorm = norm(nextVector);
    for (int j = 0; j < vector.size(); ++j) {
      vector[j] = nextVector[j] / euclidNorm;
    }

    if (findResidual(matrix, vector, allEigenvalues[i]) < 1e-6) {
      firstMethodWork = true;
      std::cout << "FIRST METHOD WORKED\n";
      std::cout << "iteration: " << i + 1 << "\n";
      std::cout << "eigenvalue: " << allEigenvalues[i] << "\n";
      std::cout << "eigenvector: ( ";
      for (int j = 0; j < vector.size(); ++j) {
        std::cout << vector[j] << " ";
      }
      std::cout << ")\n";
      break;
    }
    ++i;
  }

  if (!firstMethodWork) {
    secondMethod(matrix, originVector);
  } else {
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "time: " << duration.count();
  }
}
//=========================TASK 1 END=========================


//=========================TASK 2 START=========================
//=========================TASK 2 END=========================


//=========================TASK 3 START=========================
double foo(double x) {
  return (((std::pow(x, 9) + M_PI) * cos(log(std::pow(x, 2) + 1))) / exp(std::pow(x, 2))) - (x / 2022);
}

double dFoo(double x) {
  return ((2 * exp(-std::pow(x, 2)) * (std::pow(x, 9) + M_PI) * x * sin(log(std::pow(x, 2) + 1))) / (std::pow(x, 2) + 1)) -
          2 * exp(-std::pow(x, 2)) * (std::pow(x, 9) + M_PI) * x * cos(log(std::pow(x, 2) + 1)) +
          9 * exp(-std::pow(x, 2)) * std::pow(x, 8) * cos(log(std::pow(x, 2) + 1)) - (1 / 2022);
}

int counter2 = 0;
double newton (double x) {
  double left = 0;
  while(std::abs(left - x) > 1e-10) {
    left = x;
    x = left - (foo(left) / dFoo(left));
    ++counter2;
  }
  return x;
}

int counter1 = 0;
double binary(double a, double b) {
  int i = 0;
  while ((std::fabs(b - a) / 2) > 1e-4) {
    i++;
    double m = (a + b) / 2;
    double yA, yB;
    yA = foo(a);
    yB = foo(b);
    if (std::fabs(yA) - std::fabs(yB) >= 0) {
      a = m;
    } else {
      b = m;
    }
    ++counter1;
  }
  return a;
}

void task3() {
  std::vector<double> sections = {-2, -1.7, -1.5, -1, 1.5, 2};

  for (int i = 0; i < sections.size() - 1; i = i + 2) {
    double left, answer;
    left = binary(sections[i], sections[i + 1]);
    std::cout << "left = " << std::setprecision(10) << left << "\n";
    answer = newton(left);
    std::cout << "answer = " << std::setprecision(10) << answer << "\n";
  }
  std::cout << "iterations by bisection: " << counter1 << "\n";
  std::cout << "iterations by newton: " << counter2 << "\n";
}
//=========================TASK 3 END=========================

int main() {
/*  std::vector<std::vector<int>> matrixGen = {{-7, 12, 5}, {-5, 10, 5}, {-12, 12, 10}};

  std::vector<double> vectorGen = {1, 3, 0};

  std::vector<std::vector<int>> matrixGen = {{18, -8, -20}, {20, -10, -20}, {8, -8, -10}};*/

/*  //task1
  std::vector<double> vectorGen = generateVector(50, 0, 2);
  std::vector<std::vector<int>> matrixGen = generateMatrix(50, 0, 9);
  std::cout << "randomly generated vector:\n";
  std::cout << "vector:\n( ";
  for (int i = 0; i < vectorGen.size(); ++i) {
    std::cout << vectorGen[i] << " ";
  }
  std::cout << " )\n";
  std::cout << "matrix\n";
  std::cout << "randomly generated matrix\n";
  for (int i = 0; i < matrixGen.size(); ++i) {
    for (int j = 0; j < matrixGen.size(); ++j) {
      std::cout << matrixGen[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  basicPowerMethod(matrixGen, vectorGen);*/

  //task3();

  return 0;
}