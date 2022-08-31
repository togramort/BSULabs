#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

HANDLE hOutEvent, hStartSumEvent;
CRITICAL_SECTION cs;

struct data {
    std::vector<char> arr_;
    int k_;
    double sum_;

    data(std::vector<char> arr, int k, double sum) {
        arr_ = arr;
        k_ = k;
        sum_ = sum;
    }
};

unsigned __stdcall work(data* data) {
    int time;
    std::cout << "please enter sleep time for each element in ms\n";
    std::cin >> time;

    int min_idx = 0;
    for (int i = 0; i < (*data).arr_.size(); ++i) {

        min_idx = std::distance((*data).arr_.begin(), std::min_element((*data).arr_.begin() + i, (*data).arr_.end()));
        std::swap((*data).arr_[i], (*data).arr_[min_idx]);
        Sleep(time);

        if (i == (*data).k_) {
            SetEvent(hOutEvent);
        }
    }

    return 0;
}

unsigned __stdcall sum_element(data* data) {
    EnterCriticalSection(&cs);
    WaitForSingleObject(hStartSumEvent, INFINITE);

    for (int i = 0; i < (*data).k_; ++i) {
        (*data).sum_ += (double)(*data).arr_[i];
    }

    (*data).sum_ /= (*data).k_;
    LeaveCriticalSection(&cs);

    return 0;
}

int main() {
    int n;
    std::cout << "enter size and array\n";
    std::cin >> n;

    std::vector<char> arr(n);
    for (int i = 0; i < arr.size(); ++i) {
        std::cin >> arr[i];
    }

    std::cout << "here is ur array!\n{";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << " " << arr[i] << " ";
    }
    std::cout << "}\nsize is: " << n << "\n";

    int k;
    std::cout << "now pls enter random integer number less than size of an array\n";
    std::cin >> k;

    InitializeCriticalSection(&cs);

    hOutEvent = CreateEvent(nullptr, false, false, nullptr);
    if (hOutEvent == nullptr) {
        return GetLastError();
    }
    hStartSumEvent = CreateEvent(nullptr, false, false, nullptr);
    if (hStartSumEvent == nullptr) {
        return GetLastError();
    }
    
    double sum = 0;
    data data(arr, k, sum);

    HANDLE hWork, hSum;
    DWORD idWork, idSum;

    hSum = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)sum_element, &data, 0, &idSum);
    hWork = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)work, &data, 0, &idWork);

    if (hWork == nullptr || hSum == nullptr) {
        return GetLastError();
    }

    WaitForSingleObject(hOutEvent, INFINITE);
    arr = data.arr_;
    std::cout << "array after sorting but from main:\n{ ";
    for (int i = 0; i < k; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "}\n";

    SetEvent(hStartSumEvent);

    EnterCriticalSection(&cs);
    sum = data.sum_;
    std::cout << "result of sum element: " << sum << "\n";
    LeaveCriticalSection(&cs);

    DeleteCriticalSection(&cs);

    WaitForSingleObject(hWork, INFINITE);

    arr = data.arr_;
    std::cout << "the rest of the array:\n{ ";
    for (int i = k; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "}\n";

    CloseHandle(hWork);
    CloseHandle(hSum);

    return 0;
}