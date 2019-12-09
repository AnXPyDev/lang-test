#pragma once

#include <vector>
#include <string>
#include <map>

namespace lt {
  struct Definition;
};

struct lt::Definition {
  std::string language;
  std::string word;
  std::vector<lt::Definition*> all_translations;
  std::map<std::string, std::vector<lt::Definition*>> translations_by_language;
  void initialize_language(std::string language);
  void add_translation(lt::Definition* translation);
  std::vector<lt::Definition*> get_translation(std::string language);
  Definition(std::string language, std::string word);
};
