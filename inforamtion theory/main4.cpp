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

std::map<char, double> get_frequencies(std::wstring text) {
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

double relative_entropy(std::map<char, double> frequencies, std::map<char, double> prepared_freq) {
    double result = 0.0;
    for (auto& pair : prepared_freq) {
        char symbol = pair.first;
        result += pair.second * log2(pair.second / frequencies[symbol]);
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

int main() {
    std::map<char, double> prepared_freq = 
    {
        {224, 0.062},
        {225, 0.014},
        {226, 0.038},
        {227, 0.013},
        {228, 0.025},
        {229, 0.072},
        {230, 0.007},
        {231, 0.016},
        {232, 0.062},
        {233, 0.010},
        {234, 0.028},
        {235, 0.035},
        {236, 0.026},
        {237, 0.053},
        {238, 0.090},
        {239, 0.023},
        {240, 0.040},
        {241, 0.045},
        {242, 0.053},
        {243, 0.021},
        {244, 0.002},
        {245, 0.009},
        {246, 0.004},
        {247, 0.012},
        {248, 0.006},
        {249, 0.003},
        {251, 0.016},
        {252, 0.014},
        {253, 0.003},
        {254, 0.006},
        {255, 0.018},
        {32, 0.175}
    };

    std::cout << std::fixed << std::setprecision(4);
    std::cout.precision(4);

    std::wifstream input ("nak.txt");
    std::wstringstream buffer;
    buffer << input.rdbuf();
    //std::wcout << "\ninput text:\n" << buffer.str();
    std::wstring text = format_text(buffer.str());
    //std::wcout << "\n\nclear text:\n" << text << "\n";
    
    std::cout << "========================================using prepared frequencies========================================\n";
    HuffmanNode* root_prep = build_huffman_tree(prepared_freq);
    std::map<char, std::string> codes_prep;
    build_huffman_codes(root_prep, "", codes_prep);
    // std::cout << "\nhuffman codes:" << std::endl;
    // for (const auto& pair : codes_prep) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    std::vector<std::string> huffman_codes_prep;
    for (auto c : text) {
        huffman_codes_prep.emplace_back(codes_prep[c]);
    }
    // std::wcout << "\nhuffman codes for text \"" << text << "\":\n";
    // for (auto i : huffman_codes_prep) {
    //     std::cout << i << " | ";
    // }

    int txt_len_prep = text.length() * 8;
    int huf_len_prep = huffman_length(huffman_codes_prep);
    std::cout << "\naverage length = " << average_length(codes_prep, prepared_freq);
    std::cout << "\nentropy = " << source_entropy(prepared_freq);
    std::cout << "\ntext length = " << txt_len_prep;
    std::cout << "\nhuffman text length = " << huf_len_prep;
    std::cout << "\n" << double(txt_len_prep) / huf_len_prep;
    std::cout << "\n========================================using prepared frequencies====================\n";

    std::cout << "\n========================================using calculated frequencies========================================\n";
    std::map<char, double> frequencies = get_frequencies(text);
    HuffmanNode* root = build_huffman_tree(frequencies);
    std::map<char, std::string> codes;
    build_huffman_codes(root, "", codes);
    // std::cout << "\nhuffman codes:" << std::endl;
    // for (const auto& pair : codes) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    std::vector<std::string> huffman_codes;
    for (auto c : text) {
        huffman_codes.emplace_back(codes[c]);
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

    std::cout << "\nrelative entropy: " << relative_entropy(frequencies, prepared_freq);

    return 0;
}