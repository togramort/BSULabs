#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include <Windows.h>

struct HuffmanNode {
    std::wstring data;
    double frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(std::wstring data, double frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct NodeComparator {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* build_huffman_tree(std::map<std::wstring, double> frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, NodeComparator> pq;

    for (auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, NodeComparator> pq2 = pq;
    std::cout << "how letters and frequencies are stored:\n";
    while (!pq2.empty()) {
        HuffmanNode* node = pq2.top();
        pq2.pop();
        std::wcout << node->data << L" - " << node->frequency << std::endl;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        
        HuffmanNode* right = pq.top();
        pq.pop();
        
        HuffmanNode* parent = new HuffmanNode(L"\0", left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    return pq.top();
}

void build_huffman_codes(HuffmanNode* root, const std::string& code, std::map<std::wstring, std::string>& codes) {
    if (root == nullptr) {
        return;
    }
    
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->data] = code;
    }
    
    build_huffman_codes(root->left, code + "0", codes);
    build_huffman_codes(root->right, code + "1", codes);
}

double average_length(std::map<std::wstring, std::string> codes, std::map<std::wstring, double> frequencies) {
    double sum = 0.0;
    for (auto& pair : codes) {
        std::wstring symbol = pair.first;
        std::string code = pair.second;
        double frequency = frequencies[symbol];
        sum += code.length() * frequency;
    }
    return sum;
}

double source_entropy(std::map<std::wstring, double> frequencies) {
    double result = 0.0;
    for (auto& pair : frequencies) {
        result += -pair.second * log2(pair.second);
    }
    return result;
}

int huffman_length(std::vector<std::string> huffman_codes) {
    int sum = 0;
    for (auto i : huffman_codes) {
        sum += i.length();
    }
    return sum;
}

std::wstring format_text(std::wstring text) {
    std::wstring clean_text = L"";
    for (auto c : text) {
        if (int(c) >= 224 && int(c) <= 255 && int(c) != 250) {
            clean_text += c;
        } else if (int(c) >= 192 && int(c) <= 223 && int(c) != 218) {
            clean_text += int(c) + 32;
        } else if (int(c) == 32 || int(c) == 10)  {
            clean_text += ' ';
        } else if (int(c) == 250 || int(c) == 218 || int(c) == 184) {
            if (int(c) == 250 || int(c) == 218) {
                clean_text += 252;
            } else if (int(c) == 184) {
                clean_text += 229;
            }
        } else {
            continue;
        }
    }   
    return clean_text;
}

std::map<std::wstring, double> get_frequencies_pair(std::wstring text) {
    std::map<std::wstring, double> frequencies;
    for (int i = 0; i < text.length(); i += 2) {
        ++frequencies[text.substr(i, 2)];
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

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout.precision(4);

    std::wifstream input ("nak.txt");
    std::wstringstream buffer;
    buffer << input.rdbuf();
    //std::wcout << "\ninput text:\n" << buffer.str();
    std::wstring text = format_text(buffer.str());
    //std::wcout << "\n\nclear text:\n" << text << "\n";

    std::cout << "\n========================================using calculated frequencies========================================\n";
    std::map<std::wstring, double> frequencies = get_frequencies_pair(text);
    HuffmanNode* root = build_huffman_tree(frequencies);
    std::map<std::wstring, std::string> codes;
    build_huffman_codes(root, "", codes);
    // std::cout << "\nhuffman codes:" << std::endl;
    // for (const auto& pair : codes) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    std::vector<std::string> huffman_codes;
    for (auto c : text) {
        huffman_codes.emplace_back(codes[std::wstring(1, c)]);
    }
    // std::wcout << "\nhuffman codes for text \"" << text << "\":\n";
    // for (auto i : huffman_codes) {
    //     std::cout << i << " | ";
    // }
    int txt_len = text.length() * 8;
    int huf_len = huffman_length(huffman_codes);
    std::cout << "\naverage length = " << average_length(codes, frequencies);
    std::cout << "\nentropy = " << source_entropy(frequencies);
    std::cout << "\ntext length = " << txt_len;
    std::cout << "\nhuffman text length = " << huf_len;
    std::cout << "\n" << double(txt_len) / huf_len;
    std::cout << "\n========================================using calculated frequencies========================================\n";

    return 0;
}