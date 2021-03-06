#pragma once

#include <string>
#include <map>
#include <vector>

namespace lt {
  struct Word;
}

struct lt::Word {
  std::map<std::string, std::vector<std::string>> definitions;
  void define(std::string key, std::string definition);
  void define(std::string key, std::vector<std::string> definitions);
  void initialize_definition(std::string key);
  std::vector<std::string> get_definition(std::string key);
  float compare_to_definition(std::string key, std::string str);
  std::string substitute_string(const std::string& str);
  Word();
};
