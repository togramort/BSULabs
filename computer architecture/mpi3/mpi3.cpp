#include <mpi.h>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include "Process.h"

class Program {
public:
    static void Main(int argc, char* argv[]) {
        srand(time(0));
        auto process = MPI::Process();
        int n = process.GetProcessCount();

        int k, l, m;

        k = atoi(argv[1]);
        l = atoi(argv[2]);
        m = atoi(argv[3]);

        float** matrix1 = nullptr;
        float** matrix2 = nullptr;
        float* matrix1ToVector = nullptr;
        float* matrix2ToVector = nullptr;
        

        int* firstSlices = nullptr;
        int* firstPosition = nullptr;
        int* secondSlices = nullptr;
        int* secondPosition = nullptr;
        int sliceSizes[2];
        double timestart, timefinish;

        if (process.IsMaster()) {

            matrix1 = new float* [k];
            for (int i = 0; i < k; i++) {
                matrix1[i] = new float[l];
            }

            matrix2 = new float* [l];
            for (int i = 0; i < l; i++) {
                matrix2[i] = new float[m];
            }

            fill(matrix1, k, l);
            fill(matrix2, l, m);

            std::cout << "number of processes: " << n << "\n";

            std::cout << "1st matrix: " << "\n";
            for (int i = 0; i < k; ++i) {
                for (int j = 0; j < l; ++j) {
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

            matrix1ToVector = convertToVector(matrix1, k, l);
            matrix2ToVector = convertToVector(matrix2, l, m);

            countSlices(n, l, k, firstSlices, firstPosition);
            countSlices(n, l, m, secondSlices, secondPosition);

            for (int i = 1; i < n; ++i) {
                sliceSizes[0] = firstSlices[i];
                sliceSizes[1] = secondSlices[i];

                MPI_Send(sliceSizes, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
            }

            sliceSizes[0] = firstSlices[0];
            sliceSizes[1] = secondSlices[0];
        } else {
            MPI_Recv(sliceSizes, 2, MPI_INT, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }

        float* sliceMatrix1 = new float[sliceSizes[0]];
        float* sliceMatrix2 = new float[sliceSizes[1]];

        MPI_Scatterv(matrix1ToVector, firstSlices, firstPosition, MPI_FLOAT, sliceMatrix1, sliceSizes[0], MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Scatterv(matrix2ToVector, secondSlices, secondPosition, MPI_FLOAT, sliceMatrix2, sliceSizes[1], MPI_FLOAT, 0, MPI_COMM_WORLD);

        timestart = MPI_Wtime();

        float* answer = nullptr;
        float* sliceResult = nullptr;
        sliceResult = multiply(sliceMatrix1, sliceMatrix2, k, sliceSizes[0] / k, m);

        if (process.IsMaster()) {
            answer = new float[k * m];
        }

        MPI_Reduce(sliceResult, answer, k * m, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        timefinish = MPI_Wtime();

        if (process.IsMaster()) {
            std::cout << "result:" << "\n";
            for (int i = 0; i < k; ++i) {
                for (int j = 0; j < m; ++j) {
                    std::cout << answer[i * m + j] << "\t";
                }
                std::cout << "\n";
            }
            std::cout << "\ntime: " << timefinish - timestart << "\n";
        }

        delete[] sliceMatrix1;
        delete[] sliceMatrix2;
        delete[] sliceResult;

        if (process.IsMaster()) {
            for (int i = 0; i < k; ++i) {
                delete[] matrix1[i];
            }
            delete[] matrix1;

            for (int i = 0; i < l; ++i) {
                delete[] matrix2[i];
            }
            delete[] matrix2;

            delete[] matrix1ToVector;
            delete[] matrix2ToVector;

            delete[] firstSlices;
            delete[] firstPosition;
            delete[] secondSlices;
            delete[] secondPosition;
            delete[] answer;
        }
    }

private:
    static float* multiply(float* firstMatrix, float* secondMatrix, int k, int l, int m) {
        float* answer = new float[k * m];

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < m; ++j) {
                answer[i * m + j] = 0;

                for (int p = 0; p < l; p++) {
                    answer[i * m + j] += firstMatrix[p * k + i] * secondMatrix[p * m + j];
                }
            }
        }

        return answer;
    }

    static void countSlices(int processCount, int n, int m, int*& slices, int*& positions) {
        slices = new int[processCount];
        positions = new int[processCount];
        std::fill(slices, slices + processCount, (n / processCount) * m);

        for (int i = 0; i < processCount; ++i) {
            positions[i] = i * (n / processCount) * m;
        }

        for (int i = 1, shift = 0; i < (n % processCount) + 1; ++i, shift += m) {
            slices[i] += m;
            positions[i] += shift;
        }
    }

    static void fill(float** matrix, int l, int m)
    {
        int x[] = { 0, -1 };
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = x[rand() % 2];
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
};

int main(int argc, char* argv[]) {
    Program::Main(argc, argv);

    return 0;
}
