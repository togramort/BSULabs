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

std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
std::string key;

const std::map<char, int> letterMap = {
    {'a', 0},
    {'b', 1},
    {'c', 2},
    {'d', 3},
    {'e', 4},
    {'f', 5},
    {'g', 6},
    {'h', 7},
    {'i', 8},
    {'j', 9},
    {'k', 10},
    {'l', 11},
    {'m', 12},
    {'n', 13},
    {'o', 14},
    {'p', 15},
    {'q', 16},
    {'r', 17},
    {'s', 18},
    {'t', 19},
    {'u', 20},
    {'v', 21},
    {'w', 22},
    {'x', 23},
    {'y', 24},
    {'z', 25}
};

void find_key() {
    // trying to find min of sums for each offset (to determine right offset) but doesnt work properly
    // double sum_of_diff = 0.0;
    // auto it1 = letter_freq.begin();
    // auto it2 = 0;
    // int counter = 0;
    // std::vector<double> all_diff;
    // while (it1 != letter_freq.end() && it2 != calc_letter_freq.size() && counter < 26) {
    //     double value1 = it1->second;
    //     double value2 = calc_letter_freq[it2];

    //     sum_of_diff += std::abs(value1 - value2);

    //     ++it1;
    //     ++it2;

    //     if (it1 == letter_freq.end() && it2 == calc_letter_freq.size()) {
    //         all_diff.push_back(sum_of_diff);
    //         sum_of_diff = 0.0;
    //         std::rotate(calc_letter_freq.begin(), calc_letter_freq.end() - 1, calc_letter_freq.end());
    //         it1 = letter_freq.begin();
    //         it2 = 0;
    //         ++counter;
    //     }
    // }

    // int idx_of_min_element = std::min_element(all_diff.begin(), all_diff.end()) - all_diff.begin();
    // auto it = letter_freq.end();
    // std::advance(it, -idx_of_min_element);
    // if (idx_of_min_element != 0) {
    //     prob_key.push_back(it->first);
    // } else {
    //     prob_key.push_back('A');   
    // }
}

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

void kasiski(const std::string& text) {
    std::unordered_map<std::string, std::vector<int>> repeated_grams;

    for (int l = 4; l <= 6; l++) {
        for (int i = 0; i <= text.length() - l; i++) {
            std::string gram = text.substr(i, l);
            repeated_grams[gram].push_back(i);
        }
    }

    std::set<int> all_diff;
    for (auto entry : repeated_grams) {
        if (entry.second.size() > 1) {
            for (int pos = 0; pos < entry.second.size() - 1; ++pos) {
                if (entry.second[pos + 1] - entry.second[pos] > 6) {
                    all_diff.insert(entry.second[pos + 1] - entry.second[pos]);
                }
            }
        }
    }
    std::cout << "all diff sizes " << all_diff.size();
    std::cout << "\n";
    for (auto i : all_diff) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (const auto& pair : repeated_grams) {
    const std::string& key = pair.first;
    const std::vector<int>& vec = pair.second;

        if (key.length() == 5 && vec.size() > 1) {
            std::cout << "key: " << key << ", vector: ";
            for (int num : vec) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\n";
    int gcd_res = 0;
    for (auto i : all_diff) {
        gcd_res = std::gcd(gcd_res, i);
    }

    std::cout << "\ngcd result aka (probaly) length of the key: " << gcd_res << "\n";

    // for (auto entry : repeated_grams) {
    //     if (entry.second.size() > 1) {
    //         std::cout << "\ngram: " << entry.first << "\n";
    //         std::cout << "repeats: " << entry.second.size() << "\n";
    //         std::cout << "positions: ";
    //         for (int position : entry.second) {
    //             std::cout << position << " ";
    //         }
    //         std::cout << "\n\n";
    //     }
    // }

    // for (const auto& entry : find_gcd) {
    //     std::cout << "GCD: " << entry.first << ", Count: " << entry.second << std::endl;
    // }
}

void encrypt() {
    std::ifstream input ("text.txt");
    std::ofstream output ("encrypted.txt", std::ofstream::trunc);
    std::string text = check_file(input, output);
    std::string encrypted_text;
    for (int i = 0, j = 0; i < text.length(); ++i) {
        if (text[i] != ' ') {
            encrypted_text.push_back((text[i] + key[j]) % 26 + 'A');
        } else {
            encrypted_text.push_back(' ');
            //continue;
        }
        j = (j + 1) % key.length();
    }
    output << encrypted_text;
    kasiski(encrypted_text);
}

void decrypt() {
    std::ifstream input ("encrypted.txt");
    std::ofstream output ("decrypted.txt", std::ofstream::trunc);
    std::string text = check_file(input, output);
    std::string decrypted_text;
    for (int i = 0, j = 0; i < text.length(); ++i) {
        if (text[i] != ' ') {
            decrypted_text.push_back((text[i] + 26 - key[j]) % 26 + 'A');
        } else {
            decrypted_text.push_back(' ');
            //continue;
        }
        j = (j + 1) % key.length();
    }
    output << decrypted_text;
}

int main() {
    // std::string a = "baba";
    // std::string b = "ccc";

    // std::cout << a[0] + b[1];

    // std::string c;
    // c.push_back(197 % 26 + 97);
    // std::cout << "\n" << 197%26+97 << c;
    // std::cout << "\n,v,v,v, " << 1 % 2;

    std::string text = "UHMTIWZOQZMDQGCFGWISBSZWNSYFMFFCOULZAKBSWQAILKIEQGNWVTQSHAASZHYVXGESHVEFQAUAPMBRULILAMIMPWFMIMOFAKBGALTWHYWZMJYTIWZUIARYPILARYYMMWQWEHYJETDCUVLWDSCFQDMUUKTSUBCNISXFYSHQNSYFLWDSZGVKULQWICEOHVMXQSFDMCQWUEJAZOFDCSPOJLMFSHILLWOIFLYJQWGSPKAGJWECUBALLWXOHYYSSSGGVWRZOWRLXMCSVJUJYVHMDWHYXZQTCJWLISYCSXESJLIENSLLLWISULLWDVUKFWQBPWVQZWWWINQBNZSMSVCLWGOHITIJUHMKXAXZLSXZQFMMRFKOHVASDACFJSOHCOIFFHILLWNSUULSZRMOEEUBNZIEQRCLIJDOHWEFESUWEJXWYJXGPOSAEEXWPARYIWNZENQFSOIDOCGARYTCMLJSYWFQMZMJYECGIBJJMNMHYTIVDCIEFMFKYWELNFYSOXMGNDYFOVUFHVUBHWVLAUYLLWDCHKYFPOSKAWQONSFASVIEIUACEWHHMSFDEXAFFMRUTWHKTSUBFMRUTWMMWMMZFQXZQPCYKWEHGWEDATNZIVMMCLWSXGINIJKQIEQGZTIJXZQDYGTDQHILECQOGAHVMMHSTJUUBLEXFSLSFASAYSPAMAUUXMMZFQNMEHQSOAZUOHJJAAGQRSBFCYLLZCQGROQSEVEQEWNSOWOZUKWWEONLLWXCWSPMZWPWVKUHSLLWDSCEILESPWVSXBULMNQGJSRAEVMHISWSLKXZQMBSZWNSYFZWDMEARVMBXHELUSHLAAFVGWELRWLKXAEHLMKYXSXLSUAAJJIZQBXLLWUFMHEFUGBTYLZCQAYFPSLKXSZRGGWLATIMVUABPWVKMHCGRKFVYQLSHSWGQEQBNWHLTONECKBOHAWZTOMAQHDCPWHSXCNKMFOSQWJADGNEILZCQAEEYCLWGGZTCVIFFHIMWWFVYDEFSIUYIAZCNZIJBZUUIKXWEWWLAFYKEFPFYKXSGFUFXKUOGKSYXOXLLSFWXWGAPSXLSKBSHVXZQGYEIKFSLZIJQWHKTSUBQWLSHSUFIPFSHVIVISYCIFPQIEMFSIJKSSSFIMTGRASXVAQBXKEFPWUJIYAWHYXGFFUNIDFCZJEFOSZGVXAILVEQEWNKWGQOMQEFPWHWBHQBMAZWFCNJENQZCFXWDBULMGZOFDCAZSOJSHQWFGZWUHCDSGWTIJASDRNGLWMFCFKXDCGQSMECIFPAWSCKEAPRIFXZQGCLELQHIKXSKWHLSMOVGGVWATNWRHQFBSTKKCOUSMXRYNIFOCGWXGHWMAXOTONVSQAINZMFW";
    std::string keyd = "Mouses";
    std::string new_text;

    // std::cout << (int)text[0] << " + " << (int)key[0] << " + " << (int)'a' << "\n";
    // std::cout << (text[0] + key[0]) % 26 + 'a';
    // std::cout << text.length();
    // for (int i = 0; i < text.length(); i += keyd.length()) {
    //     new_text.push_back(text[i]);
    // }
    // std::cout << "\n" << new_text << "\n";

    // std::map<char, double> letterCounts;

    // for (char c : new_text) {
    //     c = std::toupper(c);
    //     letterCounts[c]++;
    // }

    // for (auto& pair : letterCounts) {
    //     pair.second /= text.length();
    // }

    // for (const auto& pair : letterCounts) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }
    // std::vector<int> v = {1, 2, 3, 4};
    // std::rotate(v.begin(), v.end() - 1, v.end());
    // for (auto i : v) {
    //     std::cout << i << " ";
    // }

    // std::ifstream keys ("keys.txt");
    // std::string line;
    // if (keys.is_open()) {
    //     while (std::getline(keys, line)) {
    //         std::cout << line << "\n";
    //     }        
    // }    
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    std::map <char, double> letter_freq = {
    {'A', 0.08167},
    {'B', 0.01492},
    {'C', 0.02782},
    {'D', 0.04253},
    {'E', 0.12702}
    };
auto it = letter_freq.begin();  // итератор на элемент, следующий за последним

// Сдвиг на -2 позиции
std::advance(it, -1);
std::cout << it->first;
it = letter_freq.end();
std::cout << "\n" << it->first;
}