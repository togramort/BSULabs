#include <omp.h>
#include <iostream>

class Program {
	const static int a = 1;
	const static int b = 10;

public:
	static void Main(int N) 
	{
		double startPoint = a;
		double h = (double)(b - a) / N;
		double res = 0;

#pragma omp parallel for schedule(static) reduction(+:res) firstprivate(startPoint, h)
		bool check = false;
		for (int i = 0; i < N; ++i) 
		{
			if (!check) 
			{
				check = true;
				startPoint += h * i;
			}
			else 
			{
				startPoint += h;
			}
			res += (std::pow(startPoint, (double)1 / 3)) * h;

		}
		std::cout << "result: " << res << "\n";
	}
};

int main(int argc, char* argv[])
{
	if (argc != 2 || std::atoi(argv[1]) < 1)
	{
		std::cout << "incorrect input parameters\n";
		return -1;
	}
	Program::Main(std::atoi(argv[1]));

	std::cout << "mein schones ergebnis: 15.408\n";
}