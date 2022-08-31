#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <windows.h>

std::chrono::duration<double, std::milli> duration_inverse;
std::chrono::duration<double, std::milli> duration_gauss;
std::chrono::duration<double, std::milli> duration_LUP;
std::chrono::duration<double, std::milli> duration_LUx;
std::chrono::duration<double, std::milli> duration_root;
std::chrono::duration<double, std::milli> duration_relax;
int count_and_relax;

std::vector<std::vector<double>> task1() {
  int n = 256;
  std::vector<std::vector<double>> matrix(n, std::vector<double>(n));

  std::mt19937 gen(time(nullptr));
  std::uniform_real_distribution<double> distribution(-std::pow(2, 5 / 4), std::pow(2, 5 / 4) - 1);

  for (int i = 0; i < n; ++i) {
    double diag = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        double temp;
        temp = distribution(gen);
        matrix[i][j] = temp;
        matrix[j][i] = temp;
        diag += std::abs(temp);
      }
    }
    matrix[i][i] = diag + 1;
  }

/*  std::cout << "\n-------------------- TASK 1 - RANDOM MATRIX --------------------\n";
  std::cout << "matrix w\\ random numbers:\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << matrix[i][j] << "\t\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return matrix;
}

std::pair<std::vector<double>, std::vector<double>> task2(std::vector<std::vector<double>> matrix) {
  std::vector<double> y(matrix.size());
  std::mt19937 gen(time(nullptr));
  std::uniform_real_distribution<double> distribution(-std::pow(2, 5 / 4), std::pow(2, 5 / 4) - 1);
  for (int i = 0; i < y.size(); ++i) {
    y[i] = distribution(gen);
  }

  std::vector<double> b(y.size());
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < y.size(); ++j) {
      b[i] += matrix[i][j] * y[j];
    }
  }

/*  std::cout << "\n-------------------- TASK 2 - VECTOR B - RANDOM Y --------------------\n";
  std::cout << "vector y is: \n";
  for (int i = 0; i < y.size(); ++i) {
    std::cout << y[i] << "\n";
  }

  std::cout << "vector b is: \n";
  for (int i = 0; i < b.size(); ++i) {
    std::cout << b[i] << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return std::make_pair(b, y);
}

double task3(std::vector<std::vector<double>> matrix) {
  std::vector<std::vector<double>> inverse = matrix;
  std::vector<std::vector<double>> identity(matrix.size(), std::vector<double>(matrix.size()));
  for (int i = 0; i < identity.size(); ++i) {
    identity[i][i] = 1;
  }

  //делим каждую строку на диагональный элемент и отнимаем ее*первый эл-т др строки от всех нижних (зануляем столбцы)
  std::chrono::high_resolution_clock::time_point start_inverse = std::chrono::high_resolution_clock::now();
   for (int i = 0; i < inverse.size(); ++i) {
     if (std::abs(inverse[i][i]) < 1e-16) {
       std::cout << "kinda bad inverse sorry :(\n";
       exit(-6);
     }

     double first_in_row = inverse[i][i];
     for (int j = 0; j < inverse[i].size(); ++j) {
       inverse[i][j] /= first_in_row;
       identity[i][j] /= first_in_row;
     }

     for (int k = i + 1; k < inverse.size(); ++k) {
       int j = i;

       first_in_row = 0;
       if (inverse[k][j] > 0) {
         first_in_row -= inverse[k][j];
       } else {
         first_in_row = std::abs(inverse[k][j]);
       }

       j = 0;
       while (j < inverse.size()) {
         inverse[k][j] += inverse[i][j] * first_in_row;
         identity[k][j] += identity[i][j] * first_in_row;
         ++j;
       }
     }
   }

  //обратный ход
  for (int i = inverse.size() - 1; i > 0; --i) {
    for (int k = i - 1; k > -1; --k) {
      int j = i;
      double last_in_row = 0;
      if (inverse[k][j] > 0) {
        last_in_row -= inverse[k][j];
      } else {
        last_in_row = std::abs(inverse[k][j]);
      }

      j = inverse.size() - 1;
      while (j > -1) {
        inverse[k][j] += last_in_row * inverse[i][j];
        identity[k][j] += last_in_row * identity[i][j];
        --j;
      }
    }
  }

  std::chrono::high_resolution_clock::time_point end_inverse = std::chrono::high_resolution_clock::now();
  duration_inverse = end_inverse - start_inverse;
  duration_inverse.count();

  double max_sum = 0, max_sum_inverse = 0;
  for (int i = 0; i < matrix.size(); ++i) {
    double sum = 0, sum_inverse = 0;
    for (int j = 0; j < matrix[i].size(); ++j) {
      sum += std::abs(matrix[i][j]);
      sum_inverse += std::abs(identity[i][j]);
    }

    if (sum > max_sum) {
      max_sum = sum;
    }
    if (sum_inverse > max_sum_inverse) {
      max_sum_inverse = sum_inverse;
    }
  }

/*  std::cout << "\n-------------------- TASK 3 - CONDITION NUMBER --------------------\n";
  std::cout << "condition number is:\n" << max_sum * max_sum_inverse;
  std::cout << "\n-------------------- END --------------------\n";*/
  return max_sum * max_sum_inverse;
}

std::vector<double> task4(std::vector<std::vector<double>> matrix, std::vector<double> b) {
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  for (int j = 0; j < matrix.size(); ++j) {
    if (std::abs(matrix[j][j]) < 1e-16) {
      std::cout << "bad matrix...\n";
      exit(-6);
    }

    int idx_max_element = 0;
    double max_element = 0;
    for (int i = j; i < matrix[j].size(); ++i) {
      if (std::abs(matrix[i][j]) > max_element) {
        max_element = std::abs(matrix[i][j]);
        idx_max_element = i;
      }
    }

    for (int k = 0; k < matrix.size(); ++k) {
      std::swap(matrix[j][k], matrix[idx_max_element][k]);
    }
    std::swap(b[j], b[idx_max_element]);
    for (int k = j; k < matrix.size() - 1; ++k) {
      double sth = 0;
      if (matrix[k + 1][j] > 0 && matrix[j][j] > 0 || matrix[k + 1][j] < 0 && matrix[j][j] < 0) {
        sth -= matrix[k + 1][j] / matrix[j][j];
      } else {
        sth = std::abs(matrix[k + 1][j] / matrix[j][j]);
      }

      int p = 0;
      while (p < matrix.size()) {
        matrix[k + 1][p] += matrix[j][p] * sth;
        ++p;
      }
      b[k + 1] += b[j] * sth;
    }
  }

  std::vector<double> x(matrix.size());
  for (int i = x.size() - 1; i > -1; --i) {
    x[i] = b[i] / matrix[i][i];
    for (int j = i + 1; j < matrix.size(); ++j) {
      x[i] -= (x[j] * matrix[i][j]) / matrix[i][i];
    }
  }
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  duration_gauss = end - start;
  duration_gauss.count();

/*  std::cout << "\n-------------------- TASK 4 - GAUSS --------------------\n";
  std::cout << "look at the matrix:\n";
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << "\n";
  }

  std::cout << "and at the vector b:\n";
  for (int i = 0; i < b.size(); ++i) {
    std::cout << b[i] << "\n";
  }

  std::cout << "its time for x:\n";
  for (int i = 0; i < x.size(); ++i) {
    std::cout << x[i] << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return x;
}

std::vector<double> task5(std::vector<std::vector<double>> matrix, std::vector<double> b) {
  std::vector<std::vector<double>> identity(matrix.size(), std::vector<double>(matrix.size()));
  std::vector<std::vector<double>> l(matrix.size(), std::vector<double>(matrix.size()));

  for (int i = 0; i < identity.size(); ++i) {
    identity[i][i] = 1;
    l[i][i] = 1;
  }

  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < matrix.size(); ++i) {
    if (std::abs(matrix[i][i]) < 1e-16) {
      std::cout << "bad matrix...\n";
      exit(-6);
    }

    int idx_max_element = 0;
    double max_element = 0;
    for (int j = i; j < matrix[i].size(); ++j) {
      if (std::abs(matrix[i][j]) > max_element) {
        max_element = std::abs(matrix[i][j]);
        idx_max_element = j;
      }
    }

    for (int k = 0; k < matrix.size(); ++k) {
      std::swap(matrix[k][i], matrix[k][idx_max_element]);
      std::swap(identity[k][i], identity[k][idx_max_element]);
    }

    int p = i + 1;
    while (p < matrix.size()) {
      l[p][i] = matrix[p][i] / matrix[i][i];
      ++p;
    }

    for (int k = i; k < matrix.size() - 1; ++k) {
      double first_in_row = 0;
      if (matrix[k + 1][i] > 0 && matrix[i][i] > 0 || matrix[k + 1][i] < 0 && matrix[i][i] < 0) {
        first_in_row -= matrix[k + 1][i] / matrix[i][i];
      } else {
        first_in_row = std::abs(matrix[k + 1][i] / matrix[i][i]);
      }

      p = 0;
      while (p < matrix.size()) {
        matrix[k + 1][p] += matrix[i][p] * first_in_row;
        ++p;
      }
    }
  }
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  duration_LUP = end - start;
  duration_LUP.count();

  std::vector<double> temp(b.size());
  for (int i = 0; i < identity.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      temp[i] += identity[i][j] * b[j];
    }
  }

  std::chrono::high_resolution_clock::time_point start_x = std::chrono::high_resolution_clock::now();
  std::vector<double> y(temp.size());
  for (int i = 0; i < l.size(); ++i) {
    y[i] = temp[i] / l[i][i];
    for (int j = i - 1; j > -1; --j) {
      y[i] -= (y[j] * l[i][j]) / l[i][i];
    }
  }

  std::vector<double> x(matrix.size());
  for (int i = x.size() - 1; i > -1; --i) {
    x[i] = y[i] / matrix[i][i];
    for (int j = i + 1; j < matrix.size(); ++j) {
      x[i] -= (x[j] * matrix[i][j]) / matrix[i][i];
    }
  }
  std::chrono::high_resolution_clock::time_point end_x = std::chrono::high_resolution_clock::now();
  duration_LUx = end_x - start_x;
  duration_LUx.count();

/*  std::cout << "\n-------------------- TASK 5 - LUP --------------------\n";
  std::cout << "NOW THIS IS U\n";
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "AND THIS IS L\n";
  for (int i = 0; i < l.size(); ++i) {
    for (int j = 0; j < l.size(); ++j) {
      std::cout << l[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "THEN THIS IS P...\n";
  for (int i = 0; i < identity.size(); ++i) {
    for (int j = 0; j < identity.size(); ++j) {
      std::cout << identity[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "OH LOOK XXX:\n";
  for (int i = 0; i < x.size(); ++i) {
    std::cout << x[i] << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return x;
}

std::vector<double> task6(std::vector<std::vector<double>> matrix, std::vector<double> b) {
  std::vector<std::vector<double>> l(matrix.size(), std::vector<double>(matrix.size()));
  for (int i = 0; i < l.size(); ++i) {
    l[i][i] = 1;
  }

  for (int j = 0; j < matrix.size(); ++j) {
    if (std::abs(matrix[j][j]) < 1e-16) {
      std::cout << "bad matrix...\n";
      exit(-6);
    }

    int p = j + 1;
    while (p < matrix.size()) {
      l[p][j] = matrix[p][j] / matrix[j][j];
      ++p;
    }

    for (int k = j; k < matrix.size() - 1; ++k) {
      double first_in_row = 0;
      if (matrix[k + 1][j] > 0 && matrix[j][j] > 0 || matrix[k + 1][j] < 0 && matrix[j][j] < 0) {
        first_in_row -= matrix[k + 1][j] / matrix[j][j];
      } else {
        first_in_row = std::abs(matrix[k + 1][j] / matrix[j][j]);
      }

      p = 0;
      while (p < matrix.size()) {
        matrix[k + 1][p] += matrix[j][p] * first_in_row;
        ++p;
      }
    }
  }

/*  std::cout << "\n-------------------- TASK 6 - LDLT - SQRT METHOD--------------------\n";
  std::cout << "LDL^T\n" << "L matrix:\n";
  for (int i = 0; i < l.size(); ++i) {
    for (int j = 0; j < l.size(); ++j) {
      std::cout << l[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "D matrix:\n";
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      if (i == j) {
        std::cout << matrix[i][j] << "\t";
      } else {
        std::cout << 0 << "\t";

      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "L^T matrix:\n";
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      std::cout << l[j][i] << "\t";
    }
    std::cout << "\n";
  }*/

  std::vector<std::vector<double>> gt(matrix.size(), std::vector<double>(matrix.size()));
  std::vector<std::vector<double>> g(gt.size(), std::vector<double>(gt.size()));
  for (int i = 0; i < gt.size(); ++i) {
    if (matrix[i][i] < 1e-16) {
      std::cout << "\nWRONG :)\n";
      exit(-6);
    }
    for (int j = 0; j < gt[i].size(); ++j) {
      gt[i][j] = matrix[i][j] / std::sqrt(matrix[i][i]);
      g[j][i] = matrix[i][j] / std::sqrt(matrix[i][i]);
    }
  }

  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  std::vector<double> y(b.size());
  for (int i = 0; i < g.size(); ++i) {
    y[i] = b[i] / g[i][i];
    for (int j = i - 1; j > -1; --j) {
      y[i] -= (y[j] * g[i][j]) / g[i][i];
    }
  }

  std::vector<double> x(gt.size());
  for (int i = x.size() - 1; i > -1; --i) {
    x[i] = y[i] / gt[i][i];
    for (int j = i + 1; j < gt.size(); ++j) {
      x[i] -= (x[j] * gt[i][j]) / gt[i][i];
    }
  }
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  duration_root = end - start;
  duration_root.count();

/*  std::cout << "\nanswer...finally...\n";
  for (int i = 0; i < x.size(); ++i) {
    std::cout << x[i] << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return x;
}

std::vector<double> task7(std::vector<std::vector<double>> matrix, std::vector<double> b) {
  std::vector<double> x(matrix.size());
  std::vector<double> prev_x(matrix.size());

  double w = 7.0 / 8.0;
  bool check = true;
  count_and_relax = 0;
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  while (check) {
    for (int i = 0; i < x.size(); ++i) {
      double sum1 = 0, sum2 = 0;
      for (int j = 0; j < i; ++j) {
        sum1 += matrix[i][j] * x[j];
      }
      for (int j = i + 1; j < x.size(); ++j) {
        sum2 += matrix[i][j] * prev_x[j];
      }

      x[i] = ((1 - w) * prev_x[i]) + ((w / matrix[i][i]) * (b[i] - sum1 - sum2));

      if (std::abs(x[i] - prev_x[i]) < 1e-16) {
        check = false;
      }

      prev_x[i] = x[i];
    }
    ++count_and_relax;
  }
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  duration_relax = end - start;
  duration_relax.count();

/*  std::cout << "\n-------------------- TASK 7 - RELAXATION METHOD --------------------\n";
  std::cout << "now look at x: \n";
  for (int i = 0; i < x.size(); ++i) {
    std::cout << x[i] << "\n";
  }
  std::cout << "\n-------------------- END --------------------\n";*/
  return x;
}

void task8() {
  std::vector<std::vector<double>> matrix;
  std::pair<std::vector<double>, std::vector<double>> b_and_y;
  double max_condition_num = 0, min_condition_num = 1000, avg_condition_num = 0, temp = 0;
  int max_count_and_relax = 0, min_count_and_relax = 1000, avg_count_and_relax = 0;
  std::vector<std::vector<double>> matrix_w_max_condition;
  std::chrono::duration<double, std::milli> duration_inverse_avg{};
  std::chrono::duration<double, std::milli> duration_gauss_avg{};
  std::chrono::duration<double, std::milli> duration_LUP_avg{};
  std::chrono::duration<double, std::milli> duration_LUx_avg{};
  std::chrono::duration<double, std::milli> duration_root_avg{};
  std::chrono::duration<double, std::milli> duration_relax_avg{};
  std::vector<double> norms_task4 = {1000, 0, 0}; // [0] - min norm
  std::vector<double> norms_task5 = {1000, 0, 0}; // [1] - avg norm
  std::vector<double> norms_task6 = {1000, 0, 0}; // [2] - max norm
  std::vector<double> norms_task7 = {1000, 0, 0};
  std::vector<double> x;
  std::vector<double> temp_norm_xy;


  int count = 0;
  while (count < 100) {
    matrix = task1();

    b_and_y = task2(matrix);

    temp = 0;
    temp = task3(matrix);
    if (temp > max_condition_num) {
      max_condition_num = temp;
      matrix_w_max_condition = matrix;
    } else if (temp < min_condition_num) {
      min_condition_num = temp;
    }
    avg_condition_num += temp;

    duration_inverse_avg += duration_inverse;
    /////////TASK4
    x = task4(matrix, b_and_y.first);
    temp_norm_xy.resize(x.size());
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      temp_norm_xy[i] = x[i] - b_and_y.second[i];
    }
    temp = 0;
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      if (std::abs(temp_norm_xy[i]) > temp) {
        temp = std::abs(temp_norm_xy[i]);
      }
    }
    if (temp > norms_task4[2]) {
      norms_task4[2] = temp;
    } else if (temp < norms_task4[0]) {
      norms_task4[0] = temp;
    }
    norms_task4[1] += temp;

    duration_gauss_avg += duration_gauss;
    /////////TASK5
    x = task5(matrix, b_and_y.first);
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      temp_norm_xy[i] = x[i] - b_and_y.second[i];
    }
    temp = 0;
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      if (std::abs(temp_norm_xy[i]) > temp) {
        temp = std::abs(temp_norm_xy[i]);
      }
    }
    if (temp > norms_task5[2]) {
      norms_task5[2] = temp;
    } else if (temp < norms_task5[0]) {
      norms_task5[0] = temp;
    }
    norms_task5[1] += temp;

    duration_LUP_avg += duration_LUP;
    duration_LUx_avg += duration_LUx;
    /////////TASK6
    x = task6(matrix, b_and_y.first);
    temp_norm_xy.resize(x.size());
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      temp_norm_xy[i] = x[i] - b_and_y.second[i];
    }
    temp = 0;
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      if (std::abs(temp_norm_xy[i]) > temp) {
        temp = std::abs(temp_norm_xy[i]);
      }
    }
    if (temp > norms_task6[2]) {
      norms_task6[2] = temp;
    } else if (temp < norms_task6[0]) {
      norms_task6[0] = temp;
    }
    norms_task6[1] += temp;

    duration_root_avg += duration_root;
    /////////TASK7
    x = task7(matrix, b_and_y.first);
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      temp_norm_xy[i] = x[i] - b_and_y.second[i];
    }
    temp = 0;
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      if (std::abs(temp_norm_xy[i]) > temp) {
        temp = std::abs(temp_norm_xy[i]);
      }
    }
    if (temp > norms_task7[2]) {
      norms_task7[2] = temp;
    } else if (temp < norms_task7[0]) {
      norms_task7[0] = temp;
    }
    norms_task7[1] += temp;

    duration_relax_avg += duration_relax;

    if (count_and_relax > max_count_and_relax) {
      max_count_and_relax = count_and_relax;
    } else if (count_and_relax < min_count_and_relax) {
      min_count_and_relax = count_and_relax;
    }
    avg_count_and_relax += count_and_relax;

    ++count;
  }

  std::ofstream fmatrix("matrix_from_task8.txt");
  for (int i = 0; i < matrix_w_max_condition.size(); ++i) {
    for (int j = 0; j < matrix_w_max_condition[i].size(); ++j) {
      fmatrix << matrix_w_max_condition[i][j] << "\t";
    }
    fmatrix << "\n";
  }

  std::ofstream ofs("task8.txt");
  ofs << "------------------------------\n";
  ofs << "max condition number: " << max_condition_num << "\n";
  ofs << "min condition number: " << min_condition_num << "\n";
  ofs << "average condition number: " << avg_condition_num / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find inverse matrix: " << duration_inverse_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "max norm for gauss: " << norms_task4[2] << "\n";
  ofs << "min norm for gauss: " << norms_task4[0] << "\n";
  ofs << "average norm for gauss: " << norms_task4[1] / 100 << "\n\n";

  ofs << "max norm for LUP: " << norms_task5[2] << "\n";
  ofs << "min norm for LUP: " << norms_task5[0] << "\n";
  ofs << "average norm for LUP: " << norms_task5[1] / 100 << "\n\n";

  ofs << "max norm for square root method: " << norms_task6[2] << "\n";
  ofs << "min norm for square root method: " << norms_task6[0] << "\n";
  ofs << "average norm for square root method: " << norms_task6[1] / 100 << "\n\n";

  ofs << "max norm for relaxation method: " << norms_task7[2] << "\n";
  ofs << "min norm for relaxation method: " << norms_task7[0] << "\n";
  ofs << "average norm for relaxation method: " << norms_task7[1] / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find x by gauss: " << duration_gauss_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find LUP: " << duration_LUP_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find solve LUx = b': " << duration_LUx_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find x by square root method: " << duration_root_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "average time to find x by relaxation method: " << duration_relax_avg.count() / 100 << "\n";
  ofs << "------------------------------\n";

  ofs << "------------------------------\n";
  ofs << "max number of iterations of relaxation method: " << max_count_and_relax << "\n";
  ofs << "min number of iterations of relaxation method: " << min_count_and_relax << "\n";
  ofs << "average number of iterations of relaxation method: " << avg_count_and_relax / 100 << "\n";
  ofs << "------------------------------\n";
}

void task9(std::vector<std::vector<double>> a2) {
  std::pair<std::vector<double>, std::vector<double>> b_and_y;
  std::vector<std::vector<double>> a1 = {{40, 4, -1, -2}, {4, -40, -1, -4}, {-1, -1, 33, -5}, {-2, -4, -5, 35}};
  std::cout << "this is matrix A1:\n";
  for (int i = 0; i < a1.size(); ++i) {
    for (int j = 0; j < a1[i].size(); ++j) {
      std::cout << a1[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "and tasks 2 - 7 for matrix A1:\n";
  b_and_y = task2(a1);
  task3(a1);
  task4(a1, b_and_y.first);
  task5(a1, b_and_y.first);
  //task6(a1, b_and_y.first);
  task7(a1, b_and_y.first);

  Sleep(3000);

  std::cout << "this is matrix A2:\n";
  for (int i = 0; i < a2.size(); ++i) {
    for (int j = 0; j < a2[i].size(); ++j) {
      std::cout << a2[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "and tasks 2 - 7 for matrix A2:\n";
  b_and_y = task2(a2);
  task3(a2);
  task4(a2, b_and_y.first);
  task5(a2, b_and_y.first);
  task6(a2, b_and_y.first);
  task7(a2, b_and_y.first);
}

void task101() {
  std::ifstream fmatrix("matrix_from_task8.txt");
  std::vector<std::vector<double>> matrix (256, std::vector<double>(256));
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      fmatrix >> matrix[i][j];
    }
  }

  std::pair<std::vector<double>, std::vector<double>> b_and_y;
  b_and_y = task2(matrix);

  std::vector<double> x(b_and_y.first.size());
  std::vector<double> b = b_and_y.first;
  int count = 0;
  double condition_number = task3(matrix);;
  while (count < 10) {
    for (int i = 0; i < b.size(); ++i) {
      b[i] +=  i * 3e-4;
    }

    x = task4(matrix, b);

    std::vector<double> temp_norm_xy(x.size());
    std::vector<double> temp_norm_bb(b_and_y.first.size());
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      temp_norm_xy[i] = x[i] - b_and_y.second[i];
      temp_norm_bb[i] = b[i] - b_and_y.first[i];
    }

    double norm_xy = 0, norm_y = 0, norm_bb = 0, norm_b = 0;
    for (int i = 0; i < temp_norm_xy.size(); ++i) {
      if (std::abs(temp_norm_xy[i]) > norm_xy) {
        norm_xy = std::abs(temp_norm_xy[i]);
      }
      if (std::abs(temp_norm_bb[i]) > norm_bb) {
        norm_bb = std::abs(temp_norm_bb[i]);
      }
      if (std::abs(b_and_y.second[i]) > norm_y) {
        norm_y = std::abs(b_and_y.second[i]);
      }
      if (std::abs(b_and_y.first[i]) > norm_b) {
        norm_b = std::abs(b_and_y.first[i]);
      }
    }

    std::cout << "\n------------------------------";
    std::cout << "\niteration: " << count + 1;
    std::cout << "\npractical: " << norm_xy / norm_y;
    std::cout << "\ntheoretical: " << condition_number * (norm_bb / norm_b);

    ++count;
  }
}

void task102(std::vector<std::vector<double>> matrix, std::vector<double> &b, std::vector<double> &y, std::vector<double> &x, double w) {
  std::vector<double> prev_x(matrix.size());


  bool check = true;
  count_and_relax = 0;
  while (check && count_and_relax < 3000) {
    for (int i = 0; i < x.size(); ++i) {
      double sum1 = 0, sum2 = 0;
      for (int j = 0; j < i; ++j) {
        sum1 += matrix[i][j] * x[j];
      }
      for (int j = i + 1; j < x.size(); ++j) {
        sum2 += matrix[i][j] * prev_x[j];
      }

      x[i] = ((1 - w) * prev_x[i]) + ((w / matrix[i][i]) * (b[i] - sum1 - sum2));

      if (std::abs(x[i] - prev_x[i]) < 1e-16) {
        check = false;
      }

      prev_x[i] = x[i];
    }
    ++count_and_relax;
    std::vector<double> temp_norm(matrix.size());
    for (int i = 0; i < matrix.size(); ++i) {
      temp_norm[i] = x[i] - y[i];
    }

    double norm = 0;
    for (int i = 0; i < temp_norm.size(); ++i) {
      if (std::abs(temp_norm[i]) > norm) {
        norm = std::abs(temp_norm[i]);
      }
    }
    std::cout << log10(norm) << "\n";
  }
  std::cout << "\n------------------------------\n";
}

int main() {
  //task8();

  std::vector<std::vector<double>> a2r = {{1, 6, 7, 8, 9, 10, 11, 12},
                                          {500, 5000, 50000, 500000, -5000, -50000, -500000, 1},
                                          {5, 4, 3, 2, 1, 0, -1, -2},
                                          {-995, -950, -500, 4000, 49000, -5, -4, -3},
                                          {-10, 0, -1, -2, -3, -4, -5, -6},
                                          {-2014, 2015, -2016, 2017, -2018, 2019, -2020, 2021},
                                          {-1990, -1985, -1970, -1935, -1860, 10095, -10100, 10105},
                                          {1010, 1556, 50252, 491854, -53936, -41913, -507970, 8293}};

  std::vector<std::vector<double>> a2 (a2r.size(), std::vector<double>(a2r.size()));
  for (int i = 0; i < a2r.size(); ++i) {
    for (int j = 0; j < a2r[i].size(); ++j) {
      for (int k = 0; k < a2r.size(); ++k) {
        a2[i][j] += a2r[k][i] * a2r[k][j];
      }
    }
  }

  //task9(a2);

  //task101();

/*  std::pair<std::vector<double>, std::vector<double>> b_and_y;
  std::vector<double> x;
  b_and_y = task2(a2);
  x = task4(a2, b_and_y.first);
  task102(a2, b_and_y.first, b_and_y.second, x, 0.8);
  task102(a2, b_and_y.first, b_and_y.second, x, 1.0);
  task102(a2, b_and_y.first, b_and_y.second, x, 1.2);*/

/*  std::ifstream fmatrix("matrix_from_task8.txt");
  std::vector<std::vector<double>> matrix (256, std::vector<double>(256));
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      fmatrix >> matrix[i][j];
    }
  }
  b_and_y = task2(matrix);
  x = task4(matrix, b_and_y.first);
  task102(matrix, b_and_y.first, b_and_y.second, x, 0.8);
  task102(matrix, b_and_y.first, b_and_y.second, x, 1.0);
  task102(matrix, b_and_y.first, b_and_y.second, x, 1.2);*/


  return 0;
}