#include <iostream>
#include <cmath>
#include <vector>

double factorial(int i) {
	if (i == 0) {
        return 1;
    } else {
        return i * factorial(i - 1);
    }
}

int main() {
    int n = 20;
    double eps = 0.138;

    double p = 0.3333; // 1 - black and 2 - white
    double h = -p * log2(p) - (1 - p) * log2(1 - p); // binary: take black or white
    std::cout << "entropy of binary random variable X = " << h << "\n";


    double min_level = std::pow(2.0, -n * (h + eps));
    double max_level = std::pow(2.0, -n * (h - eps));
    std::cout << "lower bound of the probability of occurance of an e-typical sequence = " << min_level << "\n";
    std::cout << "upper bound of the probability of occurance of an e-typical sequence = " << max_level << "\n\n";

    // all possible sequences
    std::vector<std::vector<int>> sequences;
    for (int i = 0; i < std::pow(2, n); ++i) {
        std::vector<int> seq;
        for (int j = 0; j < n; ++j) {
            int x = i & (1 << j);
            if (x > 0) {
                seq.push_back(1);
            } else {
                seq.push_back(0);
            }
        }
        sequences.push_back(seq);
    }

    // for (int i = 0; i < sequences.size(); i++) {
    //     for (int j = 0; j < sequences[i].size(); j++) {
    //         std::cout << sequences[i][j];
    //     }
    //     std::cout << "\n";
    // }

    // е-типичные - кол-во шариков одного цвета отличается от количества шариков другого цвета не более чем на е
    // примем 0 - белый 1 - черный
    // => вероятность последовательности >= 0.138

    std::cout << "\nall e-typical sequences for eps = " << eps << ":\n";
    double temp_sum = 1.0;
    for (int i = 0; i < sequences.size(); ++i) {
        temp_sum = 1.0;
        for (int j = 0; j < sequences[i].size(); ++j) {
            if (sequences[i][j] == 0) {
                temp_sum *= (2.0 / 3.0);
            } else {
                temp_sum *= (1.0 / 3.0);
            }
        }
        std::cout << "temp sum for i = " << i << " is " << temp_sum << "\n";
        if (temp_sum >= eps) { //or look between bounds??
            for (int k = 0; k < sequences[i].size(); ++k) {
                std::cout << sequences[i][k];
            }
            std::cout << "\n";
        }
    }

    double sum = 0.0, sum_p = 0.0;
    double eps1 = eps / log2((1 - p) / p);
    for (int i = 1; i < n + 1; ++i) {
        double curr_eps = (double)i / (double)n - p;
        if (curr_eps <= eps1) {
            double fact = factorial(n) / (factorial(i) * factorial(n - i)); // все сочетания для разного кол-ва 1
            sum += fact;
            sum_p += fact * std::pow(p, i) * std::pow(1.0 - p, n - i);
        }
    }

    std::cout << "\namount of all e-typical sequences = " << sum << "\n";
    std::cout << "part among all possible  = " << sum / std::pow(2, n) << "\n";
    std::cout << "sum of probabilities for e-typical sequences = " << sum_p << "\n";

    double min_level_t = (1.0 - eps) * std::pow(2.0, n * (h - eps));
    double max_level_t = std::pow(2.0, n * (h + eps));
    std::cout << "lower bound of the probability of occurance of an e-typical sequence for T(X) = " << min_level << "\n";
    std::cout << "upper bound of the probability of occurance of an e-typical sequence for T(X) = " << max_level << "\n\n";

    if (sum_p <= 1 - eps) {
        std::cout << "\nP_e > 1 - e? | " << sum_p << " <= " << 1 - eps << " | false";
    } else {
        std::cout << "\nP_e > 1 - e? | " << sum_p << " > " << 1 - eps << " | true";
    }
    return 0;
}