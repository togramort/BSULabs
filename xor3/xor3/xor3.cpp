#include <iostream>

int main() {

    unsigned int key;
    std::cout << "key " << "\n";
    std::cin >> key;

    int n;
    std::cout << "enter size of the array " << "\n";
    std::cin >> n;

    char* a = new char[n];
    std::cout << "array: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    char enc, dec;
    std::cout << "encrypted: ";
    for (int i = 0; i < n; ++i) {
        enc = a[i] ^ key;
        a[i] = enc;
        std::cout << enc << " ";
    }
    std::cout << "\n";
    std::cout << "decrypted: ";
    for (int i = 0; i < n; ++i) {
        dec = a[i] ^ key;
        std::cout <<  dec << " ";
    }
    delete[] a;
    return 0;
}
