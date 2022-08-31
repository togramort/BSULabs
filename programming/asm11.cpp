#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <tchar.h>
#include <float.h>
#include <math.h>

double cfunc(double x) {
    return std::pow(std::sin(x), 2);
}

double fpufunc(double x) {

    int temp = 1;
    _asm {
        finit
        fld1
        fld1
        fiadd temp
        fld x
        fmul st, st(1)
        fcos
        fsub st, st(2)
        fchs
        fdiv st, st(1)
    }
}

const double d1pow10[DBL_DIG] = {
        0.01,
        0.001,              // 1/(10^3)
        0.0001,             // 1/(10^4)
        0.00001,            // 1/(10^5)
        0.000001,           // 1/(10^6)
        0.0000001,          // 1/(10^7)
        0.00000001,         // 1/(10^8)
        0.000000001,        // 1/(10^9)
        0.0000000001,       // 1/(10^10)
        0.00000000001,      // 1/(10^11)
        0.000000000001,     // 1/(10^12)
        0.0000000000001,    // 1/(10^13)
        0.00000000000001,   // 1/(10^14)
        0.000000000000001,  // 1/(10^15)
};

double taylor(double x, int n) {
    // asm version by Taylor
    //    st(3)     result
    //    st(2)     x
    //    st(1)     step
    //    st(0)     eps
    _asm {
        ;// result = 0
        fldz
            ;// load x
        fld     x
            ;// step = x
        fld     st;
        // eps = 1 / 10^(n + 1)
        mov     ebx, n
            dec     ebx
            dec     ebx
            fld     qword ptr d1pow10[ebx * 8]
            ;// n = 1, ebx == n
        mov     ebx, 1
            mov     n, ebx
            ;// while( fabs( step ) >= eps ) {
        fld     st(1);
    next:
        fabs;// st= abs(step)
        fcomip  st, st(1);
        jna     finish;

        ;// result += step;
        fld     st(1);// st = step, st1 = eps, st2 = step, st3 = x, st4= result
        fadd    st(4), st
            ;// step = (( step * n ) * x )/( n + 1 );

        fmul    st, st(3);// st= (( step * n ) * x ), ...
        fmul    st, st(3)

            inc     n
            fidiv   n;// st = (( step * n ) * x )/( n + 1 )
        inc     n
            fidiv   n

            fchs

            fst     st(2);// step = st
        ;// }
        jmp     next
            finish :
        fstp    st;
        fstp    st;
        fstp    st;
        fmul st, st
        ; //fchs                ;// st = result * (-1)
    }
}

int main(int argc, char* argv[]) {

    double x;
    int k;

    _TCHAR fmt[80];

    if (argc != 3) {
        std::cout << "sth wrong with number of arguments. syntax: " << argv[0] << " x k\n";
        return -1;
    }

    x = std::atof(argv[1]);
    k = std::atoi(argv[2]);

    if (k <= 1 || k > DBL_DIG + 1) {
        std::cerr << "argument k must be in range ]1, " << DBL_DIG + 1 << "[\n";
        return -1;
    }

    _tprintf(_T("Started with arguments: %f  %d\n"), x, k);
    if (x > 2 * M_PI || x < -2 * M_PI) {
        long long int q = (long long int)(x / (2 * M_PI));
        x -= (q * 2 * M_PI);
    }

    _stprintf(fmt, _T("C version by RTL:\t %%.%df\n"), k);
    _tprintf(fmt, cfunc(x));

    _stprintf(fmt, _T("Asm version by FPU:\t %%.%df\n"), k);
    _tprintf(fmt, fpufunc(x));

    _stprintf(fmt, _T("Asm version by Taylor:\t %%.%df\n"), k);
    _tprintf(fmt, taylor(x, k));

    return 0;
}