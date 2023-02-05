#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <sstream>
#include <string>

int count(std::string file_path, std::string word) {
  std::ifstream stream(file_path);
  std::vector<std::string> words;
  int counter = 0;
  if (stream.is_open()) {
    while (!stream.eof()) {
      std::string temp_;
      stream >> temp_;
      if (temp_ == word) {
        counter++;
      }
    }
  }
  return counter;
}

int main() {
  const int SIZE = 10;
  std::ifstream fin("files.txt");
  std::vector<std::string> files;
  while (!fin.eof()) {
    std::stringstream buffer;
    std::string file_path;
    fin >> file_path;
    files.push_back(file_path);
  }
  std::vector<int> counters(SIZE - 1);
  for (int i = 0; i < SIZE; i++) {
    std::cout << files.at(i) << "\n";
  }
  std::string word = "hello";
  auto startTime = std::chrono::high_resolution_clock::now(); // start;
  for (int i = 0; i < SIZE - 1; i++) {
    counters[i] = std::async(count, files.at(i), word).get();
  }

  auto endTime = std::chrono::high_resolution_clock::now(); // end;
  std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
            << " ms\n";

  for (size_t i = 0; i < counters.size(); i++) {
    std::cout << "counter " << i << " " << counters[i] << "\n";
  }
}

/*#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <string>
#include <queue>

using namespace std;

string word_for_find = "hello";
int n = 10;
int p = 8;
queue<string> fileNames;
mutex mut;
struct count_block {
  string fileName;
  ifstream fin;
  int counter;

  void operator()() {
    while (true) {
      mut.lock();
      if (fileNames.empty()) {
        mut.unlock();
        break;
      }
      fileName = fileNames.front();
      fileNames.pop();
      mut.unlock();
      fin.open(fileName);
      counter = 0;
      while (!fin.eof()) {
        string word;
        fin >> word;
        if (word == word_for_find) {
          counter++;
        }
      }
      fin.close();
      mut.lock();
      cout << fileName << ": " << counter << endl;
      mut.unlock();
    }
  }
};

void parallel_count() {
  vector<thread> threads(p);
  for (int i = 0; i < p; ++i) {

    threads[i] = thread(count_block());
  }

  for (auto &entry: threads)
    entry.join();
}

int main() {
  ifstream fin("files.txt");
  for (int i = 0; i < n; i++) {
    string word;
    getline(fin, word);
    fileNames.push(word);
  }
  fin.close();

  auto startTime = std::chrono::high_resolution_clock::now(); // start;
  parallel_count();

  auto endTime = std::chrono::high_resolution_clock::now(); // end;
  std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
            << " ms\n";
  return 0;
}*/
