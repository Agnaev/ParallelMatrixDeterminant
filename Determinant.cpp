#include <numeric>
#include "Determinant.h"

Determinant::type_matrix Determinant::deletionLineAndRow(Determinant::type_matrix matrix, int delete_line, int delete_column) {
  int size = matrix.size();
  Determinant::type_matrix result = {};

  for (int line = 0, i = 0; line < size; line++, i++) {
    if (line == delete_line) {
      --i;
      continue;
    }
    result.push_back({});
    for (int column = 0, j = 0; column < size; column++, j++) {
      if (column == delete_column) {
        --j;
        continue;
      }

      result[i].push_back(matrix[line][column]);
    }
  }
  return result;
}

int Determinant::findDeterminant(Determinant::type_matrix matrix) {
  int size = matrix.size();
  if (size != matrix[0].size()) {
    throw std::exception("Empty matrix.");
  }
  if (size == 1) {
    return matrix[0][0];
  }
  if (size == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }
  int i = 0;
  auto accCallback = [&matrix, &i](int prevRes, std::vector<int>& line) -> int {
    return pow(-1, i) * line[i] * findDeterminant(deletionLineAndRow(matrix, i++, 0));
  };

  return std::accumulate(
    std::begin(matrix),
    std::end(matrix),
    0,
    accCallback
  );
}
