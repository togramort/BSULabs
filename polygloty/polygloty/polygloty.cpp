#include <iostream>
int main() {
  int N, S1, S2, S3, S4, P;
  std::cin >> N >> S1 >> S2 >> S3 >> S4;
  P = (S1 + S2 + S3 + S4) - 3 * N;
  if ((S1 + S2 + S3 + S4) <= 3 * N) {
    P = 0;
  }
  std::cout << P;
}
