/*#include <iostream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <algorithm>

using namespace std::chrono_literals;

std::ifstream in ("input.txt");
std::ofstream out ("output.txt", std::ios::app);

std::queue<std::string> q;
std::mutex mut;
std::condition_variable cv;
bool finished {false};

static void producer() {
  while(!in.eof()) {
    std::string temp;
    std::getline(in, temp);
    std::lock_guard<std::mutex> lk {mut};
    q.push(temp);
    cv.notify_all();
  }
  std::lock_guard<std::mutex> lk {mut};
  finished = true;

  cv.notify_all();
}

static void consumer() {
  while (!finished) {
    std::unique_lock<std::mutex> l {mut};
    cv.wait(l, [] { return !q.empty() || finished; });
    while (!q.empty()) {
      std::reverse(q.front().begin(), q.front().end());
      out << "Got " << q.front()
           << " from queue.\n";
      q.pop();
    }
  }
}

int main() {
  auto start = std::chrono::steady_clock::now();
  std::thread t1 {producer};
  std::thread t2 {consumer};
  t1.join();
  t2.join();
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  out << "finished!\n";
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}*/

#include <iostream>
#include <queue>
#include <condition_variable>
#include <fstream>
#include <algorithm>

int main() {
  std::ifstream in ("input.txt");
  std::ofstream out ("sec_output.txt", std::ios::app);

  auto start = std::chrono::steady_clock::now();
  std::queue<std::string> q;
  while(!in.eof()) {
      std::string temp;
      std::getline(in, temp);
      q.push(temp);
  }
  while (!q.empty()) {
    std::reverse(q.front().begin(), q.front().end());
    out << "Got " << q.front()
        << " from queue.\n";
    q.pop();
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  out << "finished!\n";
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
