#include <vector>
#include <iostream>
#include <iomanip>
#include "ThreadPool.h"
#include "Determinant.h"

void printMatrix(Determinant::type_matrix matrix) {
	for (auto list : matrix) {
		for (int el : list) {
			std::cout << std::setfill(' ') << std::setw(2) << el << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	int threadsCount;
	std::cout << "Enter threads count: ";
	std::cin >> threadsCount;
	ThreadPool pool(threadsCount);
	std::vector<std::future<int>> results;

	Determinant::type_matrix matrix = {
		{ 2,  3,  0,  5 },
		{ 4, -3, -1,  1 },
		{ 2,  5,  1,  3 },
		{ 2,  7,  2, -2 }
	};
	printMatrix(matrix);
	
	for (size_t i = 0; i < matrix.size(); ++i) {
		results.emplace_back(
			pool.enqueue(
				[i, matrix]() -> int {
					return pow(-1, i) * matrix[i][0] * Determinant::findDeterminant(Determinant::deletionLineAndRow(matrix, i, 0));
				}
			)
		);
	}
	int determinant = 0;
	for (auto&& result : results) {
		determinant += result.get();
	}
	std::cout << "Determinant is: " << determinant << std::endl;
}
