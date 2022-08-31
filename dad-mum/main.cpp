#include <iostream>
#include <thread>
#include "Say.h"

int main() {
  Say word1 (500, 10, "mum"), word2 (550, 12, "dad"), word3(5000, 1, "u");
  std::thread t1(&Say::say, &word1);
  std::thread t2(&Say::say, &word2);
  std::thread t3(&Say::say, &word3);
  t1.join();
  t2.join();
  t3.join();
  std::cout << "\nthe amount of words: " << Say::cur_amount;

  return 0;
}