#pragma once

#include <string>

#include "word.hpp"

namespace lt {
  struct Test_Template;
};

using namespace lt;

struct lt::Test {
  std::string prompt;
  std::string required_input;
  float word(Word* word);
  Test(std::string prompt, std::string required_input);
};
