#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <algorithm>
#include <thread>

template<typename T>

class threadsafe_queue {
 private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

 public:
  threadsafe_queue(){}

  threadsafe_queue(threadsafe_queue const& other) {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }

  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty();});
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty();});
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return false;
    }
    value = data_queue.front();
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return true;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};

using namespace std::chrono_literals;

std::ifstream in ("input.txt");
std::ofstream out ("output.txt", std::ios::app);

threadsafe_queue<std::string> q;
/*std::mutex mut;
std::condition_variable cv;*/
bool finished {false};

static void producer() {
  while(!in.eof()) {
    std::string temp;
    std::getline(in, temp);
    q.push(temp);
  }
  finished = true;
}

static void consumer() {
  std::string line;
  while (!finished) {
    while (!q.empty()) {
      q.wait_and_pop(line);
      std::reverse(line.begin(), line.end());
      out << "Got " << line
          << " from queue.\n";
    }
  }
}

int main() {
  auto start = std::chrono::steady_clock::now();
  std::thread t1{producer};
  std::thread t2{consumer};
  t1.join();
  t2.join();
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  out << "finished!\n";
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
