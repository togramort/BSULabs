#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

struct TunstallNode {
    double probability;
    std::string data;
    int data_length;
    
    TunstallNode(double probability, std::string data, int data_length) : probability(probability), data(data), data_length(data_length) {}
};

std::vector<TunstallNode> build_tunstall_codes(int base, int length, std::vector<double>& probs) {
    int temp_l = probs.size();
    int temp_d = std::pow(base, length);
    int split = floor((temp_d - temp_l) / (temp_l - 1));
    int temp_m = temp_l + split * (temp_l - 1);
    std::cout << "q* - splits: " << split << "\nM - amount of output codes: " << temp_m << "\n";

    std::vector<TunstallNode> result = { {1.0, "", 0} };
    int num_codes = 0;
    for (int i = 0; i <= split; ++i) {
        double max_prob = result[0].probability;
        int max_idx = 0;

        for (int j = 1; j < result.size(); ++j) {
            if (result[j].probability > max_prob) {
                max_prob = result[j].probability;
                max_idx = j;
            }
        }

        TunstallNode node = result[max_idx];
        result.erase(result.begin() + max_idx);

        for (int j = 0; j < temp_l; ++j) {
            TunstallNode node_copy = node;
            node_copy.probability *= probs[j];
            node_copy.data += std::to_string(j);
            ++node_copy.data_length;
            result.emplace_back(node_copy);
        }
    }
    return result;
}

double average_length(std::vector<TunstallNode> codes) {
    double sum = 0.0;
    for (int i = 0; i < codes.size(); i++) {
        sum += codes[i].data.length() * codes[i].probability;
    }
    return sum;
}

double source_entropy(std::vector<double> probs) {
    double result = 0.0;
    for (int i = 0; i < probs.size(); ++i) {
        result += -probs[i] * log2(probs[i]);
    }
    return result;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout.precision(4);

    int base, length;
    std::cout << "enter base and length: \n";
    std::cin >> base >> length;

    std::vector<double> probs;
    double curr_prob, total_prob = 0.0;
    std::cout << "enter probabilities for each \"word\": \n";
    while (std::cin >> curr_prob) {
        probs.emplace_back(curr_prob);
        total_prob += curr_prob;
        if (total_prob > 1) {
            std::cerr << "sum of probabilities is " << total_prob << " > 1\n";
            return -1;
        }
    }
    if (total_prob != 1.0) {
        std::cerr << "sum of probabilities != 1 but = " << total_prob;
        return -1;
    }

    std::vector<TunstallNode> codes = build_tunstall_codes(base, length, probs);
    for (TunstallNode code : codes) {
        std::cout << "prob: " << code.probability << " | code: " << code.data << "\n";
    }
    double avg_length = average_length(codes);
    std::cout << "\naverage length = " << avg_length;
    std::cout << "\naverage amount of codes symbols = " << length / avg_length;
    std::cout << "\nlower bound = " << source_entropy(probs) / log2(base);
    return 0;
}