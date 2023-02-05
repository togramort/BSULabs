#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <math.h>
#define p 4

typedef struct SThreadParam SThreadParam;
int n = 100000000;
struct SThreadParam{
  int k;
  double sum;
};

DWORD WINAPI ThreadFunction(LPVOID pvParam) {
  struct SThreadParam *param = (SThreadParam *) pvParam;
  double h, sum = 0, a = 4, b = 100, x;
  h = (b - a) / n;
  for (int i = param->k; i < n; i += p)  {
    x = i * h + a;
    if (x > b) {
      break;
    }
    sum += x * x;
  }
  param->sum = h * sum;
  return 0;
}

int main() {
  HANDLE hThreads[p];
  SThreadParam params[p];
  int k;
  double sum;
  LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
  QueryPerformanceFrequency(&liFrequency);
  QueryPerformanceCounter(&liStartTime);
  for (k = 0; k < p; ++k) {
    params[k].k = k;
    hThreads[k] = (HANDLE) _beginthreadex(NULL, 0,
                                          (unsigned int (*)(void *)) ThreadFunction, (LPVOID) &(params[k]), 0, NULL);
    if (hThreads[k] == NULL)
    {
      printf("Create Thread %d Error=%lu\n", k, GetLastError());
      return -1;
    }
  }
  WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
  for (k = 0; k < p; ++k) {
    CloseHandle(hThreads[k]);
  }
  QueryPerformanceCounter(&liFinishTime);
  double dElapsedTime = 1000. * (liFinishTime.QuadPart - liStartTime.QuadPart)/liFrequency.QuadPart;

  sum = 0;
  for (k = 0; k < p; ++k) {
    sum += params[k].sum;
  }

  printf("1 \\ log(x) = %.16f\n", sum);
  printf("time: %.16f", dElapsedTime);
  return 0;
}

