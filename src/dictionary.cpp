#include <vector>
#include <map>
#include <string>

#include "definition.hpp"
#include "dictionary.hpp"

lt::Dictionary::Dictionary() {};

void lt::Dictionary::initialize_language(std::string language) {
  if (this->definitions_by_lang.find(language) == this->definitions_by_lang.end()) {
    this->definitions_by_lang[language] = *(new std::vector<lt::Definition*>);
  };
  if (this->definitions_by_lang_and_word.find(language) == this->definitions_by_lang_and_word.end()) {
    this->definitions_by_lang_and_word[language] = *(new std::map<std::string, lt::Definition*>);
  };
};

lt::Definition* lt::Dictionary::initialize_definition(std::string language, std::string word) {
  this->initialize_language(language);
  if (this->definitions_by_lang_and_word[language].find(word) == this->definitions_by_lang_and_word[language].end()) {
    auto definition = new lt::Definition(language, word);
    this->definitions_by_lang_and_word[language][word] = definition;
    this->definitions_by_lang[language].push_back(definition);
    this->all_definitions.push_back(definition);
  };
  return this->definitions_by_lang_and_word[language][word];
};

void lt::Dictionary::set_translation(std::string language1, std::string word1, std::string language2, std::string word2, bool one_way) {
  auto definition1 = this->initialize_definition(language1, word1);
  auto definition2 = this->initialize_definition(language2, word2);
  definition1->add_translation(definition2);
  if (!one_way) {
    definition2->add_translation(definition1);
  };
};
