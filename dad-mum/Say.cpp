#include <iostream>
#include <thread>
#include <utility>
#include <mutex>
#include "Say.h"


int Say::cur_amount = 0;
int Say::max_amount = 3;

Say::Say(int ms, int n, std::string word) {
  ms_ = ms;
  n_ = n;
  word_= std::move(word);
}

std::mutex mtx;
void Say::say() {
  for (int i = 0; i < n_; ++i) {
    if (cur_amount == max_amount) {
      break;
    }
    mtx.lock();
    std::cout << word_ << " ";
    ++cur_amount;
    mtx.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_));
  }
}