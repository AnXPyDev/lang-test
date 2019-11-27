#pragma once

#include <vector>
#include <string>

namespace lt {};

namespace lt::strlib {
  std::vector<std::string> split(std::string str, std::string delimiter);
  std::string strip(std::string str, char to_strip);
  size_t edit_distance(std::string a, std::string b);
  size_t edit_distance(std::wstring a, std::wstring b);
  float percentual_similiarity(std::string a, std::string b);
  float percentual_similiarity(std::wstring a, std::wstring b);
  std::wstring string_to_wstring(std::string str);
};
