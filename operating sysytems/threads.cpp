#include <Windows.h>
#include <iostream>
#include <process.h>
#include <vector>

unsigned __stdcall workerxxx(void* arr) {

    std::vector<int> temp = *(std::vector<int> *) arr;
    unsigned int count = 0;
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == 0) {
            ++count;
        }
        Sleep(12);
    }
    std::cout << "there are/is " << count << " zero/s :D\n";
   // _endthreadex(0);
    return 0;
}

int main()
{
    int n;
    std::cout << "enter the size of the array \n";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "\n";
        std::cout << "dont mess w/ me boiiiii\n";
        return -666;
    }
    std::cout << "\n";

    std::vector<int> arr(n);
    std::cout << "fill the array \n";
    for (int i = 0; i < n; ++i) {
        //std::cin >> arr[i];
        arr[i] = 0; // to check Sleep(12) in workerxxx
    }
    std::cout << "\n";

    int delay;
    std::cout << "our thread needs time to get ready... how much time (in ms) youre ready to wait?\n";
    std::cin >> delay;

    if (delay < 0) {
        std::cout << "\n";
        std::cout << "dont mess w/ me boiiiii\n";
        return -666;
    }
    std::cout << "\n";

    HANDLE worker;
    DWORD threadID;

    worker = (HANDLE)_beginthreadex(NULL, 0, workerxxx, &arr, 0, (unsigned int*) & threadID);

    if (worker == NULL) {
        return GetLastError();
    }

    SuspendThread(worker);
    Sleep(delay);
    ResumeThread(worker);

   // WaitForSingleObject(worker, INFINITE);

    CloseHandle(worker);
    return 0;
}