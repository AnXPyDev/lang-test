#pragma once

#include <vector>
#include <string>

#include "core.hpp"

namespace lt::arg {
  std::vector<std::string> parse(int argc, char** argv);
  bool exists(std::string name, std::vector<std::string> args);
  std::vector<std::string> values(std::string name, std::vector<std::string> args);
};
