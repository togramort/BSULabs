#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    int n;
    std::cout << "enter size and array\n";
    std::cin >> n;

    std::wstring arr;
    wchar_t temp;
    for (int i = 0; i < n; ++i) {
        std::wcin >> temp;
        arr.push_back(temp);
        arr += L" ";
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USECOUNTCHARS;
    si.dwYCountChars = 1000;
    ZeroMemory(&pi, sizeof(pi));

    std::wstring command = L"child.exe " + arr;
    //wchar_t stemp[300];
    //mbstowcs_s(0 , stemp, command.c_str(), command.length());
    wchar_t* s = (wchar_t*)command.c_str();


    if (!CreateProcess(NULL, s, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        std::cout << "cannot create process... error: " << GetLastError();
    }
    else {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    return 0;
}