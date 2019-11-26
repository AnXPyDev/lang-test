#pragma once

#include <vector>
#include <string>

#include "core.hpp"

namespace lt::strlib {
  std::vector<std::string> split(std::string str, std::string delimiter);
  std::string strip(std::string str, char to_strip);
  unsigned int edit_distance(std::string a, std::string b);
  unsigned int edit_distance(std::wstring a, std::wstring b);
  float percentual_similiarity(std::string a, std::string b);
  float percentual_similiarity(std::wstring a, std::wstring b);
  std::wstring string_to_wstring(std::string str);
};
