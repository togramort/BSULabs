#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <iostream>
#include <future>
#include <asyncinfo.h>
#include <random>
#include <vector>
using namespace std;
using task_type = long(long*, long, long);
int main()
{
  random_device rnd_device;
  mt19937 mersenne_engine{ rnd_device() };
  uniform_int_distribution<int> dist{ 1, 52 };
  auto gen = [&dist, &mersenne_engine]() {
    return dist(mersenne_engine);
  };
  vector<int> vec(100000000);
  generate(begin(vec), end(vec), gen);
  vector<int>::iterator it;
  auto start1 = chrono::high_resolution_clock::now();
  it = max_element(vec.begin(), vec.end());
  auto end1 = chrono::high_resolution_clock::now();
  cout << *it;
  cout << "Time of execution: " << chrono::duration_cast<chrono::milliseconds>(end1 -
      start1).count() << " ms" << endl;
}
///////////////////////////////////////////////
#include <iostream>
#include <future>
#include <asyncinfo.h>
#include <random>
#include <vector>
using namespace std;
using task_type = long(long*, long, long);
long find_max(long* num_vector, long step, long n) {
  long max = num_vector[step];
  for (long i = 1; i < n; i++) {
    if (num_vector[step + i] > max) {
      max = num_vector[step + i];
    };
  };
  return max;
}
long parallel(long* num_vector, long n, long thread_num) {
  long sqrt_num = thread_num - 1;
  long step = n / thread_num;
  auto pcg_tasks = new packaged_task<task_type>[sqrt_num + 1];
  for (long i = 0; i < sqrt_num + 1; i++) {
    pcg_tasks[i] = packaged_task<task_type>(find_max);
  };
  auto futures = new future<long>[sqrt_num + 1];
  for (long i = 0; i < sqrt_num + 1; i++) {
    futures[i] = pcg_tasks[i].get_future();
  };
  for (long i = 0; i < sqrt_num; i++) {
    async(move(pcg_tasks[i]), num_vector, i * step, step);
  };
  async(move(pcg_tasks[sqrt_num]), num_vector, step * sqrt_num, n - step * sqrt_num);
  long* res = new long[sqrt_num + 1];
  for (long i = 0; i < sqrt_num + 1; i++) {
    res[i] = futures[i].get();
  };
  packaged_task<task_type> last_pack(find_max);
  future<long> last_future(last_pack.get_future());
  async(move(last_pack), res, 0, sqrt_num + 1);
  return last_future.get();
}
long main() {
  long size = 1000000;
  long thread_count = 1;
  srand(time(NULL));
  long* num_vector = new long[size];
  for (long i = 0; i < size; i++)
  {
    num_vector[i] = rand() % 200 - 100;
  }
  auto start1 = chrono::high_resolution_clock::now();
  auto max = parallel(num_vector, size, thread_count);
  auto end1 = chrono::high_resolution_clock::now();
  cout << "Max value: " << max << endl;
  cout << "Time of execution: " << chrono::duration_cast<chrono::milliseconds>(end1 -
      start1).count() << " ms" << endl;
}
