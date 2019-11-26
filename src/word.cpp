#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "core.hpp"
#include "strlib.hpp"
#include "word.hpp"

using namespace lt;

Word::Word() {};

void Word::initialize_definition(std::string key) {
  if (this->definitions.find(key) != this->definitions.end()) {
    return;
  };
  this->definitions[key] = *(new std::vector<std::string>);
}

void Word::define(std::string key, std::string definition) {
  this->initialize_definition(key);
  this->definitions[key].push_back(definition);
  //std::cout << key << " " << definition << std::endl;
}

void Word::define(std::string key, std::vector<std::string> definitions) {
  this->initialize_definition(key);
  this->definitions[key].insert(this->definitions[key].end(), definitions.begin(), definitions.end());
}

std::vector<std::string> Word::get_definition(std::string key) {
  this->initialize_definition(key);
  return this->definitions[key];
}

float Word::compare_to_definition(std::string key, std::string str) {
  float result = 0;
  this->initialize_definition(key);
  for (auto it = this->definitions[key].begin(); it < this->definitions[key].end(); ++it) {
    float current = strlib::percentual_similiarity(strlib::string_to_wstring(str), strlib::string_to_wstring(*it));
    result = (current > result ? current : result);
  }
  return result;
}
