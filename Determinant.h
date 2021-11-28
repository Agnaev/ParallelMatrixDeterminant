#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <future>

namespace Determinant {
  typedef std::vector<std::vector<int>> type_matrix;

  type_matrix deletionLineAndRow(type_matrix, int, int);
  int findDeterminant(type_matrix);
};
