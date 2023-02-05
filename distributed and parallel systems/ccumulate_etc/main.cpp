11.11.2022
Новик Арина Вячеславовна
1
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    int n;
    std::cout << "Enter len of vector\n";
    std::cin >> n;
    std::cout << "Enter elements\n";
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
    QueryPerformanceFrequency(&liFrequency);
    // получаем стартовое время


    std::cout << "Sum : " << std::accumulate(vec.begin(), vec.end(), 0) << '\n';

    QueryPerformanceCounter(&liFinishTime);
    // вычисляет время в миллисекундах

    double dElapsedTime = 1000. * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;

    std::cout << "time : " << dElapsedTime;
    return 0;
}
2
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define p 3 // кол-во потоков
std::vector<int> vec; // начальный вектор
std::vector<std::vector<int>> vectors;

std::vector<int> answer = std::vector<int>(p);

DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
    int kParam = (int)pvParam;

    answer[kParam] = std::accumulate(vectors[kParam].begin(), vectors[kParam].end(), 0);

    return 0;
}
int main()
{
    HANDLE hThreads[p];
    int n;
    std::cout << "Enter len of vector\n";
    std::cin >> n;
    std::cout << "Enter elements\n";
    vectors = std::vector<std::vector<int>>(p);
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        vec.push_back(temp);
    }
    for (int i = 0; i < n; ++i) {
        vectors[i % p].push_back(vec[i]);
    }

    LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
    QueryPerformanceFrequency(&liFrequency);
    // получаем стартовое время
    QueryPerformanceCounter(&liStartTime);
    // создание дочерних потоков

    for (int k = 0; k < p; ++k)
    {
        hThreads[k] = (HANDLE)_beginthreadex(NULL, 0,
            (_beginthreadex_proc_type)ThreadFunction, (LPVOID)k, 0, NULL);
        if (hThreads[k] == NULL) // обработка ошибки
        {
            printf("Create Thread %d Error=%d\n", k, GetLastError());
            return -1;
        }
    }
    // ожидание завершения дочерних потоков
    WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
    for (int k = 0; k < p; ++k)
        CloseHandle(hThreads[k]);

    std::cout << "Sum : " << std::accumulate(answer.begin(), answer.end(), 0) << '\n';

    QueryPerformanceCounter(&liFinishTime);
    // вычисляет время в миллисекундах

    double dElapsedTime = 1000. * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;

    std::cout << "time : " << dElapsedTime;
    return 0;
}

