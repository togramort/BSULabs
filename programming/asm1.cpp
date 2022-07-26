#include <iostream>
#include <cmath>

int asm_func(int n, int m)
{
	unsigned int result;
	_asm
	{
		mov    eax, n
		mov    ecx, m
		mov    edi, 10
		mov    ebx, 0

		cmp    ecx, 0
		jz    no_for

		for:
				mov    edx, 0
				div    edi
				add    ebx, edx
		loop    for

		no_for:
		mov result, ebx	
	}
	return result;
}

int c_func(int n, int m) {
	int part = 0;
	int d = std::pow(10, m);
	n %= d;
	for (int i = 0; i < m; ++i) {
		part += n % 10;
		n /= 10;
	}
	return part;
}

int count(int n) {
	int x = 0;
	while (n != 0) {
		n /= 10;
		++x;
	}
	return x;
}

int main()
{
	float n, m;
	std::cout << "enter numbers: ";
	std::cin >> n >> m;
	if (m != (int)m || n != (int)n) {
		std::cerr << "not int";
		return -1;
	}
	if (m > count(n) || m <= 0) {
		std::cerr << "fu";
		return -1;
	}
	std::cout << "asm res: " << asm_func(n, m) << "\n" << "c++ res: " << c_func(n, m);
	return 0;
}