#pragma once

#include <string>
#include <vector>


#include "word.hpp"
#include "dictionary.hpp"

namespace lt {};

namespace lt::parse {
  lt::Word* as_word(std::string str);
  void to_dictionary(std::string str, lt::Dictionary* dictionary);
};
