#include <iostream>
#include <vector>

long long fib(long long k) {
  std::vector<long long> v(k);
  v[0] = 1;
  if (k > 1) {
    v[1] = 2;
  }
  for (int i = 2; i < k; ++i) {
    v[i] = (v[i - 1] + v[i - 2]) % 1000000009;
  }
  return v[k - 1];
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  long long n, k;
  std::cin >> n >> k;

  std::vector<long long> v(n);
  v[0] = 1;
  long long res = fib(k);
  for (int i = 1; i < n; ++i) {
    v[i] = ((v[i - 1]) * ((res * res) % 1000000009 + 1)) % 1000000009;
  }
  std::cout << v[n - 1];
  return 0;
}