#include <iostream>
#include <string>
#include <vector>

#include "word.hpp"
#include "strlib.hpp"
#include "parse.hpp"
#include "dictionary.hpp"

using namespace lt;

Word* parse::as_word(std::string str) {
  if (str.substr(0, 1) == "#") {
    return NULL;
  };

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


struct Intermediate_defintion {
  short int left_equality;
  short int right_equality;
  std::string language;
  std::string word;
};

void parse::to_dictionary(std::string str, lt::Dictionary* dictionary) {
  std::vector<Intermediate_defintion*> ids;
  if (str.substr(0, 1) == "#" || str.substr(0, 1) == " ") {
    return;
  };

  short int last_equality = 0;
  short int state = 1;
  size_t look_from = 0;
  std::string current_key;
  while (true) {
    size_t equality_pos = str.find(":", look_from);
    short int equality = 0;
    if (equality_pos != std::string::npos) {
      equality = str.substr(equality_pos - 1, 1) == "<" ? -1 : (str.substr(equality_pos + 1, 1) == ">" ? 1 : 0);
    };
    size_t first_quote = str.find("\"", look_from);
    if (first_quote == std::string::npos) {break;};
    if (equality_pos < first_quote) {
      state = 1;
      look_from = equality_pos + 1;
      last_equality = equality;
      continue;
    };
    size_t second_quote = str.find("\"", first_quote + 1);
    if (second_quote == std::string::npos) {break;};
    std::string cut = str.substr(first_quote + 1, second_quote - first_quote - 1);
    if (state == 1) {
      current_key = cut;
      state = 2;
    } else if (state == 2) {
      ids.push_back(new Intermediate_defintion {last_equality, equality, current_key, cut});
    }
    look_from = second_quote + 1;
    //std::cout << semicolon << " "<< first_quote << " " << second_quote << " " << cut << std::endl;
  };


  for (int i = 0; i < ids.size(); ++i) {
    if (ids[i]->left_equality != 1) {
      for (int x = i - 1; x >= 0; --x) {
        if (ids[x]->right_equality != 1) {
          dictionary->set_translation(ids[i]->language, ids[i]->word, ids[x]->language, ids[x]->word, ids[i]->left_equality == -1);
          continue;
        };
        break;
      };
    };
    if (ids[i]->right_equality != -1) {
      for (int x = i + 1; x < ids.size(); ++x) {
        if (ids[x]->left_equality != -1) {
          dictionary->set_translation(ids[i]->language, ids[i]->word, ids[x]->language, ids[x]->word, ids[i]->right_equality == 1);
          continue;
        };
        break;
      };
    };
  };
};
