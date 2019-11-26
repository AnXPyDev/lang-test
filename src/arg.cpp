#include <iostream>
#include <vector>
#include <string>

#include "core.hpp"
#include "arg.hpp"

using namespace lt;

std::vector<std::string> arg::parse(int argc, char** argv) {
  std::vector<std::string> result;
  for (unsigned int i = 0; i < argc; ++i) {
    result.push_back(argv[i]);
  };
  return result;
};

bool arg::exists(std::string name, std::vector<std::string> args) {
  for (auto it = args.begin(); it < args.end(); ++it) {
    if (*it == name) {
      return true;
    };
  };
  return false;
};

std::vector<std::string> arg::values(std::string name, std::vector<std::string> args) {
  std::vector<std::string> result;
  bool found = false;
  for (auto it = args.begin(); it < args.end(); ++it) {
    if (found) {
      if (std::string(*it).substr(0,1) != "-") {
        result.push_back(*it);
      } else {
        break;
      }
    } else if (*it == name) {
      found = true;
    };
  };
  return result;
};
