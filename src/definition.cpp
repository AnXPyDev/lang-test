#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "definition.hpp"
#include "strlib.hpp"

using namespace lt;

lt::Definition::Definition(std::string language, std::string word) {
  this->language = language;
  this->word = word;
};

void lt::Definition::initialize_language(std::string language) {
  if (this->translations_by_language.find(language) == this->translations_by_language.end()) {
    this->translations_by_language[language] = *(new std::vector<lt::Definition*>());
  };
};

void lt::Definition::add_translation(lt::Definition* translation) {
  this->all_translations.push_back(translation);
  this->initialize_language(translation->language);
  this->translations_by_language[translation->language].push_back(translation);
};

std::vector<lt::Definition*> lt::Definition::get_translation(std::string language) {
  this->initialize_language(language);
  return this->translations_by_language[language];
};
