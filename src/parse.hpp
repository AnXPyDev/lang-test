#pragma once

#include <string>
#include <vector>

#include "core.hpp"
#include "word.hpp"

using namespace lt;

namespace lt::parse {
  Word* as_word(std::string str);
};
