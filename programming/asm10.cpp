#include <iostream>

int funcc(char* str, char* substr) {
    int idx = 0;
    for (int i = strlen(substr) - 1; i > -1;) {
        bool prev = false;
        for (int j = strlen(str); j > -1; --j) {
            if (substr[i] == str[j]) {
                prev = true;
                idx = j;
                --i;
            }
            else if (substr[i] == str[j] && !prev && i != strlen(substr) - 1) {
                std::cout << "there is no subsring in this string\n";
                return 0;
            }
        }
    }
    if (idx == 0) {
        std::cout << "there is no subsring in this string\n";
    }
    else {
        return idx;
    }
    return 0;
}

int funcasm(char* str, char* substr)
{
    int strSize = strlen(str);
    int substrSize = strlen(substr);
    char* current;
    _asm
    {
        mov eax, strSize;
        sub eax, substrSize;

        cmp eax, 0;
        jl no_str;

        mov edi, str;
        mov esi, substr;

        add edi, eax;
        mov current, edi;

    try_str:
        mov edi, current;
        cmp edi, str;
        jl no_str;

        mov esi, substr;
        dec current;
        mov ecx, substrSize;
        repe cmpsb;

        jne try_str;

    found_str:
        mov eax, current;
        sub eax, str;
        inc eax;
        jmp return_str;

    no_str:
        mov eax, -1;
    return_str:
    }
}

int main()
{
    char string[] = "123123";
    char substring[] = "1234";
    std::cout /*<< "c++ " << funcc(string, substring)*/ << "\nasm " << funcasm(string, substring);
    return 0; 
}