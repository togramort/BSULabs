#include <omp.h>
#include <iostream>

class Program
{
public:
	static void Main(int b, int N)
	{
		double a = -1;
		double h = (double)(b - a) / N + 1;

		double startValue = 0;
		double tmp = 0;
		double maxValue = DBL_MIN;
		double startDivide = (double) (b + 1) / 4;

		h /= 4;

		omp_set_nested(true);

#pragma omp parallel sections firstprivate(startValue, a, tmp, startDivide) 
		{
#pragma omp section 
			{
				a = -1;
#pragma omp parallel for schedule(static) firstprivate(startValue,a,tmp)

				for (int i = 0; i < N; ++i)
				{
					startValue = countValue(a + h * i);
					tmp = std::abs((countValue(a + h * (i + 1)) - startValue) / h);
#pragma omp critical 
					{

						if (tmp > maxValue)
						{
							maxValue = tmp;
						}

					}
				}
			}
#pragma omp section 
			{
				a = -1 + startDivide;
#pragma omp parallel for schedule(static) firstprivate(startValue,a,tmp)

				for (int i = 0; i < N; ++i)
				{
					startValue = countValue(a + h * i);
					tmp = fabs((countValue(a + h * (i + 1)) - startValue) / h);
#pragma omp critical 
					{

						if (tmp > maxValue)
						{
							maxValue = tmp;
						}

					}
				}
			}

#pragma omp section 
			{
				a = -1 + startDivide * 2;
#pragma omp parallel for schedule(static) firstprivate(startValue,a,tmp)

				for (int i = 0; i < N; ++i)
				{
					startValue = countValue(a + h * i);
					tmp = fabs((countValue(a + h * (i + 1)) - startValue) / h);
#pragma omp critical 
					{

						if (tmp > maxValue)
						{
							maxValue = tmp;
						}

					}
				}
			}

#pragma omp section 
			{
				a = -1 + startDivide * 3;
#pragma omp parallel for schedule(static) firstprivate(startValue,a,tmp)

				for (int i = 0; i < N; ++i)
				{
					startValue = countValue(a + h * i);
					tmp = fabs((countValue(a + h * (i + 1)) - startValue) / h);
#pragma omp critical 
					{

						if (tmp > maxValue)
						{
							maxValue = tmp;
						}

					}
				}
			}
		}

		std::cout << "result: " << maxValue << "\n";

		}

private:
	static double countValue(double x)
	{
		return x <= 1 ? (x * x - 5 * x / 2 + (double)1 / 2) : (-std::pow(x, (double)1 / 2));
	}
};


int main(int argc, char* argv[])
{
	if (argc != 3 || std::atoi(argv[2]) < 1 || std::atoi(argv[1]) <= 1)
	{
		std::cout << "incorrect parameters";
		return -1;
	}

	Program::Main(std::atoi(argv[1]), std::atoi(argv[2]));

	std::cout << "mein schones ergebnis (b = 5): 4.5\n";
}