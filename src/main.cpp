#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#include "core.hpp"

using namespace lt;

std::vector<std::string> ARGS;
std::vector<lt::Word*> words;
lt::Dictionary dictionary;

void load_dictionaries() {
  auto file_names = arg::values("-d", ARGS);
  for (auto it = file_names.begin(); it < file_names.end(); ++it) {
    std::ifstream file;
    file.open(*it);
    if (!file.is_open()) {
      continue;
    }
    for (std::string line; std::getline(file, line);) {
      parse::to_dictionary(line, &dictionary);
    };
    file.close();
  };
};

float test_word(Word* word, std::string from, std::string to) {
  std::cout << strlib::concat(word->get_definition(from), ", ") << " (" << from << ") -> (" << to << ") ";
  std::string answer;
  std::getline(std::cin, answer);
  float result = word->compare_to_definition(to, answer);
  std::cout << (int)(result * 100) << "% correct, Correct answers: " << strlib::concat(word->get_definition(to), ", ") << std::endl;
  return result;
}

void test(std::string from, std::string to) {
  int count = words.size();
  auto narg = arg::values("-n", ARGS);
  if (narg.size() > 0) {
    count = stoi(narg[0]);
  };
  auto order = random::unique_integer(0, words.size() - 1, count);
  float total = 0.f;
  for (auto it = order.begin(); it < order.end(); ++it) {
    total += test_word(words[*it], from, to);
  };
  std::cout << "Total score " << (int)total << "/" << count << " or " << (int)((total / (float)count) * 100) << "%" << std::endl;
}

int main(int argc, char** argv) {
  ARGS = arg::parse(argc, argv);
  load_dictionaries();
  auto langs = arg::values("-l", ARGS);
  if (langs.size() < 2) {
    std::cout << "-l requires two values" << std::endl;
    return 0;
  };
  return 0;
};
