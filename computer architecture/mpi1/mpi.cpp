#include "Process.h"
#include <mpi.h>
#include <iostream>
#include <random>

class Program {
public:
	static void Main() {
		srand(time(0));

		auto process = MPI::Process();
		int n = process.GetProcessCount();
		const int l = 10;
		float* array1 = nullptr;
		float* array2 = nullptr;

		if (process.IsMaster()) {
			array1 = new float[l];
			array2 = new float[l];

			fill(array1, l);
			fill(array2, l);

			std::cout << "number of processes: " << n << "\n";

			std::cout << "1st array: " << "\n";
			for (int i = 0; i < l; ++i) {
				std::cout << array1[i] << "\t";
			}
			std::cout << "\n";

			std::cout << "2nd array: " << "\n";
			for (int i = 0; i < l; ++i) {
				std::cout << array2[i] << "\t";
			}
			std::cout << "\n";
		}

		const int sliceSize = (l + n - 1) / n;
		float* sliceArr1 = new float[sliceSize];
		float* sliceArr2 = new float[sliceSize];
		
		int* sizes = new int[n];
		int* displs = new int[n];

		fillSizes(sizes, n, l, displs);

		MPI_Scatterv(array1, sizes, displs, MPI_FLOAT, sliceArr1, sizes[process.GetRank()], MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Scatterv(array2, sizes, displs, MPI_FLOAT, sliceArr2, sizes[process.GetRank()], MPI_FLOAT, 0, MPI_COMM_WORLD);

		float result = 0;

		float answer = 0;

		for (int i = 0; i < sizes[process.GetRank()]; ++i) {
			result += sliceArr1[i] * sliceArr2[i];
		}

		MPI_Reduce(&result, &answer, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

		if (process.IsMaster()) {
			std::cout << "scalar multiplication = " << answer << "\n";
			delete[] array1;
			delete[] array2;
		}

		delete[] sliceArr1;
		delete[] sliceArr2;
	}

private:

	static void fill(float* data, int length)
	{
		float x[] = { -1, 0, 1 };

		for (auto i = 0; i < length; ++i) {
			data[i] = x[rand() % 3];
		}
	}

	static void fillSizes(int* sizes, int processCount, int length, int* displs)
	{
		if (length < processCount) {
			for (int i = length; i < processCount; ++i) {
				sizes[i] = 0;
			}
			processCount = length;
		}

		int tmpLength = length;
		for (int i = 0; i < processCount; ++i) {
			sizes[i] = (length / processCount);
			tmpLength -= (length / processCount);
		}
		
		while (tmpLength > 0) {
			for (int i = 0; i < tmpLength && i < processCount; ++i) {
				++sizes[i];
			}
			tmpLength -= processCount;
		}

		for (int i = 0; i < processCount; ++i) {
			if (i == 0) {
				displs[i] = 0;
			}
			else {
				displs[i] = displs[i - 1] + sizes[i - 1];
			}
		}

	}
};

int main()
{
	Program::Main();
	return 0;
}