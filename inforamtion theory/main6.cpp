#include <iostream>
#include <iomanip>
#include <unordered_map>
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

std::string dec_to_bin(int n)  { 
    std::string bin;
    int i = 0; 
    //std::cout << "\ndec " << n;
    while (n > 0) { 
        bin += std::to_string(n % 2); 
        n = n / 2; 
        i++; 
    } 
    //std::cout << " to bin: " << bin << "\n";
    return bin;
}

std::unordered_map<std::string, int> lz_compress(std::string input) {
    std::unordered_map<std::string, int> dictionary;
    std::vector<std::pair<int, int>> encoded;
    std::vector<int> compressed;
    std::string current_str, new_str;
    int num = 1;
    for (auto c : input) {
        new_str = current_str + c;

        if (dictionary.find(new_str) != dictionary.end()) {
            current_str = new_str;
        } else {
            dictionary[new_str] = num;
            compressed.emplace_back(dictionary[new_str]);
            encoded.emplace_back(std::make_pair(dictionary[current_str], c - '0'));
            ++num;
            current_str = "";
        }
    }
    dictionary[current_str] = num;
    compressed.emplace_back(dictionary[current_str]);
    encoded.emplace_back(std::make_pair(dictionary[current_str], 0));

    std::cout << "\n\ndict:\n";
    for (auto i : dictionary) {
        std::cout << i.first << " : " << i.second << "\n";
    }

    std::cout << "\ncomppressed:\n";
    for (auto i : compressed) {
        std::cout << i << " ";
    }

    std::cout << "\nencoded:\n";
    for (auto i : encoded) {
        std::cout << i.first << " : " << i.second << "\n";
    }
    return dictionary;
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout.precision(4);

    std::wifstream input ("input4.txt");
    std::wstringstream buffer;
    buffer << input.rdbuf();
    std::wstring text = format_text(buffer.str());

    std::string codes;
    for (auto i : text) {
        codes += dec_to_bin(i);
    }

    std::wcout << "\ninput text:\n" << buffer.str();
    std::wcout << "\n\nclear text:\n" << text << "\n\n";
    for (auto i : text) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << "\ncodes : " << codes << "\n";

    std::unordered_map<std::string, int> dictionary = lz_compress(codes);
    
    int uniq_phrases = dictionary.size() - 1;
    int bin_phrase_length = codes.length();
    double eps = 1e-9;
    std::cout << "\nlength of source text (bits) = " << text.length() * 8;
    std::cout << "\nlength of lz encoded text (bits) = " << uniq_phrases * (std::floor(log2(uniq_phrases)) + 2);
    if (uniq_phrases <= bin_phrase_length / ((1 - eps) * log2(bin_phrase_length))) {
        std::cout << "\nlz inequality | true\n";
        std::cout << uniq_phrases << " <= " << bin_phrase_length / ((1 - eps) * log2(bin_phrase_length));
    } else {
        std::cout << "\nlz inequality | false\n";
        std::cout << uniq_phrases << " >= " << bin_phrase_length / ((1 - eps) * log2(bin_phrase_length));

    }

    return 0;
}