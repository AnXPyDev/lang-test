#pragma once

#include <vector>

namespace lt {}

namespace lt::random {
  int integer(int min, int max);
  std::vector<int> integer(int min, int max, unsigned int n);
  std::vector<int> unique_integer(int min, int max, unsigned int n);
}
