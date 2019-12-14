#pragma once

#include <vector>
#include <string>
#include <map>

#include "definition.hpp"

namespace lt {
  struct Dictionary;
}

struct lt::Dictionary {
  std::map<std::string, std::map<std::string, lt::Definition*>> definitions_by_lang_and_word;
  std::map<std::string, std::vector<lt::Definition*>> definitions_by_lang;
  std::vector<lt::Definition*> all_definitions;
  void initialize_language(std::string language);
  lt::Definition* initialize_definition(std::string language, std::string word);
  void set_translation(std::string language1, std::string word1, std::string language2, std::string word2, bool one_way = false);
  std::vector<lt::Definition*> get_language(std::string language);
  std::vector<lt::Definition*> get_translatable(std::string from, std::string to);
  Dictionary();
};
