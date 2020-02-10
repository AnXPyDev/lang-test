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
    }
    file.close();
  }
}

float test_definition(lt::Definition* def, std::string from, std::string to) {
  std::cout << strlib::concat(def->get_translation(from), ", ") << " (" << from << ") -> (" << to << ") ";
  std::string answer;
  std::getline(std::cin, answer);
  float result = def->check_translation(to, answer);
  std::cout << result*100 << "%, correct answers: " << strlib::concat(def->get_translation(to), ", ") << std::endl;
  return result;
}

void test() {
  auto langs = arg::values("-l", ARGS);
  if (langs.size() < 2 or !arg::exists("-l", ARGS)) {
    std::cout << "-l requires two values" << std::endl;
    return;
  }
  auto definitions = dictionary.get_translatable(langs[0], langs[1]);
  int n = definitions.size();
  if (arg::exists("-n", ARGS)) {
    auto vals = arg::values("-n", ARGS);
    if (vals.size() > 0) {
      n = CLAMP(stoi(vals[0]), 0, n);
    }
  }

  float total_score = 0;
  float max_score = (float)n;

  auto order = random::unique_integer(0, definitions.size() - 1, n);

  for (auto it = order.begin(); it < order.end(); ++it) {
    total_score += test_definition(definitions[*it], langs[0], langs[1]);
  }

  std::cout << "You scored: " << total_score << "/" << max_score << " or " << (int)((total_score/max_score)*100) << "%" << std::endl;
  
}

int main(int argc, char** argv) {
  ARGS = arg::parse(argc, argv);
  load_dictionaries();

  if (arg::exists("-t", ARGS)) {
    test();
  }

  return 0;
}
