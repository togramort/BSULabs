#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

struct HuffmanNode {
    char data;
    double frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char data, double frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct NodeComparator {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* build_huffman_tree(std::map<char, double> frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, NodeComparator> pq;

    for (auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, NodeComparator> pq2 = pq;
    std::cout << "how letters and frequencies are stored:\n";
    while (!pq2.empty()) {
        HuffmanNode* node = pq2.top();
        pq2.pop();
        std::cout << node->data << " - " << node->frequency << std::endl;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        
        HuffmanNode* right = pq.top();
        pq.pop();
        
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    return pq.top();
}

void build_huffman_codes(HuffmanNode* root, const std::string& code, std::map<char, std::string>& codes) {
    if (root == nullptr) {
        return;
    }
    
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->data] = code;
    }
    
    build_huffman_codes(root->left, code + "0", codes);
    build_huffman_codes(root->right, code + "1", codes);
}

std::map<char, double> get_frequencies(std::string text) {
    std::map<char, double> frequencies;
    for (char c : text) {
        ++frequencies[c];
    }
    int total_freq = 0;
    for (auto pair : frequencies) {
        total_freq += pair.second;
    }
    for (auto& pair : frequencies) {
        pair.second /= static_cast<double>(total_freq);
    }
    double sum_freq = 0.0;
    for (auto pair : frequencies) {
        sum_freq += pair.second;
    }
    if (abs(sum_freq - 1.0) < 1e-9) {
        std::cout << "\nsum of probabilities equals to 1" << "\n\n";
    } else {
        std::cerr << "\nsum of probabilities does not  equal to 1 but = " << sum_freq << "\n";
        std::exit(EXIT_FAILURE);
    }
    return frequencies;
}

double average_length(std::map<char, std::string> codes, std::map<char, double> frequencies) {
    double sum = 0.0;
    for (auto& pair : codes) {
        char symbol = pair.first;
        std::string code = pair.second;
        double frequency = frequencies[symbol];
        sum += code.length() * frequency;
    }
    return sum;
}

double source_entropy(std::map<char, double> frequencies) {
    double result = 0.0;
    for (auto& pair : frequencies) {
        result += -pair.second * log2(pair.second);
    }
    return result;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::string text;
    std::cout.precision(4);
    std::cout << "enter text: \n";
    std::getline(std::cin, text);
    
    std::map<char, double> frequencies = get_frequencies(text);
    HuffmanNode* root = build_huffman_tree(frequencies);
    std::map<char, std::string> codes;
    build_huffman_codes(root, "", codes);
    std::cout << "\nhuffman codes:" << std::endl;
    for (const auto& pair : codes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::vector<std::string> huffman_codes;
    for (char c : text) {
        huffman_codes.emplace_back(codes[c]);
    }
    std::cout << "\nhuffman codes for text \"" << text << "\":\n";
    for (auto i : huffman_codes) {
        std::cout << i << " | ";
    }

    std::cout << "\naverage length = " << average_length(codes, frequencies);
    std::cout << "\nentropy = " << source_entropy(frequencies);
    return 0;
}