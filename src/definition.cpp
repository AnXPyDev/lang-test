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
  this->add_translation(this);
}

void lt::Definition::initialize_language(std::string language) {
  if (this->translations_by_language.find(language) == this->translations_by_language.end()) {
    this->translations_by_language[language] = *(new std::vector<lt::Definition*>());
  }
}

void lt::Definition::add_translation(lt::Definition* translation) {
  for (auto it = this->all_translations.begin(); it < this->all_translations.end(); ++it) {
    if (translation == *it) {
      return;
    }
  }
  this->all_translations.push_back(translation);
  this->initialize_language(translation->language);
  this->translations_by_language[translation->language].push_back(translation);
}

std::vector<lt::Definition*> lt::Definition::get_translation(std::string language) {
  this->initialize_language(language);
  return this->translations_by_language[language];
}

float lt::Definition::check_translation(std::string language, std::string word) {
  this->initialize_language(language);
  float result = 0;
  for (auto it = this->translations_by_language[language].begin(); it < this->translations_by_language[language].end(); ++it) {
    float current = strlib::percentual_similiarity(strlib::string_to_wstring(word), strlib::string_to_wstring((*it)->word));
    result = (current > result ? current : result);
  }
  return result;
}

std::string strlib::concat(std::vector<lt::Definition*> def, std::string delimiter) {
  std::string result = "";
  for (unsigned int i = 0; i < def.size(); ++i) {
    result += def[i]->word;
    if (i < def.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}
