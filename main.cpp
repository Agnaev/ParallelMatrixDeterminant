#include <vector>
#include <iostream>
#include "ThreadPool.h"
#include "Determinant.h"

int main() {
	int threadsCount;
	std::cout << "Enter threads count: ";
	std::cin >> threadsCount;
	ThreadPool pool(threadsCount);
	std::vector<std::future<int>> results;

	Determinant::type_matrix matrix = {
		{ 4, 5, 2 },
		{ 6, 4, 7 },
		{ 8, 6, 2 }
	};
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
	std::cout << determinant << std::endl;
}
