#include <iostream>
#include <string>
#include <vector>

#include "word.hpp"
#include "strlib.hpp"
#include "parse.hpp"

using namespace lt;

Word* parse::as_word(std::string str) {
  Word* result = new Word();

  int state = 1;
  size_t look_from = 0;
  std::string current_key;
  while (true) {
    size_t semicolon = str.find(";", look_from);
    size_t first_quote = str.find("\"", look_from);
    if (first_quote == std::string::npos) {break;};
    if (semicolon < first_quote) {
      state = 1;
      look_from = semicolon + 1;
      continue;
    };
    size_t second_quote = str.find("\"", first_quote + 1);
    if (second_quote == std::string::npos) {break;};
    std::string cut = str.substr(first_quote + 1, second_quote - first_quote - 1);
    if (state == 1) {
      current_key = cut;
      result->initialize_definition(current_key);
      state = 2;
    } else if (state == 2) {
      result->define(current_key, cut);
    }
    look_from = second_quote + 1;
    //std::cout << semicolon << " "<< first_quote << " " << second_quote << " " << cut << std::endl;
  };

  return result;
};
