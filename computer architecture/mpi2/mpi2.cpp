#include <mpi.h>
#include <iostream>
#include <random>
#include <sstream>
#include "Process.h"

class Program {
public:
	static void Main() {

		srand(time(0));
		auto process = MPI::Process();
		int n = process.GetProcessCount();
		float** matrix1 = nullptr;
		float** matrix2 = nullptr;
		float* matrix1ToVector = nullptr;
		float* matrix2ToVector = nullptr;
		int l{}, m{};

		if (process.IsMaster()) {
			std::cout << "\ninput the parameters l, m\n";
			std::cin >> l >> m;
		}
		MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

		if (process.IsMaster()) {

			matrix1 = new float* [l];
			for (int i = 0; i < l; i++) {
				matrix1[i] = new float[m];
			}

			matrix2 = new float* [l];
			for (int i = 0; i < l; i++) {
				matrix2[i] = new float[m];
			}

			fill(matrix1, l, m);
			fill(matrix2, l, m);

			std::cout << "number of processes: " << n << "\n";

			std::cout << "1st matrix: " << "\n";
			for (int i = 0; i < l; ++i) {
				for (int j = 0; j < m; ++j) {
					std::cout << matrix1[i][j] << "\t";
				}
				std::cout << "\n";
			}
			std::cout << "\n";

			std::cout << "2nd matrix: " << "\n";
			for (int i = 0; i < l; ++i) {
				for (int j = 0; j < m; ++j) {
					std::cout << matrix2[i][j] << "\t";
				}
				std::cout << "\n";
			}
			std::cout << "\n";

			matrix1ToVector = convertToVector(matrix1, l, m);
			matrix2ToVector = convertToVector(matrix2, l, m);			
		}

		const int sliceSize = l * m / n + 1;
		float* sliceMatrix1 = new float[sliceSize];
		float* sliceMatrix2 = new float[sliceSize];

		int* sizes = new int[n];
		int* displs = new int[n];

		fillSizes(sizes, n, l * m, displs);

		MPI_Scatterv(matrix1ToVector, sizes, displs, MPI_FLOAT, sliceMatrix1, sizes[process.GetRank()], MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Scatterv(matrix2ToVector, sizes, displs, MPI_FLOAT, sliceMatrix2, sizes[process.GetRank()], MPI_FLOAT, 0, MPI_COMM_WORLD);

		float* sliceResult = new float[sizes[process.GetRank()]];

		float* answer = new float[l * m];

		for (int i = 0; i < sizes[process.GetRank()]; ++i) {
			sliceResult[i] = sliceMatrix1[i] + sliceMatrix2[i];
		}
	
		MPI_Gatherv(sliceResult, sizes[process.GetRank()], MPI_FLOAT, answer, sizes, displs, MPI_FLOAT, 0, MPI_COMM_WORLD);

		if (process.IsMaster()) {
			std::cout << "answer matrix" << "\n";

			for (int i = 0; i < l; ++i) {
				for (int j = 0; j < m; ++j) {
					std::cout << answer[i * m + j] << "\t";
				}
				std::cout << "\n";
			}

			for (int i = 0; i < l; ++i) {
				delete[] matrix1[i];
			}
			delete[] matrix1;

			for (int i = 0; i < l; ++i) {
				delete[] matrix2[i];
			}
			delete[] matrix2;

			delete[] matrix1ToVector;
			delete[] matrix2ToVector;
			delete[] answer;
		}

		delete[] sliceMatrix1;
		delete[] sliceMatrix2;
		delete[] displs;
		delete[] sizes;
	}

private:

	static void fill(float** matrix, int l, int m)
	{
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < m; ++j) {
				matrix[i][j] = (rand() % 9);
			}
		}
	}

	static float* convertToVector(float** matrix, int l, int m)
	{
		float* answer = new float[l * m];

		for (int i = 0; i < l; i++) {
			for (int j = 0; j < m; j++) {
				answer[i * m + j] = matrix[i][j];
			}
		}
		return answer;
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