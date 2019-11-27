#pragma once

#include <string>
#include <vector>

#include "word.hpp"

namespace lt {};

namespace lt::parse {
  lt::Word* as_word(std::string str);
};
