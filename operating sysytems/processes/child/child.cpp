#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, wchar_t** argv)
{
    int n = argc - 1;
    std::vector<wchar_t> arr(n);

    for (int i = 0; i < n; ++i) {
        arr[i] = argv[i + 1][0];
    }

    int min_idx = 0;
    for (int i = 0; i < n; ++i) {
        min_idx = std::distance(arr.begin(), std::min_element(arr.begin() + i, arr.end()));
        std::swap(arr[i], arr[min_idx]);
    }

    std::cout << "sorted arrayu:\n";
    for (int i = 0; i < n; ++i) {
        std::wcout << arr[i] << " ";
    }
    std::wcout << "\n";
    
    system("pause");

    return 0;
}