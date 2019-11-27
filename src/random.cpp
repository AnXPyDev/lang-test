#include <random>
#include <vector>
#include <time.h>

#include "random.hpp"
#include "macros.hpp"

using namespace lt;

std::default_random_engine randomizer(time(NULL));

int random::integer(int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(randomizer);
};

std::vector<int> random::integer(int min, int max, unsigned int n) {
  std::vector<int> result;
  for (unsigned int i = 0; i < n; ++i) {
    result.push_back(random::integer(min, max));
  };
  return result;
};

std::vector<int> random::unique_integer(int min, int max, unsigned int n) {
  std::vector<int> result;
  n = CLAMP(n, 0, (max - min) + 1);
  for (unsigned int i = 0; i < n; ++i) {
  make_choice:int choice = random::integer(min, max);
    for (auto it = result.begin(); it < result.end(); ++it) {
      if (*it == choice) {
        goto make_choice;
      }
    }
    result.push_back(choice);
  }
  return result;
}
