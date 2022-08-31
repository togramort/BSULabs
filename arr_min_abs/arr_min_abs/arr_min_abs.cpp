#include<iostream>
#include<random>
#include<cmath>
#include<ctime>
#include<algorithm>

int main() {

    int r, n;
    std::cout << "enter the size of array: " << "\n";
    std::cin >> n;
    if (n < 0) {
        std::cout << "error" << "\n";
        return 0;
    }

    std::cout << "choose the type of input:\n1 - random\n2 - from keyboard" << "\n";
    std::cin >> r;

    std::mt19937 gen((unsigned int)time(nullptr));
    std::uniform_real_distribution<double>urd(-100, 100);

    double *a = new double[n];
    if (r == 1) {
        std::cout << "array:";
        for (int i = 0; i < n; ++i) {
            a[i] = urd(gen);
            std::cout << " " << a[i];
        }
        std::cout << "\n";
    }
    else if (r == 2) {
        std::cout << "enter numbers of array: " << "\n";
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
    }
    else {
        std::cout << "enter only 1 or 2!";  
        return 0;
    }

    double min = abs(a[0]);
    int imin = 0;
    for (int i = 0; i < n; ++i) {
        if (abs(a[i]) <= min) {
            min = abs(a[i]); 
            imin = i + 1;
        } 
    }    
    std::cout << "index of minimum modulo: " << imin << "\n";

    double sum = 0; 
     int ineg = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] < 0) {
            ineg = i;
            break;
        }
    }
    for (int i = ineg + 1; i < n; ++i) {
            sum += abs(a[i]);
    }
    if (ineg == -1) {
        std::cout << "no negatives in array" << "\n";
    }
    else {
        std::cout << "sum after negative number: " << sum << "\n";
    }

    int l = 0; 
    for (int i = 0; i < n; ++i) {
        if (a[i] < 2 || a[i] > 7) {
            a[l] = a[i];
            ++l;
        }
    }
    for (int i = l; i < n; ++i) {
        a[i] = 0;
    }
    std::cout << "reformed array:";
    for (int i = 0; i < n; ++i) {
         std::cout << " " << a[i];
    }
    delete[] a;
    return 0;
}