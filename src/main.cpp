#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#include "core.hpp"

using namespace lt;

std::vector<std::string> ARGS;
std::vector<Word*> words;

void load_dictionaries() {
  auto file_names = arg::values("-d", ARGS);
  for (auto it = file_names.begin(); it < file_names.end(); ++it) {
    std::ifstream file;
    file.open(*it);
    if (!file.is_open()) {
      continue;
    }
    for (std::string line; std::getline(file, line);) {
      //std::cout << line << std::endl;
      words.push_back(parse::as_word(line));
    };
    file.close();
  };
};

int main(int argc, char** argv) {
  ARGS = arg::parse(argc, argv);
  load_dictionaries();
};
