#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>
#include <numeric>
#include <set>
#include <deque>

std::map <char, double> letter_freq = {
    {'A', 0.08167},
    {'B', 0.01492},
    {'C', 0.02782},
    {'D', 0.04253},
    {'E', 0.12702},
    {'F', 0.0228},
    {'G', 0.02015},
    {'H', 0.06094},
    {'I', 0.06966},
    {'J', 0.00153},
    {'K', 0.00772},
    {'L', 0.04025},
    {'M', 0.02406},
    {'N', 0.06749},
    {'O', 0.07507},
    {'P', 0.01929},
    {'Q', 0.00095},
    {'R', 0.05987},
    {'S', 0.06327},
    {'T', 0.09056},
    {'U', 0.02758},
    {'V', 0.00978},
    {'W', 0.0236},
    {'X', 0.0015},
    {'Y', 0.01974},
    {'Z', 0.00074}
};

std::string check_file(std::ifstream& input, std::ofstream& output) {
    if (!input || !output) {
        std::cout << "\nlavochka closed!!!!1!!1!11\n";
        return "nu realno";
    } else if (input.peek() == EOF) {
        std::cout << "\nxochupiwo\n";
        return "ya tozhe";
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string text = buffer.str();
    std::string clean_text = "";
    for (auto c : text) {
        if (isalpha(c)) {
            clean_text += std::toupper(c);
        }
    }    
    //std::cout << "\nclear text\n" << clean_text << "\n\n";
    return clean_text;
}

void decrypt(std::string key) {
    std::ifstream input ("encrypted.txt");
    std::ofstream output ("decrypted.txt", std::ofstream::trunc);
    std::string text = check_file(input, output);
    std::string decrypted_text;
    for (int i = 0, j = 0; i < text.length(); ++i) {
        decrypted_text.push_back((text[i] + 26 - key[j]) % 26 + 'A');
        j = (j + 1) % key.length();
    }
    output << decrypted_text;
    input.close();
    output.close();
}

void find_key(std::string encrypted_text, int key_lenght) {
    //other (kinda) solutions:
    // - check diff of freq < 0.0025
    // - find the offset using only most used letter (E in english + in ciphertext)
    // - index of coincedence
    // - min of sums for each offset using letter_freq (has problems?)
    int temp = 0;
    std::string prob_key;
    std::vector<double> calc_letter_freq(letter_freq.size());

    while (temp < key_lenght) {
        std::fill(calc_letter_freq.begin(), calc_letter_freq.end(), 0.0);
        for (auto i = temp; i < encrypted_text.length(); i += key_lenght) {
            calc_letter_freq[std::distance(letter_freq.begin(), letter_freq.find(encrypted_text[i]))] += 1.0;
        }

        for (auto i = 0; i < calc_letter_freq.size(); ++i) {
            calc_letter_freq[i] /= encrypted_text.length() / key_lenght;
        }
        
        int e_pos = 4;
        int max_freq_pos = std::distance(calc_letter_freq.begin(), std::max_element(calc_letter_freq.begin(), calc_letter_freq.end()));
        auto it = letter_freq.begin();
        if (max_freq_pos - e_pos >= 0) {
            std::advance(it, max_freq_pos - e_pos);
        } else {
            std::advance(it, max_freq_pos - e_pos - 1);
        }
        prob_key.push_back(it->first);
        ++temp;
    }

    std::cout << "\nyooo look at this key: " << prob_key;
    decrypt(prob_key);
}

void kasiski(std::string encrypted_text) {
    std::unordered_map<std::string, std::vector<int>> repeated_grams;
    //careful w/ l-grams
    for (int l = 4; l < 6; ++l) {
        for (int i = 0; i <= encrypted_text.length() - l; i++) {
            std::string gram = encrypted_text.substr(i, l);
            repeated_grams[gram].push_back(i);
        }
    }

    std::set<int> all_diff;
    for (auto entry : repeated_grams) {
        if (entry.second.size() > 1) {
            for (int pos = 0; pos < entry.second.size() - 1; ++pos) {
                if (entry.second[pos + 1] - entry.second[pos] > 15) {
                    all_diff.insert(entry.second[pos + 1] - entry.second[pos]);
                }
            }
        }
    }

    std::map<int, int> find_gcd;

    auto it = all_diff.begin();
    auto prev = *it;
    ++it;

    for (; it != all_diff.end(); ++it) {
        int current = *it;
        ++find_gcd[std::gcd(prev, current)];
        prev = current;
    }

    int max_value = 0;
    int max_key = 0;

    for (auto entry : find_gcd) {
        if (entry.second > max_value && entry.first != 1) {
            max_value = entry.second;
            max_key = entry.first;
        }
    }

    // for (auto entry : find_gcd) {
    //     std::cout << "GCD: " << entry.first << ", Count: " << entry.second << std::endl;
    // }

    std::cout << "\ngcd result aka (probaly) length of the key: " << max_key << "\n";
    find_key(encrypted_text, max_key);
}


void encrypt(std::ifstream& input, std::string actual_key) {
    std::ofstream output ("encrypted.txt", std::ofstream::trunc);
    std::string text = check_file(input, output);
    std::string encrypted_text;
    for (int i = 0, j = 0; i < text.length(); ++i) {
        encrypted_text.push_back((text[i] + actual_key[j]) % 26 + 'A');
        j = (j + 1) % actual_key.length();
    }
    output << encrypted_text;
    input.close();
    output.close();
    kasiski(encrypted_text);
}

int main() {
    // std::string path;
    // std::string actual_key = "BACKSPACESMANIC";
    // int count = 1;
    // for (int i = 100; i < 15000;) {
    //     ++count;
    //     for (int j = 1; j < 11; ++j) {
    //         path = "D:\\program etc\\projects4\\kbrs1\\text\\" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
    //         std::cout << "\n=========================================================\n";
    //         std::cout << "\n" << path << "\n";
    //         std::ifstream input (path);
    //         encrypt(input, actual_key);
    //         std::cout << "\n=========================================================\n";
    //     }
    //     if (count % 2 == 0) {
    //         i *= 5;
    //     } else {
    //         i *= 2;
    //     }
    // }

    // std::ifstream keys ("keys.txt");
    // std::string actual_key;
    // if (keys.is_open()) {
    //     while (std::getline(keys, actual_key)) {
    //         std::ifstream path ("for_key.txt");
    //         std::cout << "\n=========================================================\n";
    //         encrypt(path, actual_key);
    //         std::cout << "\nyoooo look actual key: " << actual_key;
    //         std::cout << "\n=========================================================\n";
    //         path.close();
    //     }        
    // } 

    std::ifstream path ("for_key.txt");
    std::string actual_key = "MOUSE";
    encrypt(path, actual_key);

    return 0;
}