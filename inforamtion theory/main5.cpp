#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>
#include <list>

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

std::string binary_code(int n, int k) {
    if (k == 0) {
        return std::string();
    }
    return binary_code(n / 2, k - 1) + std::to_string(n % 2);
}

std::vector<std::string> word_to_bin(std::wstring text, int k) {
    std::string temp;
    std::vector<std::string> codes;
    for (auto i : text) {
        temp += binary_code(i, 1);
        if (temp.length() % 2 == 0) {
            codes.emplace_back(temp);
            temp = "";
        }
    }

    while (temp.length() % k != 0) {
        temp += "0";
        if (temp.length() % 2 == 0) {
            codes.emplace_back(temp);
            temp = "";
        }
    }
    return codes;
}

std::string elias (int n) {
    int l = std::floor(log2(n)) + 1;
    int pref_l = std::floor(log2(l)) + 1;
    return binary_code(0, pref_l - 1) + binary_code(l, pref_l) + binary_code(n, l - 1);
}

std::vector<std::string> shuffle_books(std::list<std::string> bin_codes, std::vector<std::string> codes, int k) {
    std::vector<std::string> encoded;
    std::list<std::string>::iterator it;
    for (auto i : codes) {
        it = std::find(bin_codes.begin(), bin_codes.end(), i);
        encoded.emplace_back(elias(std::distance(bin_codes.begin(), it) + 1));
        if (it != bin_codes.end()) {
            std::string found_code = *it;
            bin_codes.erase(it);
            bin_codes.push_front(found_code);
        }
    }
    return encoded;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout.precision(4);

    std::wifstream input ("input4.txt");
    std::wstringstream buffer;
    buffer << input.rdbuf();
    std::wstring text = format_text(buffer.str());

    std::vector<int> k_vec;
    std::vector<double> len_vec;

    int k = 2;
    int phrase_number = std::pow(2, k);
    std::list<std::string> bin_codes;
    std::vector<std::string> codes = word_to_bin(text, k);
    std::vector<std::string> encoded;
    for (int i = 0; i < phrase_number; ++i) {
        bin_codes.emplace_back(binary_code(i, k));
    }
    encoded = shuffle_books(bin_codes, codes, k);
    int total_length = 0;
    for (auto i : encoded) {
        total_length += i.length();
    }
    // k_vec.emplace_back(k);
    // len_vec.emplace_back((double)total_length / encoded.size());

    // for (auto i : k_vec) {
    //     std::cout << i << " ";
    // }
    // std::cout << "\n";
    // for (auto i : len_vec) {
    //     std::cout << i << " ";
    // }

    std::wcout << "\ninput text:\n" << buffer.str();
    std::wcout << "\n\nclear text:\n" << text << "\n\n";
    std::cout << "phrase length = " << k << "\n";
    std::cout << "phrase number = " << phrase_number << "\n";
    std::cout << "bin codes for k = " << k << " are : ";
    for (auto i : bin_codes) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (auto i : text) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (auto i : text) {
        std::cout << binary_code(i, 1) << "   ";
    }
    std::cout << "\ncodes : ";
    for (auto i : codes) {
        std::cout << i << " ";
    }
    std::cout << "\nencoded: ";
    for (auto i : encoded) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "avg length for k = " << k << " of code word = " << double(total_length) / encoded.size();


    return 0;
}